
#include <ansi.h>

inherit NPC;

#define PLACE "hz"     //����
#define TYPE  "good"    //�׵�
#define WAIT_TIME 60    //��ɲ�������ķ�ʡʱ��

mapping bang_good = ([
        "name" : "�޼���",
        "id"   : "wjb",
        "place": "hz",
        "boss" : "�򽣳�",
        "place_name" : "����",
]);

void create()
{
        set_name("�򽣳�", ({ "wan jianchou", "wan" }));
        set("gender", "����");
        set("age", 42);
        set("long", "���������˾������������\n");
        set("nickname",HIY"���ϴ���"NOR);
        set("title","�޼��ﺼ�ݷֶ�");
        set("per",28);
        set("combat_exp", 1000000);
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

