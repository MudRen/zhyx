#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "����Ѩ��" NOR);
        set("long", HIW @LONG

                �����ǵ���Ѩ

    ������ɭ�ֲ�����ʱ����һ���Ǻ�֮�������˺��¡����ܴ�������
��磬������һ����ζ������ǳ��Ĳ������


LONG NOR );

     set("exits", ([
                "out" : "/d/huanghe/shulin2",
                "north" :"/u/dgdg/fuben/room/sncave",
]));
       
        set("sleep_room", 1);
       /* set("objects", ([
                "/u/dgdg/fuben/npc/shennong": 1,
                "/u/dgdg/fuben/npc/shennong dizi":1,
               
        ])); */
      
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
                if ( objectp(present("tie chuanjia", environment(me))))
                {
                        write(CYN "ֻ��������һ�����ȣ�����λ" +
                              RANK_D->query_respect(me) + CYN
                              "����ͣ������\n" NOR);
                        return 1;
                }
                message_vision(HIW "\n$N" HIW "˳����������һ"
                               "�ݣ��������������Ʈ����ȥ����\n"
                               NOR, this_player());
                me->move(__DIR__"sky2"); 
                return 1;
        }
        return 0;
}

