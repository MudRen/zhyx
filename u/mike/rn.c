//realnews ʵʱ����ϵͳ
//write by Hcifml@Nt2

//Nt2 ��Mudos�е�ֹ� private��ͬ���裬���������Ҿ�����private����ʵ�ܶ�ط��ǲ����õ�

#include <net/socket.h>
#include <ansi.h>

#define SOCK_OB 0
#define TITLE 1
#define HOST 2
#define PAGE_URL 3
#define NEWS_URL 0
#define NEWS_FROM 1
#define NEWS_TIME 2
#define NEWS_DATA 3
#define REFRESH_TIME 7200
#define BROADCAST_TIME 150
#define BROADCAST_NUM 12
#define DEFAULT_LIST_URL "/hotnews/"
#define DEFAULT_NEWS_IP "61.135.153.178"
#define DEFAULT_NEWS_URL "news.sina.com.cn"
#define CLEAR_URL(x) replace_string(x, "\"", "")

#define HTTP_GET_PAGE_REQUEST(_page_, _host_name_) "\n \
GET " + _page_ + " HTTP/1.0\n \
Accept: */ *\n \
Accept-Language: zh-cn\n \
Accept-Encoding: deflate\n \
Host: " + _host_name_ + "\n \
Connection: Keep-Alive\n\n"

#define DEBUGER "hcifml"
#define DEBUG(x) tell_object(find_player(DEBUGER), x)

private void get_news_list(string url);
private void get_each_news_data(int fd);

private mapping news_data;
private mapping news_list;
private mapping group_ids;
private mapping title_ids;
private mapping ready_list;
private int socket_fd;
private int list_idx = 0;
private int get_news_event_id;
private int broadcast_event_id;
mapping socket_obs = allocate_mapping(0);

mapping query_news_data() {return news_data;}
mapping query_news_list() {return news_list;}
mapping query_title_ids() {return title_ids;}

string read_news_list()
{
    string list = sprintf("\n%4s%|12s%-48s\n%64'-'s\n", "���", "���", "����", "");
    string *groups;
    string *titles;

    if(!sizeof(ready_list))
        return "��ǰû�пɶ����š�\n";
    groups = keys(news_data);

    foreach(string gp in groups)
    {
        titles = keys(news_data[gp]);
        foreach(string tt in titles)
        {
            if(query(gp + "/" + tt, ready_list))
                list += sprintf("%2d%2'0'd%|12s%-48s\n", group_ids[gp], title_ids[tt], gp, tt);
        }
    }
    return list;
}

string read_news(string num)
{
    int group_id;
    int title_id;
    string group;
    string title;
    string *title_in_group;
    mixed data;

    if(!sscanf(num[0..0], "%d", group_id))
        return "���ű�Ŵ���\n";
    if(!sscanf(num[1..], "%d", title_id))
        return "���ű�Ŵ���\n";
    if(!sizeof(group_ids))
        return "���ű�Ŵ���\n";
    foreach(string gp, int n in group_ids)
    {
        if(n == group_id) 
        {
            group = gp;
            break;
        }
    }
    title_in_group = keys(news_data[group]);
    foreach(string tt in title_in_group)
    {
        if(title_ids[tt] == title_id)
        {
            title = tt;
            break;
        }
    }
    if(!query(group + "/" + title, ready_list))
        return "���ű�Ŵ���\n";
    data = news_data[group][title];
    return "\n" + HIY + sprintf("%|64s", title) + HIW + "\n" + data[NEWS_URL] + NOR + data[NEWS_DATA];
}

void create_news_board()
{
    string *groups = keys(news_data);
    string *titles;
    int i = 1;
    group_ids = allocate_mapping(0);
    title_ids = allocate_mapping(0);

    foreach(string group in groups)
    {
        int j = 1;
        group_ids += ([ group : i ]);
        i++;
        titles = keys(news_data[group]);
        foreach(string tt in titles)
        {
            title_ids += ([ tt : j ]);
            j++;
        }
    }
}

void create_news_list()
{
    string *groups = keys(news_data);
    
    news_list = allocate_mapping(0);
    foreach(string group in groups)
    {
        foreach(string title in keys(news_data[group]))
        {
            news_list += ([title : news_data[group][title][NEWS_URL]]);
        }
    }
}

