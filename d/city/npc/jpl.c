#include <ansi.h>

inherit NPC;

void create()
{
        set_name("�����õ�", ({ "jian polan" }));

        set("long", @LONG
����˲����Լ������ã�����Ҳ�������ò�����
LONG
        );

        set("gender", "����" );
        set("age", 30);

        set("combat_exp", 1000);
        set_skill("unarmed", 20); 
        set_skill("parry", 20); 
        set_skill("dodge", 20); 
               
        set_temp("apply/attack", 5); 
        set_temp("apply/defense", 5); 
        set_temp("apply/damage", 5); 
      
        set("attitude", "friendly"); 


        set("chat_chance", 10);
        set("chat_msg", ({
                (: command, "get all" :),
                "�����õ��૵�����ô��Щ����ôû�����ģ�������Ӷ�����\n",
                "�����õ��������������֪��˵Щʲ�ᡣ\n",
                "�����õ�����׽ס�����ϵ�ʭ�ӣ�һ�Ųȵñ��ġ� \n",
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
        }) );

        setup();

        add_money("coin", 50);

}

int accept_object(object me, object obj)
{
        command("smile");
        command("say ��л��λ" + RANK_D->query_respect(me) + "��");
        return 1;
}

int accept_fight(object me)
{
        command("say " + RANK_D->query_respect(me) + "������С������뿪��\n");
        return 0;
}

