#include <ansi.h>

inherit NPC;

void create()
{
        set_name("Ѫ������--��", ({ "xuedao laozu-shadow","shadow" }));
        set("long",@LONG
���������Ż��ۣ���ͼ��ϣ���ͷ���������϶������ơ�������Ѫ���ŵ��Ĵ����š�
������ϸһ�����ƺ����������ˡ�
LONG
        );
        set("title",HIR"Ѫ���ŵ��Ĵ�����"NOR);
        set("gender", "����");
        set("age", 85);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 130);
        set("int", 130);
        set("con", 130);
        set("dex", 130);
        set("max_qi", 311000);
        set("max_jing", 101100);
        set("neili", 20100);
        set("max_neili", 20100);
        set("jiali", 50);
        set("combat_exp", 180011000);
        set("score", 18110000);

        set_skill("lamaism", 1150);
        set_skill("literate", 1180);
        set_skill("force", 1180);
        set_skill("parry", 1180);
        set_skill("blade", 1180);
        set_skill("sword", 1120);
        set_skill("dodge", 1180);
        set_skill("longxiang", 1180);
        set_skill("shenkong-xing", 1180);
        set_skill("hand", 1180);
        set_skill("dashou-yin", 1180);
        set_skill("mingwang-jian", 1120);
        set_skill("xuedao-daofa", 2100);

        map_skill("force", "longxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("parry", "xuedao-daofa");
        map_skill("blade", "xuedao-daofa");
        map_skill("sword", "mingwang-jian");
        prepare_skill("hand","dashou-yin");        
        set("chat_chance_combat", 50);  
        set("chat_msg_combat", ({
                (: perform_action, "blade.shendao" :), 
                (: perform_action, "blade.shendao" :),
                (: perform_action, "blade.shendao" :),
                (: perform_action, "blade.shendao" :),
                (: perform_action, "blade.shendao" :),
        }) );

        create_family("ѩɽ��", 4, "����");
        set("class", "bonze");

        setup();
        carry_object("/clone/weapon/blade.c")->wield();

} 

int accept_fight(object ob)
{
        ob=this_player();   
        if( !ob->query("fighter") ) {        command("grin");        command("say �ã����������ˣ�\n");
        ob->set("fighter",1);  
        ob->set_temp("m_success/��Ӱ",1);  
        remove_call_out("kill_ob");
        call_out("kill_ob", 1, ob);
        return 1;
        }
        else
        write(ob->query("name")+"�����Ѿ��Ϲ����ˣ�\n");     }
void die()
{
        object ob;        message_vision("\n$Nһ�Σ���Ϊһ��������ʧ�ˡ�\n", this_object());
        ob = new("/quest/tulong/npc/shadow2");
        ob->move(environment(this_object()));
        destruct(this_object());
} 

