// gui1-2.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIC"���Ȼ����һ��������Ů�ڲݴ���������ֹ����첽�߽�����ǰ�쿴��" +
                   "������Ů���������ǰ��ʧ��\n" +
                HIB"��Χ����ɲ�Ǽ���ر�Ĺ���Ī�⡣\n"NOR; 

string *stya = ({ 
HIB"��Χ�������ȴ����Ů�ӵ���Ц��������˷�������$N����־��Щ�Ժ���\n"NOR, 
HIB"һ������絽��ǰ��$N��������һ�ڣ�ֻ��������������ŭ�����۰㷭����ֹ��˵�����������ܡ�\n"NOR, 
HIB"$Nͻ��������������ͷ�����������������̣����д󺧡�\n"NOR, 
HIB"$N�е�һ˫�廬��˫�������ϸ�������ʧɫ����æ����������\n"NOR
}); 

string *styb = ({
HIC"$N��$n��ȵ��������˾�������ײ������ү������������ó�������\n"NOR,
HIC"$N������"HIY"��ֽ"HIC"�ĳ���һ��ǿ������$n��\n"NOR,
HIY"$N�������е�"HIM"��ľ��"HIY"������ҫ�۵Ĺ�â�����������$n��ȥ��\n"NOR
});

void check_time();

void create()
{
    set_name("���꾫", ({ "fox ghost", "ghost" }));
    set("gender", "Ů��");
    set("race", "��ħ");
    set("age", 200);
    set("per", 30);
    set("long",
        "һ����ǧ������������ɵľ��顣���������ò��Ů���ˡ�\n");
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

