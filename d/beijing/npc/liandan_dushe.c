#include <ansi.h>
inherit NPC;
void create()
{
        set_name("����", ({ "du she", "du", "she"}));
        set("long",     "һ֧�������ŵĶ��ߣ�����������ض����㡣\n");
        set("race", "����");
        set("age", 3);
        set("attitude", "peaceful");
        set("max_ging", 40);
        set("max_qi", 40);
        set("str", 10);
        set("cor", 30);
        set("verbs", ({ "bite" }) );
        set_temp("apply/attack", 6);
        set_temp("apply/damage", 6);
        set_temp("apply/armor", 6);
        set("combat_exp", 1000);
        setup();
}
void init()
{
        object ob;

        if (! living(this_object()))
        return; ::init();

        if (interactive(ob = this_player()))
        {
        remove_call_out("kill_ob");
        call_out("kill_ob", 1, ob); 
        }       
}
