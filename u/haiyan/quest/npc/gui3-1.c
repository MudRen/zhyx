// gui3-1.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIB"��ͻȻ����һ����Х���·�е�һ����������һ��������\n"NOR; 

string *stya = ({ 
HIB"$N�е�����������ɨ������ʱһ�����������ʹ��\n"NOR, 
HIB"$N�����촽��������ס��һ��"HIR"��Ѫ"HIB"�ӿ��ڼ�к������\n"NOR, 
HIR"$n�ſ�������Ѫ�Ĵ�ڣ���$N����һ����ҧ��\n"NOR, 
HIB"$NͻȻ�������ϱ�����ץס����ʧɫ����æ����������\n"NOR
}); 

string *styb = ({ 
HIC"$N�������е�"HIY"��ֽ"HIC"������$n���ƣ����Ķ�����\n"NOR,
HIY"$N�Ӷ�"HIM"��ľ��"HIY"���û���������⽣Ӱ������һ������$n�̳���\n"NOR
});

void check_time();

void create()
{
    set_name("��Ѫ��", ({ "leech ghost", "ghost" }));
    set("gender", "Ů��");
    set("race", "��ħ");
    set("age", 200);
    set("per", 25);
    set("long",
        "һ��ר����ʳ��Ѫ�Ĺ�ꡣ�������������Ů���Ի��������ˣ���������Ѫ��\n");
    set("combat_exp", 100000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "����", "��צ" }) );
    set("verbs", ({ "bite", "claw" }) );
    set("env/invisible", 1);
    set("water", 200);
    set("food", 200);
    set("apply/attack", 350);
    set("apply/defense", 350);
    set_skill("parry", 350);
    set_skill("dodge", 400);

    set("chat_chance", 80);
    set("chat_msg", ({ (: check_time :) })); 
    setup();
    keep_heart_beat();
}

#include "/u/haiyan/quest/npc/ghoster.h"

