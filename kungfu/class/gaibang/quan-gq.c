// gaibang npc code

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("ȫ����", ({"quan guanqing", "quan", "guanqing"}));
        set("title", "ؤ��˴�����");
        set("gender", "����");
        set("age", 35);
        set("long", 
                "����λ��Ĭ����ȴ�����ļƵ�������ؤ��˴����ӡ�\n");
        set("attitude", "peaceful");
        set("class", "beggar");
        set("str", 25);
        set("int", 32);
        set("con", 28);
        set("dex", 27);

        set("max_qi", 1200);
        set("max_jing", 1200);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 40);
        
        set("combat_exp", 500000);
        
        set_skill("force", 150); 
        set_skill("jiaohua-neigong", 150); 
        set_skill("unarmed", 160); 
        set_skill("changquan", 160); 
        set_skill("dodge", 170); 
        set_skill("feiyan-zoubi", 170); 
        set_skill("parry", 160); 
        set_skill("shexing-diaoshou",160);
        set_skill("hand",160);
        set_skill("staff", 150); 
        set_skill("begging", 80); 
        set_skill("training", 120);
        
        map_skill("force", "jiaohua-neigong");
        map_skill("unarmed", "changquan");
       map_skill("hand","shexing-diaoshou");
        map_skill("dodge", "feiyan-zoubi");
        
        create_family("ؤ��", 19, "����");
        setup();
        carry_object("/d/gaibang/obj/budai")->set_amount(7);
        carry_object("/d/gaibang/obj/budai")->wear();
}

void attempt_apprentice(object ob)
{
        if( ob->query("combat_exp") < 30000 ) return;

        if (ob->query("class")=="bonze") {
                if (ob->query("gender")=="Ů��")
                        command ("say ʦ̫���ǳ����ˣ���ô���ڱ������л����أ�");
                return;
        }

        if( ob->query("family/family_name") != "ؤ��" ) 
        {
                if( ob->query("rank") > 1 ) {
                        command("say ����������Ϊ�ȣ����ݲ�����������������ļһ\n");
                        return;
                }

                command("say �ðɣ��Ҿ��������ˣ�");
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
