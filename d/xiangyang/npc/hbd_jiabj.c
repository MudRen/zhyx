//hbd_jiabj.c

#include <ansi.h>

inherit NPC;

#define PLACE "xy"
#define TYPE  "bad"
#define WAIT_TIME 60

mapping bang_bad = ([ 
        "name" : "�ڰ׵�",
        "id"   : "hbd",
        "place": "xy",      //�ܻ�
        "boss" : "�ֲ���",
        "place_name" : "����" //�ֻ�
]);

void create()
{
        set_name("�ֲ���", ({ "jia bujia", "jia" }));
        set("gender", "����");
        set("age", 30);
        set("long", "������" + bang_bad["name"] + "����" + bang_bad["place_name"] + "�ķ�̳���졣\n");
        set("nickname",HIY"����Ϊ�ý�����"NOR);
        set("title",HIB"��"HIW"��"NOR"����̳��"NOR);
        set("per",20);
        set("combat_exp", 800000);
        set("shen_type", -1);
        set("attitude", "peaceful");
        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver",2);
}
#include <boss_bad.h>

