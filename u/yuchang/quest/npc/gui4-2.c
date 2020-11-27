// gui4-2.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIB"�����ͻȻ���������һ�������ס��̫������̼��ɳ��ʯ�����ذ���\n"NOR; 

string *stya = ({ 
HIB"һ�ɺ�������������������һ�����а�Ů��ɳ��ɤ�������������׵���Ц�š�\n"NOR, 
HIB"һ�����Ǻ���Ľ���������˷�ӿ������$Nֻ����ͷ�����ѣ���ð���ǣ�\n"NOR, 
HIB"����ͻȻ�ѿ�һ�������Ŀ��ӣ�����߷ɳ������ִ�����������ε�ץס�����֫��ƴ�����ѷ����ϡ�\n"NOR, 
HIB"$n��������һ��ǿ�ҵ����������������һ�ɺ�����ֱ��$N��ȫ��\n"NOR
}); 

string *styb = ({ 
HIC"$N�ƿ����ģ�����Ѫ�������������"HIM"��ľ��"HIC"�ϣ����һ�������̶�����\n"NOR,
HIC"$Nһ����Х������ֱ��������$n�����Ĳ��ƶ�ʱ���������֮�䡣\n"NOR,
HIY"$N�Ӷ�������ľ��������һ���������������½�⣬��$n������ס��\n"NOR
});

void check_time();

void create()
{
    set_name("ǧ������", ({ "tree ghost", "ghost" }));
    set("gender", "����");
    set("race", "��ħ");
    set("age", 200);
    set("per", 22);
    set("long",
        "һ��ǧ�������������ɵ���ħ��ʮ��ǿ����\n");
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

#include "/u/yuchang/quest/npc/ghoster.h"

