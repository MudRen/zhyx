// gaibang npc code

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("何不净", ({"he bujing", "he", "bujing"}));
	set("title", "丐帮七袋弟子");
	set("gender", "男性");
	set("age", 30);
	set("long", 
		"这是位衣著邋塌，蓬头垢面的丐帮七袋弟子。\n");
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
	
	create_family("丐帮", 19, "弟子");
	setup();

	carry_object("/d/gaibang/obj/budai")->set_amount(6);
	carry_object("/d/gaibang/obj/budai")->wear();
}

void attempt_apprentice(object ob)
{
	if( ob->query("combat_exp") < 30000 ) return;

        if (ob->query("class")=="bonze") {
                if (ob->query("gender")=="女性")
                        command ("say 师太是是出家人，怎么能在本帮做叫化子呢？");
                return;
        }

	if( ob->query("family/family_name") != "丐帮" ) 
	{
	        if( ob->query("rank") > 1 ) {
       	         	command("say 本帮以忠义为先，可容不下你这种无信无义的家伙！\n");
                	return;
        	}

		command("say 你很爱打架吧？ 哈哈哈，好吧，我就收下你了！");
		ob->set("rank", 1); 
		command("recruit " + ob->query("id"));
		ob->set("title", "丐帮一袋弟子");
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
