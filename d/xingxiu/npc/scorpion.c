// Code of ShenZhou
// Ryu, 11/20/96.

#include <ansi.h>
inherit NPC;

void create()
{
        set_name(YEL"Ы��"NOR, ({ "scorpion", "xiezi" }) );
        set("race", "����");
        set("subrace", "����");
        set("age", 3);
        set("long", "һֻ��ɫ��Ы�ӣ�β�����л������Ļ��ơ�\n");
        set("attitude", "peaceful");

//        set("limbs", ({ "ͷ��", "����", "����", "ǰ��", "β��" }) );
//        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 900);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 6);
        set_temp("apply/armor", 1);

        set("insect_poison", ([
                "level"  : 80,
                "maximum": 50,
        ]));

        setup();
}
void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) &&
                random(ob->query_kar() + ob->query_per()) < 30) {
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob);
        }
}
void die()
{
        object ob;
        message_vision("\n$Nβ��һ�̣����ˡ�\n", this_object());
        ob = new(__DIR__"scorp_shell");
        ob->move(environment(this_object()));
        destruct(this_object());
}