private string parse_news_data(string data)
{
    string temp;
    string text = "";
    int i = 0, j = 0, data_size, text_flag = 0, el_flag = 0;

    i = strsrch(data, "<font id=\"zoom\"");
    j = strsrch(data, "http://mms.sina.com.cn/xmlmms/xmlmmsQue.php");
    data = data[i..j];
    i = strsrch(data, "<!--NEWSZW_HZH_BEGIN-->");
    j = strsrch(data, "<!--NEWSZW_HZH_END-->");
    if(i > 0 && j > 0)
        data = data[0..i] + data[j..];
    data_size = sizeof(data);
    i = 0;
    while(i++ < data_size) 
    {
        temp = data[i-1..i-1];
        if(temp == "<") 
        {
            if((data[i] == 'p' || data[i] == 'P') && data[i+1] == '>')
            {
                i += 2;
                text += "\n";
                text_flag = 1;
            }
            else if(data[i] == '/')
            {
                if(data[i+1] == 'p' && data[i+2] == '>')
                {
                    i += 3;
                    text_flag = 0;
                }
                else
                {
                    while(data[i++] != '>') {}
                }

            }
            else if((data[i] == 'b' || data[i] == 'B') && data[i+1] == '>')
            {
                i += 2;
                text += "\n";
            }
            else if(text_flag)
                el_flag = 1;
        }
        else if(temp == ">")
        {
            if(el_flag)
                el_flag = 0;
        }
        else
        {
            if(text_flag && !el_flag)
                text += temp;
        }
    }
    return sort_msg(text);
}


private void get_news_stat(mixed msg, int fd)
{
    DEBUG(sprintf("Get news status: %O\n", fd, msg));
}

private void get_each_news_status(string msg, int fd)
{
    if(fd) DEBUG(sprintf("��ȡ�������š�%s���߳�״����%s\n", socket_obs[fd][TITLE], msg));
    else DEBUG(sprintf("��ȡ���������߳�״����%s\n", msg));
}

private void get_each_news_rece(mixed data, int fd)
{
    set("temp/" + fd, query("temp/" + fd, news_data) + data, news_data);
}

private void get_each_news_close(int fd)
{
    //parse_each_news();
    string title;
    string group_name;
    string news_html_page;
    string *groups = keys(news_data);
    string *news_info;

    if(undefinedp(socket_obs[fd])) return;
    title = socket_obs[fd][TITLE];
    foreach(string group in groups) {
        if(!undefinedp(news_data[group][title])) {
            group_name = group;
            break;
        }
    }
    if(!sizeof(group_name)){
        efun::socket_close(fd);
        if(objectp(socket_obs[fd][SOCK_OB]))
            destruct(socket_obs[fd][SOCK_OB]);
        map_delete(socket_obs, fd);
        return;
    }
    news_info = query(group_name + "/" + title, news_data);
    news_html_page = query("temp/" + fd, news_data);
    if(!sizeof(news_html_page) || strsrch(news_html_page, "</html>") < 0) {
        get_each_news_data(fd);
        return;
    }
    news_html_page = parse_news_data(news_html_page);
    news_info += ({news_html_page});
    set(group_name + "/" + title, news_info, news_data);
    delete("temp/" + fd, news_data);
    efun::socket_close(fd);
    destruct(socket_obs[fd][SOCK_OB]);
    map_delete(socket_obs, fd);
    set(group_name + "/" + title, 1, ready_list);
    if(!sizeof(socket_obs)) 
        delete("temp", news_data);
}

