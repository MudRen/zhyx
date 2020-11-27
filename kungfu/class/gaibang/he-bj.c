// gaibang npc code

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("�β���", ({"he bujing", "he", "bujing"}));
	set("title", "ؤ���ߴ�����");
	set("gender", "����");
	set("age", 30);
	set("long", 
		"����λ������������ͷ�����ؤ���ߴ����ӡ�\n");
	set("attitude", "heroism");
	set("class", "beggar");
	set("str", 28);
	set("int", 22);
	set("con", 24);
	set("dex", 23);
    set("rank", 7);

	set("qi", 850);
	set("max_qi", 850);
	set("max_jing", 420);
	set("neili", 1800);
	set("max_neili", 1800);
	set("jiali", 35);
	
	set("combat_exp", 270000);
	
	set_skill("force", 125);
	set_skill("jiaohua-neigong", 125);
	set_skill("unarmed", 120);
	set_skill("changquan", 120);
	set_skill("dodge", 110);
	set_skill("feiyan-zoubi", 110);
	set_skill("parry", 120);
	set_skill("begging", 60);
	set_skill("stealing", 50);
	
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

		command("say ��ܰ���ܰɣ� ���������ðɣ��Ҿ��������ˣ�");
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
