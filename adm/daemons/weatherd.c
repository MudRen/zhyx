// ����Ԥ������
// ��������ץȡ��Ϣ��Ԥ������
// ������Ϊץȡ���ԣ�"202.106.184.193"������Ԥ����Ϣ��

#include <runtime_config.h>
#include <getconfig.h>
#include <net/socket.h>
#include <ansi.h>

// 202.106.184.193 202.108.36.156
#define SITE "202.106.184.193 80"

inherit F_DBASE;

int have_get = 0;
int fail = 0;
string msg = "";

int check_time();
void close(int fd);
void write_s(int fd);

void create()
{
      set("channel_id", "����̽�⾫��");
      seteuid(getuid());
      check_time();
}

int check_time()
{
      mixed* times = localtime(time());
      int hours = times[2];
      int fd,fc;

      if(1 || (hours == 3 && ! have_get)) // ÿ��3�㿪ʼץ��ҳ
      {
             fd = socket_create(STREAM, "read_callback", "write_callback");

             if(fd < 0)
             {
                   write("socket_create error " + socket_error(fd) + "\n");
                   socket_close(fd);
                   return 1;
             }

             fc = socket_connect(fd, SITE, "read_callback", "write_callback");

             if(fc != EESUCCESS)
             {
                   close(fd);
                   write("socket_connect error " + socket_error(fc) + "\n");
                   socket_close(fd);
                   return 1;
             }
/*
             remove_call_out("write_s");
             call_out("write_s", 2, fd);
*/
             remove_call_out("close");
             call_out("close", 20, fd); // �ȴ���ʮ�룬��ʱ��Ϊ����ʧ�ܡ�
       }

       if(hours == 12)
       {
               have_get = 0; // 12��������
               msg = "";
               fail = 0;
       }

       remove_call_out("check_time");
       call_out("check_time", 15 * 60);
       return 1;
}

void read_callback(int fd, mixed val)
{
        CHANNEL_D->do_channel(this_object(), "wiz", HIR "msg = " + val + "\n" NOR);
        msg += sprintf("%s", val);
        CHANNEL_D->do_channel(this_object(), "wiz", HIR "msg = " + msg + "\n" NOR);
        log_file("weather_msg", msg);
}

void write_callback(int fd)
{
        CHANNEL_D->do_channel(this_object(), "wiz", HIR "msg2 = " + msg + "\n" NOR);
        return;
}

void close(int fd)
{        
        if(strsrch(msg, "HTTP/1.1 200 OK") != -1) //�ɹ���ȡ
        {
               log_file("weather", msg + "\n");
               have_get = 1;
        }

        // ��ʱ�ر�����
        socket_close(fd);

        return;
}
