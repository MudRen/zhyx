// boss-ju.c 
#include <ansi.h>

inherit NPC;

#define PLACE "yz"     //����
#define TYPE  "bad"    //�ڵ�
#define WAIT_TIME 60    //��ɲ�������ķ�ʡʱ��



mapping bang_bad = ([
        "name" : "С����",
        "id"   : "xdh",
        "place": "yz",
        "boss" : "���ϴ�",
        "place_name": "����",
]);

void create()
{
        set_name("���ϴ�", ({ "ju laoda", "laoda","ju" }));
        set("gender", "����");
        set("age", 23);
        set("long", "����һ�����ú�Ӣ�������ӣ�����ȥ�������Σ������޷��������ͱ��ǵ�ͷ��" + bang_bad["name"] + "�����졣\n");
        set("title","С����ͷ��"NOR);
        set("nickname",HIY"����̫��"NOR);
        set("per",29);
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



