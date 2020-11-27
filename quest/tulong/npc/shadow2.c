#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("ŷ����--Ӱ", ({ "ouyang feng-shadow", "shadow" }));
        set("long", "���ǰ���ɽׯ�����ųơ���������ŷ���档\n"
                   +"����ϰ���������澭���߻���ħ���ѱ�þ�\n"
                   +"����ң�������ͷɢ��������������Ҳ����\n"
                   +"�����ء�\n");
        set("title", "����ɽׯ��");
        set("gender", "����");
        set("age", 53);
        set("nickname", HIR "����" NOR);
        set("shen_type",-1);
        set("shen", -150000);
        set("attitude", "peaceful");

        set("str", 130);
        set("int", 129);
        set("con", 130);
        set("dex", 128);

        set("qi", 251100);
        set("max_qi", 251100);
        set("jing", 90111);
        set("max_jing", 91100);
        set("neili", 20100);
        set("max_neili", 20100);
        set("jiali", 550);

        set("combat_exp", 151100000);
        set("score", 20001100);

        set_skill("force", 2110);
        set_skill("unarmed", 1510);
        set_skill("dodge", 1810);
        set_skill("parry", 1810);
        set_skill("hand",1710);
        set_skill("training",1510);
        set_skill("staff", 1810);
        set_skill("hamagong", 2010);
        set_skill("chanchu-bufa", 1810);
        set_skill("shexing-diaoshou", 1810);
        set_skill("lingshe-zhangfa", 1810);

        map_skill("force", "hamagong");
        map_skill("dodge", "chanchu-bufa");
        map_skill("unarmed", "shexing-diaoshou");
        map_skill("hand", "shexing-diaoshou");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("staff", "lingshe-zhangfa"); 
        set("chat_chance_combat", 60);  
        set("chat_msg_combat", ({ 
               (: exert_function, "recover" :),
                (: exert_function, "reserve" :),
                (: exert_function, "powerup" :),                (: perform_action, "staff.shoot" :),  
                (: perform_action, "staff.shoot" :), 
                (: perform_action, "staff.shoot" :), 
                (: perform_action, "staff.shoot" :), 
                (: perform_action, "staff.shoot" :),         }) );

        create_family("����ɽ��",1, "��ɽ��ʦ");
        setup();
    carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/misc/cloth")->wear();
}

int accept_fight(object ob)
{
        ob=this_player();   
        if( !ob->query("fighter") ) {
        command("heihei");
        command("say �ã������ҳ�����ɣ�\n");
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
        ob = new("/quest/tulong/npc/shadow3");
        ob->move(environment(this_object()));
        destruct(this_object());
} 


