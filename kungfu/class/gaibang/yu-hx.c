// gaibang npc code

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("�����", ({"yu hongxing", "yu", "hongxing"}));
        set("title", "ؤ��˴�����");
        set("gender", "����");
        set("age", 30);
        set("long", 
                "����λЦ���е�ؤ��˴����ӣ����Զ��ǣ����С���á�\n");
        set("attitude", "peaceful");
         set("rank", 8);
        set("str", 22);
        set("int", 30);
        set("con", 24);
        set("dex", 22);

        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 530);
        set("max_jing", 530);
        set("neili", 1800);
        set("max_neili", 1800);
        set("jiali", 45);
        
        set("combat_exp", 550000);
        
        set_skill("force", 150); 
        set_skill("jiaohua-neigong", 150); 
        set_skill("unarmed", 140); 
        set_skill("changquan", 140); 
        set_skill("dodge", 140); 
        set_skill("feiyan-zoubi", 140); 
        set_skill("parry", 140); 
        set_skill("begging", 100); 
        set_skill("stealing", 30); 
        set_skill("checking", 80); 
        
        map_skill("force", "jiaohua-neigong");
        map_skill("unarmed", "changquan");
        map_skill("dodge", "feiyan-zoubi");
        
        create_family("ؤ��", 19, "����");
        setup();

        carry_object("/d/gaibang/obj/budai")->set_amount(7);
        carry_object("/d/gaibang/obj/budai")->wear();
//      carry_object("/clone/weapon/gangdao")->wield();
}

void attempt_apprentice(object ob)
{
        if (ob->query("class")=="bonze") {
                if (ob->query("gender")=="Ů��")
                        command ("say ʦ̫���ǳ����ˣ���ô���ڱ������л����أ�");
                return;
        }

        if( ob->query("int") < 25 ) return;

        if( ob->query("family/family_name") != "ؤ��" )
        {
                if( ob->query("rank") > 1 ) {
                        command("say ����������Ϊ�ȣ����ݲ�����������������ļһ\n");
                        return;
                }

                command("say �����������Ϊ����ֻ���߹������˼Һ��Ҳ��ر���Щ����ͽ����");
                command("say ��Ҷ�ҪΪ��Զ���밡��");
                ob->set("rank", 1); 
                command("recruit " + ob->query("id"));
                ob->set("title", "ؤ��һ������");
        } 
        else
        {
                ob->set_temp("title", ob->query("title"));
                command("recruit " + ob->query("id"));
                ob->set("title", ob->query_temp("title"));
                ob->delete_temp("title");
        }
}

#include "/kungfu/class/gaibang/promote.h"

