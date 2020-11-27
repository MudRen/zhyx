// gui2-2.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIB"һ��������Զ�������㼱����������֮����ȥ��" +
                "����һ�߹�ľ�ƺ������ҵ�ײ���ţ�ͻȻ�׸Ǳ�һ�ɹ������ɡ�\n" +
                HIR"һ��Ѫ��֮����ֱ������������\n"NOR; 

string *stya = ({ 
HIB"����һ���ƿ�֮����$N���ɸе�һ˿����Ϯ����\n"NOR, 
HIB"$N����˫������һ������ʮָ�����ǣ�����ʹ�ι�ȥ��\n"NOR, 
HIB"$NͻȻ�������ϱ�ҧ��һ�£���ʹ�ѵ���\n"NOR, 
HIB"$NͻȻ�������ϱ�����ץס����ʧɫ����æ����������\n"NOR
}); 

string *styb = ({ 
HIC"$N��$n�ȵ���������ү����Ҫ�������ʮ�˲�����������ó�������\n"NOR,
HIY"$N�������е�"HIM"��ľ��"HIY"�����������⻷����$n���ڵ��С�\n"NOR
});

void check_time();

void create()
{
    set_name("��ʬ", ({ "corpse ghost", "ghost" }));
    set("gender", "����");
    set("race", "��ħ");
    set("age", 200);
    set("per", 12);
    set("long",
        "һ���������ɵĽ�ʬ���쳣���ͣ�����ʳ���������Ѫ��ʹ֮�ݽ߶�����\n");
    set("combat_exp", 50000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "����", "��צ" }) );
    set("verbs", ({ "bite", "claw" }) );
    set("env/invisible", 1);
    set("water", 200);
    set("food", 200);
    set("apply/attack", 260);
    set("apply/defense", 260);
    set_skill("parry", 250);
    set_skill("dodge", 300);

    set("chat_chance", 80);
    set("chat_msg", ({ (: check_time :) })); 
    setup();
    keep_heart_beat();
}

#include "/u/yuchang/quest/npc/ghoster.h"

