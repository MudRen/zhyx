// gaibang npc code

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("���Ϊ", ({"ma juwei", "ma", "juwei"}));
        set("title", "ؤ���ߴ�����");
        set("gender", "����");
        set("age", 35);
        set("long", 
                "����λ���վ�ǿ��ȴ��Ĭ���Ե�ؤ���ߴ����ӡ�\n");
        set("attitude", "peaceful");
        set("rank",7);
        set("str", 25);
        set("int", 22);
        set("con", 25);
        set("dex", 30);

        set("qi", 800);
        set("max_qi", 800);
        set("jing", 350);
        set("max_jing", 350);
        set("neili", 1400);
        set("max_neili", 1400);
        set("jiali", 32);
        
        set("combat_exp", 180000);
        
        set_skill("force", 120);
        set_skill("jiaohua-neigong", 120);
        set_skill("unarmed", 120);
        set_skill("changquan", 120);
        set_skill("dodge", 120);
        set_skill("feiyan-zoubi", 120);
        set_skill("parry", 120);
        set_skill("staff", 120);
        set_skill("begging", 60);

        map_skill("force", "jiaohua-neigong");
        map_skill("unarmed", "changquan");
        map_skill("parry", "changquan");
        map_skill("dodge", "feiyan-zoubi");
        
        create_family("ؤ��", 19, "����");
        setup();

        carry_object("/d/gaibang/obj/budai")->set_amount(6);
        carry_object("/d/gaibang/obj/budai")->wear();
        
}

void attempt_apprentice(object ob)
{
        if (ob->query("class")=="bonze") {
                if (ob->query("gender")=="Ů��")
                        command ("say ʦ̫���ǳ����ˣ���ô���ڱ������л����أ�");
                return;
        }

        if( ob->query("con") < 20 ) return;

        if( ob->query("family/family_name") != "ؤ��" )
        {
                if( ob->query("rank") > 1 ) {
                        command("say ����������Ϊ�ȣ����ݲ�����������������ļһ\n");
                        return;
                }

                command("say �����Ϊʦ����Ҫ���óԿ��׼�����ú�����ؤ����ӣ�");
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

