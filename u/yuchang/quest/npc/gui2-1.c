// gui2-1.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIW"ͻȻ��е�һ��ʮ��ǿ�ҵ�Թ��ֱ��������\n"NOR;

string *stya = ({ 
HIB"һ��̶��ĳ�Х������$N�е����������쳣���ܡ�\n"NOR, 
HIB"$N����һ����ҵĳ�̾���ٸ������쳣���̲�ס���һ��"HIR"��Ѫ"HIB"��\n"NOR
}); 

string *styb = ({
HIC"$N��$n�ȵ���������ү���ճ������㣬����Ͷ̥ת�������ٺ��ˣ���\n"NOR,
HIY"$N�Ӷ����е�"HIM"��ľ��"HIY"����ʱ��ؼ�������죬Թ��������\n"NOR
});

void check_time();

void create()
{
    set_name("ԩ��", ({ "wrong ghost", "ghost" }));
    set("gender", "Ů��");
    set("race", "��ħ");
    set("age", 200);
    set("per", 20);
    set("long",
        "һ����ԩ�����������󼴱��ԩ�꣬�����Ʒ������������޹������顣\n");
    set("combat_exp", 100000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "����", "��צ" }) );
    set("verbs", ({ "bite", "claw" }) );
    set("env/invisible", 1);
    set("water", 200);
    set("food", 200);
    set("apply/attack", 250);
    set("apply/defense", 250);
    set_skill("parry", 250);
    set_skill("dodge", 300);

    set("chat_chance", 80);
    set("chat_msg", ({ (: check_time :) })); 
    setup();
    keep_heart_beat();
}

#include "/u/yuchang/quest/npc/ghoster.h"

