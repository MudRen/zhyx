// gui1-1.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIB"����߹������;�һ������ĺ���ӭ��Ϯ�����������˸����¡�\n"NOR;

string *stya = ({
HIB"һ������Ϯ����$N��Ȼ����ȫ��ѪҺ�ƺ�����������綳ס��\n"NOR,
HIB"$N�е�һ�ɺ���˳����������������ʹ����ƺ���һ����\n"NOR,
HIR"$N�е�����һ���ʹ��\n"NOR,
HIB"$Nͻ�����ϱ�Ұ�����ץס����ʧɫ����æ����������\n"NOR
});

string *styb = ({
HIC"$N��$n��ȵ�������ħ�����ŷ���������������ү�������������ó�������\n"NOR,
HIY"$N�������е�"HIM"��ľ��"HIY"������ҫ�۵Ĺ�â�����������$n��ȥ��\n"NOR,
HIC"$N����"HIM"��ľ��"HIC"�����������𻷣�һȦһȦ����$n��\n"NOR
});

void check_time();

void create()
{
    set_name("Ұ��", ({ "wild ghost", "ghost" }));
    set("gender", "����");
    set("race", "��ħ");
    set("age", 200);
    set("per", 10);
    set("long",
        "һ�������ɲ����Ŀ�����Ĺ�ꡣ����ɫ�Ұף������ֳ��ּ⣬ʮָ���ڵ���
��Ѫ���������ض����㡣\n");
    set("combat_exp", 50000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "����", "��צ" }) );
    set("verbs", ({ "bite", "claw" }) );
    set("env/invisible", 1);
    set("water", 200);
    set("food", 200);
    set("apply/attack", 120);
    set("apply/defense", 120);
    set_skill("parry", 150);
    set_skill("dodge", 200);

    set("chat_chance", 80);
    set("chat_msg", ({ (: check_time :) })); 
    setup();
    keep_heart_beat();
}

#include "/u/haiyan/quest/npc/ghoster.h"

