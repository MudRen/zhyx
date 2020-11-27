inherit NPC;
#include <ansi.h>;

void create()
{
        set_name("����Ⱥ--��", ({ "yue buqun shadow", "shadow" }) );
        set("title", "��ɽ������");
        set("nickname", "���ӽ�");
        set("gender", "����");
        set("class", "swordsman");
        set("age", 55);
        set("long",
                "����Ⱥ����ִ�ƻ�ɽ�ɣ��˵���������һ��һ�ĸ��֡�������ǰ���\n"
    +"����Ⱥ���ƺ�������Щ����ʵ�С�\n");
        set("attitude", "peaceful");
        set("str", 126);
        set("con", 130);
        set("dex", 130);
        set("int", 128);

        set("neili", 21400);
        set("max_neili", 21400);
        set("jiali", 330);
        set("max_qi",23000);
        set("max_jing",13200);

        set("combat_exp", 13300000);
        set("shen", -200000);
        set("xunshan", 1);
        set("apprentice_available", 3);

        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :), 
                (: perform_action, "sword.cimu" :),  
                (: perform_action, "sword.cimu" :), 
                (: perform_action, "sword.cimu" :), 
                (: perform_action, "sword.cimu" :), 
                (: perform_action, "sword.cimu" :),         }) );
        set("inquiry", ([
            "����": "Ҫ����أ����ȴ���ҡ�\n",
        ]) );

        set_skill("unarmed", 820);
        set_skill("sword", 850);
        set_skill("force", 850);
        set_skill("parry", 640);
        set_skill("dodge", 820);
        set_skill("literate", 800);
        set_skill("huashan-sword", 860);
        set_skill("zixia-shengong", 850);
        set_skill("huashan-quanfa", 820);
        set_skill("feiyan-huixiang", 820);
        set_skill("pixie-jian",850);

        map_skill("sword", "pixie-jian");
        map_skill("parry", "pixie-jian");
        map_skill("force", "zixia-shengong");
        map_skill("unarmed", "huashan-quanfa");
        map_skill("dodge", "feiyan-huixiang");

        create_family("��ɽ��", 13, "����");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

int accept_fight(object ob)
{
        ob=this_player();   
        if( !ob->query("fighter") ) {
        command("say ���úã��ҿ��ǲ�����������ġ�\n");
        ob->set("fighter",1);  
        ob->set_temp("m_success/��Ӱ",1);  
        remove_call_out("kill_ob");
        call_out("kill_ob", 1, ob);
        return 1;
        }
        else
        write(ob->query("name")+"�����Ѿ��Ϲ����ˣ�\n");
}

void die()
{
        object ob;
        message_vision("\n$Nһ�Σ���Ϊһ��������ʧ�ˡ�\n", this_object());
        ob = new("/quest/tulong/npc/shadow1");
        ob->move(environment(this_object()));
        destruct(this_object());
} 

