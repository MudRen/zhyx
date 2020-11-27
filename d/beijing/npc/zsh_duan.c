//zsh_duan.c

#include <ansi.h>

inherit NPC;

#define PLACE "bje"     //�����ֻ�
#define TYPE  "good"    //�׵�
#define WAIT_TIME 60    //��ɲ�������ķ�ʡʱ��

mapping bang_good = ([ 
        "name" : "������",
        "id"   : "zsh",
        "place": "sz",      //�ܻ�
        "boss" : "�δ�����",
        "place_name" : "����" //�ֻ�
]);

void create()
{
        set_name("����", ({ "duan qing", "duan" }));
        set("gender", "����");
        set("age", 28);
        set("long", "������" + bang_good["name"] + "����" + bang_good["place_name"] + "�ķֻ�᳤��\n");
        set("nickname",HIY"��������"NOR);
        set("title",GRN"�����ᱱ���ֻ�᳤"NOR);
        set("per",28);
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

