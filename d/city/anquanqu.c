#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "��ȫ��");
        set("long", @LONG
�����Ǳ���̨�µİ�ȫ������������ܰ�ȫ���ٺ٣�
LONG );
        set("biwutai",1);
        set("no_fight",1);
        set("no_sleep_room",1);
        set("no_steal",1);
        set("no_beg",1);
        set("no_get_from",1);
              set("objects", ([ 
                      "/adm/npc/shizhe": 1, 
              ])); 

        set("exits", ([
                "out" : __DIR__"kedian",
                "leitai" : __DIR__"leitai",
        ]));
        setup();
}
int no_die(object me)
{               
        message_vision (HIC"��ȫʹ����ָ��$Nһָ��$N��ʱ�ָ��˾���\n"NOR,me);
        me->revive();
        me->set("eff_qi",me->query("max_qi")); 
        me->set("eff_jing",me->query("max_jing"));               
        me->add("qi",5);
        me->add("jing",5); 
        me->clear_condition("poison");
        return 1;
}


