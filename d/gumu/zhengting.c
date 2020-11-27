#include <ansi.h>
inherit ROOM;

int do_sleep(string arg);

void create()
{
        set("short", "����");
        set("long", @LONG
�����ǹ�Ĺ������������Ӧͣ�����ѹ�ľ֮��Ķ�����ȴ
��֪�����˰㵽����ȥ�ˡ������ж�����һλ������Ů������
�ϰڷ���һ��ʯͷ���ɵĴ�(chuang)�����к�ϵ��һ�����ӣ�
��֪����ʲô�õģ�����֮�⣬���ް��衣
LONG
        );

        set("exits", ([
                "west" : __DIR__"liangong",
                "north" : __DIR__"xiaoting",
                "south" : __DIR__"houting",
        ]));

   /*     set("objects", ([
                CLASS_D("gumu") + "/longnv" : 1,
        ]));      */
        set("valid_startroom",1);

        set("item_desc", ([
                "chuang": HIC "����һ����" HIW "ǧ�꺮��" HIC "��ɵĺ��񴲡�\n" NOR,
        ]) );
        setup();
        "/clone/board/gumu_b"->foo();
}

void init()
{
        add_action("do_sleep", "sleep");
}

int do_sleep(string arg)
{
        object me=this_player();
        int lvl_force;        

        lvl_force = (int)me->query_skill("force");
        if (lvl_force > 50)
        {       
                if ( me->query("max_neili") > 1500 )
                {
                write(HIR"����ô�������˻���?\n"NOR);
                return 1;
                  }
                message_vision(HIC "\n$N" HIC "�����˺��񴲣���ʼǱ���ڹ���ʹ��"
                               "Ϣ���д�С���졣\n", this_player());
                if (random(20) > 12)
                {
                        message_vision(HIM "\n$N" HIM" ��Ϣ��ϣ�ֻ���þ�����"
                                       "����Ϣ���������ڶ�����\n" NOR, this_player());
                        me->add("max_neili",1);
                        me->receive_damage("qi", lvl_force / 3 + random(lvl_force / 3));
                        me->start_busy(1+random(2));
                }
                else
                {
                        message_vision(HIY "\n$N" HIY "��Ϣ��ϣ�վ������������������"
                                       "������ûʲô������\n" NOR, this_player());
                        me->receive_damage("qi", 10 + random(10));
                        me->start_busy(1);
                }
        } else
        {
                message_vision(HIW "\n$N" HIW "���Ϻ��񴲣�ֻ���ñ���̹ǣ�������"
                               "��һ���Ǳ�����������������\n", this_player());
        }
        return 1;
}


