#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY "�������š�" NOR);
        set("long", HIW @LONG
�����������������ããһƬ�ƺ�����ǰһ����ΰ�ĳ����Ĵ�
�ţ����ŵ�������������һλ���ӣ��ƺ�����ĵ����������⡣����
Ҳ��һ������(yunti)����˵��������͵��ﴫ˵�еļ��������ˡ�
LONG NOR );
        set("sleep_room", 1);
        set("objects", ([
                __DIR__"npc/li": 1,
        ]));
        setup();
}

void init()
{
        add_action("do_move", "jump");
        add_action("do_move", "move");
        add_action("do_move", "tiao");
        add_action("do_move", "enter");
        add_action("do_move", "up");
}

int do_move(string arg)
{
        object paper,
        me = this_player();

        if (! arg || arg == "")
                return 0;

        if (arg == "yunti")
        {
                if ( objectp(present("li xunhuan", environment(me))))
                {
                        write(CYN "ֻ����Ѱ��˵��������λ" +
                              RANK_D->query_respect(me) + CYN
                              "���㻹�������ɡ���\n" NOR);
                        return 1;
                }
                message_vision(HIW "\n$N" HIW "˳����������һ"
                               "�ݣ��������������Ʈ����ȥ����\n"
                               NOR, this_player());
                me->move(__DIR__"heaven"); 
                return 1;
        }
        return 0;
}


