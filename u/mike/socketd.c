// socket_d.c
#include <net/socket.h>
#include <net/socket_errors.h>

#define monitor(x)
#define PROCESS_TIMEOUT         30

mapping sockets = allocate_mapping(0);

mapping query_sockets()
{
    return sockets;
}

private void connect_timeout(int fd)
{
    if( undefinedp(sockets[fd]) ) return;
    if( objectp(sockets[fd]["owner"]) )
        evaluate(sockets[fd]["stat_callback"], 
        "Unable to connect to remote host: Connection timeout");
    socket_close(fd);
    return;
}

private void receive_data(int fd, mixed data)
{ 
    if(undefinedp(sockets[fd]))
        return;

    if( !sockets[fd]["owner"] )
    {
        socket_close(fd);
        return;
    }
    if(objectp(sockets[fd]["owner"]))
        evaluate(sockets[fd]["rece_callback"], data);
    return;
}

private void write_data(int fd)
{
    sockets[fd]["write_fd"] = fd;
        
    if( !undefinedp(sockets[fd]["connect_handle"]) )
    {
        remove_call_out(sockets[fd]["connect_handle"]);
        map_delete(sockets[fd], "connect_handle");
    }

    // ����յ� socket write callback ʱ
    // buffer ����ѶϢδ�������������ͣ������ buffer
    if( sockets[fd]["write_buffer"] )
    {
        socket_write(fd, sockets[fd]["write_buffer"]);
        sockets[fd]["write_buffer"] = 0;
    }
    return;
}


void socket_close(int fd)
{
    monitor("socket_close: " + fd);
    if(undefinedp(sockets[fd]))
        return;
    if(!objectp(sockets[fd]["owner"])) {
        map_delete(sockets, fd);
        return;
    }

    if( !undefinedp(sockets[fd]["clos_callback"]) && objectp(sockets[fd]["owner"]) )
    {
        evaluate(sockets[fd]["clos_callback"]);
    } else
        efun::socket_close(fd);
    
    if( !undefinedp(sockets[fd]["connect_handle"]) )
    {
        remove_call_out(sockets[fd]["connect_handle"]);
        map_delete(sockets[fd], "connect_handle");
    }
    map_delete(sockets, fd);
    return;
}

void socket_send(int fd, mixed data)
{
    int res;

    if( !data || data == "" ) return; 
    // ��δ�յ� socket write callback ǰ���������͵�ѶϢ���� buffer
    if( !sockets[fd]["write_fd"] )
    {
        if( !sockets[fd]["write_buffer"] )
            sockets[fd]["write_buffer"] = data;
        else
            sockets[fd]["write_buffer"] += data;
        return;
    }
        
    // ��� buffer ����ѶϢ��δ�ͳ������뱾��ѶϢͬʱ�ͳ�
    if( sockets[fd]["write_buffer"] )
    {
        sockets[fd]["write_buffer"] += data;
        res = socket_write(fd, sockets[fd]["write_buffer"]);
    }
    else res = socket_write(fd, data);

    switch(res) {

        case EESUCCESS:         /* �ɹ� */
        case EECALLBACK:        /* �ȴ���� */
            sockets[fd]["write_buffer"] = 0;
            break;
        case EEALREADY:         /* �����ѽ��� */
        case EEWOULDBLOCK:      /* ����ͣ�� */
        case EESEND:            /* �������ϴ��� */
            if( !sockets[fd]["write_buffer"] )
                sockets[fd]["write_buffer"] = data;

            call_out((: socket_send :), 1, fd, "");
            break;
        default:                /* �������� */
            if(objectp(sockets[fd]["owner"]))
                evaluate(sockets[fd]["stat_callback"], socket_error(res));
            socket_close(fd);
            break;
    }
}

varargs int socket_open(
    string host, 
    int port,
    int mode,
    function rece_callback, 
    function stat_callback, 
    function clos_callback
)
{
    int socket_fd, res;
    string addr;

    monitor("socket_open: " + sprintf("%s %d %O %O %O", 
        host, port, rece_callback, stat_callback, clos_callback));

    mode = mode || STREAM_BINARY;

    socket_fd = socket_create(mode, 
        (: receive_data :), (: socket_close :));
    if( socket_fd < 0 )
    {
        evaluate(stat_callback, "socket_create: " + socket_error(socket_fd));
        return -1;
    }

    sockets[socket_fd] = allocate_mapping(0);
    addr = sprintf("%s %d", host, port);
    res = socket_connect(socket_fd, addr, (: receive_data :), (: write_data :));

    if( res != EESUCCESS )
    {
        evaluate(stat_callback, "socket_connect: " + socket_error(res));
        socket_close(socket_fd);
        return -1;
    }

    sockets[socket_fd]["addr"] = host;
    sockets[socket_fd]["port"] = port;
    sockets[socket_fd]["owner"] = previous_object();
    sockets[socket_fd]["rece_callback"] = rece_callback;
    sockets[socket_fd]["stat_callback"] = stat_callback;
    sockets[socket_fd]["clos_callback"] = clos_callback;
    sockets[socket_fd]["connect_handle"] = call_out((: connect_timeout :), 
        PROCESS_TIMEOUT, socket_fd);
    return socket_fd;
}

