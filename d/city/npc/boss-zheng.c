//xym_yz_npc.c

#include <ansi.h>

inherit NPC;

#define PLACE "yz"     //���ݷֶ�
#define TYPE  "good"    //�׵�
#define WAIT_TIME 60    //��ɲ�������ķ�ʡʱ��

mapping bang_good = ([
        "name" : "������",
        "id"   : "xym",
        "place": "ca",      //�ܶ�
        "boss" : "������",
        "place_name" : "����" //�ֶ�
]);

void create()
{
        set_name("֣�ƻ�", ({ "zheng yunhu", "zheng" }));
        set("gender", "����");
        set("age", 38);
        set("long", "������" + bang_good["name"] + "����" + bang_good["place_name"] + "�ķֶ������\n");
        set("nickname",HIY"�޵����師"NOR);
        set("title",GRN"���������ݷֶ����"NOR);
        set("per",18);
        set("combat_exp", 800000);
        set("shen_type", 1);

        set("attitude", "peaceful");
        
        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver",2);
}
#include <boss_good.h>


