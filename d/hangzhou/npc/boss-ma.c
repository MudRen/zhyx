
#include <ansi.h>

inherit NPC;

#define PLACE "hz"     //����
#define TYPE  "bad"    //�׵�
#define WAIT_TIME 60    //��ɲ�������ķ�ʡʱ��

mapping bang_bad = ([
        "name" : "С����",
        "id"   : "xdh",
        "place": "hz",
        "boss" : "����",
        "place_name" : "����",
]);

void create()
{
        set_name("����", ({ "ma liu", "ma" }));
        set("gender", "����");
        set("age", 29);
        set("long", "�����Ǳ��صĵ�ͷ����֯" + bang_bad["name"] + "��ͷ�ӡ�\n");
        set("nickname",HIY"�޶���"NOR);
        set("title","С���Ẽ�ݷֶ�ͷ��");
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

#include "boss_bad.h"

