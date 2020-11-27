#include <command.h>
#include <dbase.h>
#include <origin.h>
#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIW "��ͷ����" NOR, ({"zhan ma", "horse", "ma"}));
        set("race", "Ұ��");
        set("age", 3);

        set("combat_exp", 500000);
        set("long", 
                "һƥ��ͷ����ȫ��ѩ�׵�ë����ɷ���񿡡�\n");

        set("limbs", ({ "ͷ��", "����", "����", "β��" }) );
        set("verbs", ({ "bite", "hoof" }) );

        set("str", 20+random(10));
        set("con", 20+random(5));
        set("dex", 20+random(5));
        set("age", 20+random(30));   
        set("ridable", 1); 
 
        set_temp("apply/attack", 3);
        set_temp("apply/defense", 5);
        set_temp("apply/armor", 1);

        set("ride_prop/dodge",100);
        set("ride_prop/defense",100);

        set("no_get",1);
        set("no_drop",1);
        set("no_put",1);

        set("chat_chance", 5);
        set("chat_msg", ({
                 HIW"ս��ס�ص��������Ӳ�ͦ���ٴ��ŵ��档\n"NOR,
        }) );

        setup();
}


void die()
{
        destruct(this_object());
        return;
}
