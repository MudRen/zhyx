
#include <ansi.h>

inherit NPC;

#define PLACE "bjw"     //����
#define TYPE  "good"    //�׵�
#define WAIT_TIME 60    //��ɲ�������ķ�ʡʱ��

mapping bang_good = ([
        "name" : "�޼���",
        "id"   : "wjb",
        "place": "bjw",
        "boss" : "�Ӱ���",
        
]);

void create()
{
        set_name("�Ӱ���", ({ "zhong baixiong", "zhong" }));
        set("gender", "����");
        set("age", 42);
        set("long", "�����Ǵ����������Ӱ����Ӵ�����\n");
        set("nickname",HIY"������"NOR);
        set("title","�޼��ﱱ�����Ƿֶ�");
        set("per",23);
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

