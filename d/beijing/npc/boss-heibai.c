// boss-ju.c 
#include <ansi.h>

inherit NPC;

#define PLACE "bje"     //����
#define TYPE  "bad"    //�ڵ�
#define WAIT_TIME 60    //��ɲ�������ķ�ʡʱ��



mapping bang_bad = ([
        "name" : "�ڰ׵�",
        "id"   : "hbd",
        "place": "bje",
        "boss" : "�ڰ��ɾ�",
        "place_name": "�����Ƕ�",
]);

void create()
{
        set_name("�ڰ��ɾ�", ({ "heibai langjun", "heibai","langjun" }));
        set("gender", "����");
        set("age", 32);
        set("long", "����һ������ֵ����ӣ������������Եķ�Ϊ�ڰ����룬�治����" + bang_bad["name"] + "�����졣\n");
        set("title",HIB"��"WHT"��"NOR"��������"NOR);
        set("per",25);
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