private void get_each_news_data(int fd)
{
    string page_url;
    string host;
    object socket_ob;
    int socket_ob_fd;
    mixed socket_data;

    if(fd) //��ȡָ��fd��news����Ҫ�����ڶ�ȡ���ɹ�ʱ��
    {
        socket_data = socket_obs[fd];
        socket_ob_fd = socket_data[SOCK_OB]->open(socket_data[HOST], 80, STREAM, ({(: get_each_news_rece :), (: get_each_news_status :), (: get_each_news_close :)}));
        if(socket_ob_fd < 0)
            return;
        socket_obs[fd] = ([socket_ob_fd : ({socket_data[SOCK_OB], socket_data[TITLE], socket_data[HOST], socket_data[PAGE_URL]})]);
        socket_data[SOCK_OB]->send(HTTP_GET_PAGE_REQUEST(socket_data[PAGE_URL], socket_data[HOST]));
        return;
    }

    foreach(string title, string url in news_list)
    {
        sscanf(url, "http://%s/%s", host, page_url);
        if(!sizeof(host)) host = DEFAULT_NEWS_IP;
        if(!sizeof(page_url)) continue;
        page_url = "/" + page_url;
        socket_ob = new(SOCKET_OB);
        socket_ob_fd = socket_ob->open(host, 80, STREAM, ({(: get_each_news_rece :), (: get_each_news_status :), (: get_each_news_close :)}));
        if(socket_ob_fd < 0)
            break;
        socket_obs += ([socket_ob_fd : ({socket_ob, title, host, page_url})]);
        socket_ob->send(HTTP_GET_PAGE_REQUEST(page_url, host));
    }
}

private void parse_news_list()
{
    string temp;
    string group_part;
    string group_name;
    string body_part;
    string next_page_url;
    string a_news_page_url;
    string a_news_title;
    string a_news_from;
    string a_news_time;
    int current_page;

    if(! temp = query("temp/list", news_data)) return;
    body_part = temp[strsrch(temp, "!-- nav end -->")..strsrch(temp, "<!-- �����ȵ����Żع� begin -->")];
    while(sscanf(body_part, "%*s<!-- %s begin -->%s<!-- %*s end -->%s", group_name, group_part, body_part) > 0)
    {
        while(sscanf(group_part, "%*s<span style='padding-left:6px'><a href=%s target=_blank>%s</a>%*s<td style='padding-top:2px'>%s</td>%*s<td style='padding-top:2px'>%s</td>%s", a_news_page_url, a_news_title, a_news_from, a_news_time, group_part) > 0)
        {
            a_news_title = replace_string(a_news_title, "/", "��");
            set(group_name + "/" + a_news_title, ({a_news_page_url, a_news_from, a_news_time}), news_data);
        }
    }
}

private void get_news_list_rece(mixed data)
{
    set("temp/list", query("temp/list", news_data) + data, news_data);
}

private void get_news_list_close()
{
    parse_news_list();
    delete("temp/list", news_data);
    create_news_list();
    ready_list = allocate_mapping(0);
    get_each_news_data(0);
    create_news_board();
    broadcast_event_id = SCHEDULE_D->set_event(BROADCAST_TIME, 1, this_object(), "broadcast_news");
}

private void get_news_list(string url)
{
    socket_fd = SOCKET_D->socket_open(DEFAULT_NEWS_IP, 80, STREAM, (: get_news_list_rece :), (: get_news_stat :), (: get_news_list_close :));
    if(socket_fd != 0) {
        if(broadcast_event_id) SCHEDULE_D->delete_event(broadcast_event_id);
        SOCKET_D->socket_send(socket_fd, HTTP_GET_PAGE_REQUEST(url, DEFAULT_NEWS_URL));
    }
}

void broadcast_news()
{
    string *groups = keys(news_data);
    string news_group = groups[random(sizeof(groups))];
    string *titles_in_group = keys(news_data[news_group]);
    string news_title = titles_in_group[random(sizeof(titles_in_group))];
    
    if(!query(news_group + "/" + news_title, ready_list)) 
    {
        broadcast_news();
        return;
    }
    message("realnews", sprintf(WHT "��%s��%s%3s%s%3s(���ű��%d%2'0'd)\n" NOR, news_group, news_title, "", news_data[news_group][news_title][NEWS_TIME], "", group_ids[news_group], title_ids[news_title]), filter_array(users(), (: !$1->query("env/no_realnews") :)));
}

void refresh_news()
{
    get_news_list(DEFAULT_LIST_URL);
}

void create()
{
        seteuid(ROOT_UID);
    news_data = allocate_mapping(0);
    //refresh_news();
    get_news_event_id = SCHEDULE_D->set_event(REFRESH_TIME, 2, this_object(), "refresh_news");
}

