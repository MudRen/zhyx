
// boss-ju.c 
#include <ansi.h>

inherit NPC;

#define PLACE "bjw"     //����
#define TYPE  "bad"    //�ڵ�
#define WAIT_TIME 60    //��ɲ�������ķ�ʡʱ��



mapping bang_bad = ([
        "name" : "������",
        "id"   : "xlm",
        "place": "bjw",
        "boss" : "������",
        "place_name": "��������",
]);

void create()
{
        set_name("������", ({ "hu meiniang", "hu","meiniang" }));
        set("gender", "Ů��");
        set("age", 26);
        set("long", "��װ��������ޱȣ�һ˫�۾������˻��ǡ�\n");
        set("title",HIB"�����ű���̳��"NOR);
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


