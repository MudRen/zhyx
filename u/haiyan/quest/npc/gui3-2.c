// gui3-2.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIW"��Ȼ��һ����Ӱ�������������ɣ�С��һ�����ѱ���ʬ����ס��\n"NOR; 

string *stya = ({ 
HIB"$N��ǰһ���������ѱ���ʬ��������ס���ٸ���Ϣ������˫�۷��ڡ�\n"NOR, 
HIB"$N���ϵĹ�ʬ����һ�ɹ���һ�������㲻�ȣ���ǰ�˵��ڵء�\n"NOR, 
HIB"ֻ������һ����$N���������ѱ�ʮָ���룬������ɫ�Ұס�\n"NOR, 
HIB"$N���±���ʬ��һ������ˤ����\n"NOR
}); 

string *styb = ({ 
HIC"$N��$n�ȵ������δ���ħ����������������ү����Ҫ������������\n"NOR,
HIW"$N�Ӷ����е�"HIM"��ľ��"HIW"���������⽫��ʬ�������Ƭ��������衣\n"NOR
});

void check_time();

void create()
{
    set_name("ľ����", ({ "mummy ghost", "ghost" }));
    set("gender", "����");
    set("race", "��ħ");
    set("age", 200);
    set("per", 15);
    set("long",
        "һ��������ʬ�岻������ɵĹ�ꡣ���ϲ����˹�ʬ����ʮ�ֿɲ���\n");
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

