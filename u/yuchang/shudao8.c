#include <ansi.h>
inherit ROOM;

#define _DEBUG_1_
#ifdef _DEBUG_1_
#else
#endif

// �೤ʱ���һ�Σ�һ��(24Сʱ=86400��)
#define PERIOD_TIME 86400

// ÿ�δ򿪶೤ʱ�䣿(10����)
#define OPEN_TIME   600

// misu 2006-1-16 19:30
// add some function to open the enterance randomly
// Ϊ�˼������ֱ�ӽ�ʱ��Ŀ��Ʒ���������ļ����棻��ʵ�����е�ʱ��
// Ϊ��׼ȷ��������һ��adm/daemons/�µ��ļ�������ÿ�μ���ʹ򿪵�ʱ�䣬
// ��mud�����ʱ���Զ����������daemon

// ���һ����ʲôʱ������ʱ��ģ�
int last_init_time;
// ���һ�δ򿪵�ʱ��
int last_open_time;

void open()
{
    // ������
    set("exits/down", "/u/yuchang/dongkou.c");

    CHANNEL_D->do_channel(this_object(), "rumor", "��˵�ɶ���ˮ���ģ�����������˼��ˣ�");
    remove_call_out("open");
    call_out("close", OPEN_TIME);
}

void close()
{
    delete("exits/down");
    CHANNEL_D->do_channel(this_object(), "rumor", "�ɶ���ˮ���ˣ�������ٴ���û�ں�ˮ֮�У�");
    remove_call_out("open");
    remove_call_out("close");
}

void recalc()
{
    last_open_time = time() + random(PERIOD_TIME); // �ڽ�������24��Сʱ�����Ĵ�һ��
    last_init_time = time() + PERIOD_TIME;

    remove_call_out("open");
    remove_call_out("close");
    remove_call_out("recalc");
    call_out("open", last_open_time-time());
    call_out("recalc", PERIOD_TIME);
}

int do_open(string arg)
{
    object who = this_player();
    string id = who->query("id");

    if( id == "yuchang" )
    {
        last_open_time = time() + 10; // �ڽ�������10��֮���
        last_init_time = time() + PERIOD_TIME;

        remove_call_out("open");
        remove_call_out("close");
        call_out("open", last_open_time-time());
        call_out("recalc", PERIOD_TIME);

        return 1;
    }

    return 0;
}

int do_close(string arg)
{
    object who = this_player();
    string id = who->query("id");

    if( id == "yuchang" )
    {
        close();

        return 1;
    }

    return 0;
}

void init()
{
#ifdef _DEBUG_1_
    add_action("do_open", "do_open");
    add_action("do_close", "do_close");
#endif

    // ��û�м���򿪵�ʱ��
    if( !last_init_time )
    {
        last_open_time = time() + random(PERIOD_TIME) + 10; // �ڽ�������24��Сʱ�����Ĵ�һ��
                                                            // +10 ��֤��10��֮��Ŵ�
        last_init_time = time() + PERIOD_TIME;

        remove_call_out("open");
        remove_call_out("close");
        remove_call_out("recalc");

        call_out("open", last_open_time-time());
        call_out("recalc", PERIOD_TIME);
    }

    // �Ѿ�����һ��û�и�����
    if( last_init_time < time() )
    {
        last_open_time = time() + random(PERIOD_TIME); // �ڽ�������24��Сʱ�����Ĵ�һ��
        last_init_time = time() + PERIOD_TIME;

        remove_call_out("open");
        remove_call_out("close");
        remove_call_out("recalc");
        call_out("open", last_open_time-time());
        call_out("recalc", PERIOD_TIME);
    }
}

void create()
{
        set("short", "�ͱ�");
        set("long", @LONG
�Թ����ƣ�����ѣ����������죬�غ����޹ִ�ʫ�����
���д��·�����������ν�����ޱȣ�һ�������ϵĽ�ˮ��һ
�����絶�а���ͱڡ���������һ����Σ�յ��ͱ��ϣ��㻹��
���߰ɣ���һ��С�ĵ�����ȥ��
LONG);
        set("exits", ([
                "eastdown" : __DIR__"shudao7",
                "westup" : __DIR__"shudao9",
        ]));

        // ע�⣬�������������������䲻�ᱻ����
        set("no_clean_up", 1);

        set("outdoors", "chengdu");
        setup();
        //replace_program(ROOM);
}


