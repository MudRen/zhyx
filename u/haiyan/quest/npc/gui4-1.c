// gui4-1.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIB"ͻȻһ���ȳ���Ũ�����������ܣ���ǰ��ʱ���һ�š�\n"NOR; 

string *stya = ({ 
HIB"��Ȼһ��"HIW"�׹�"HIB"��$N����������ֱ�һ�飬�ѱ�$nҧ�С�\n"NOR, 
HIB"$N���屻$n��ס��Խ��Խ��������͸����������\n"NOR, 
HIB"$N����һ���ʹ����$n��β���С�\n"NOR
}); 

string *styb = ({ 
HIC"$Nһ�����ȣ���������"HIY"��ֽ"HIC"����$n�ĳ���\n"NOR,
HIY"$N�Ӷ����е�"HIM"��ľ��"HIY"��ֱ��$n�ߴ硣\n"NOR
});

void check_time();

void create()
{
    set_name("��������", ({ "snake ghost", "ghost" }));
    set("gender", "Ů��");
    set("race", "��ħ");
    set("age", 200);
    set("per", 20);
    set("long",
        "һ�ֶ��߾��������������ɵ���ħ��\n");
    set("combat_exp", 500000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "����", "��צ" }) );
    set("verbs", ({ "bite", "claw" }) );
    set("env/invisible", 1);
    set("water", 200);
    set("food", 200);
    set("apply/attack", 450);
    set("apply/defense", 450);
    set_skill("parry", 450);
    set_skill("dodge", 500);

    set("chat_chance", 80);
    set("chat_msg", ({ (: check_time :) })); 
    setup();
    keep_heart_beat();
}

#include "/u/haiyan/quest/npc/ghoster.h"

