#include <ansi.h>


inherit NPC;

#define PLACE "sz"     //����
#define TYPE  "good"    //�׵�
#define WAIT_TIME 60    //��ɲ�������ķ�ʡʱ��

mapping bang_good = ([
        "name" : "������",
        "id"   : "zsh",
        "place": "sz",
        "boss" : "�δ�����",
]);

void create()
{
        set_name("�δ�����", ({ "song xiansheng", "song" }));
        set("gender", "����");
        set("age", 46);
        set("long", "�����Ƕ���������" + bang_good["name"] + "�����ܡ�\n");
        set("nickname",HIY"����Ǭ��"NOR);
        set("title","����������");
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

