
// boss-ju.c 
#include <ansi.h>

inherit NPC;

#define PLACE "cd"     //����
#define TYPE  "bad"    //�ڵ�
#define WAIT_TIME 60    //��ɲ�������ķ�ʡʱ��



mapping bang_bad = ([
        "name" : "������",
        "id"   : "xlm",
        "place": "cd",
        "boss" : "���޷�",
        "place_name": "�ɶ�",
]);

void create()
{
        set_name("���޷�", ({ "leng wufeng", "leng","wufeng" }));
        set("gender", "����");
        set("age", 32);
        set("long", "������������ģ��沿����ס��һ�㣬û��һ�����仯��������" + bang_bad["name"] + "�ĳɶ�̳����\n");
        set("title",HIB"�����ųɶ�̳��"NOR);
        set("per",20);
        set("combat_exp", 1000000);
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


