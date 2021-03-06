// taogu.c 桃谷老仙

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("桃谷老仙", ({ "taogu laoxian", "laoxian" }));
	set("long",  "他据说是桃谷六仙的长辈，出身于东海桃花岛。\n");
	set("gender", "男性");
	set("age", 58);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 35);
	set("int", 31);
	set("con", 32);
	set("dex", 31);
	
	set("max_qi", 6000);
	set("max_jing", 3000);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 150);
	set("combat_exp", 25000000);
	set("score", 10000000);

	set_skill("force", 580);
	set_skill("bibo-shengong", 580);
	set_skill("dodge", 550);
	set_skill("anying-fuxiang", 550);
	set_skill("finger", 570);
	set_skill("tanzhi-shentong", 570);
	set_skill("hand", 570);
	set_skill("lanhua-shou", 570);
	set_skill("parry", 570);
	set_skill("sword", 570);
	set_skill("yuxiao-jian", 570);
  	set_skill("qimen-wuxing", 250);
	set_skill("literate", 100);

	map_skill("force", "bibo-shengong");
	map_skill("dodge", "anying-fuxiang");
	map_skill("finger", "tanzhi-shentong");
	map_skill("parry", "tanzhi-shentong");
	map_skill("sword", "yuxiao-jian");
	map_skill("hand", "lanhua-shou");

	prepare_skill("finger", "tanzhi-shentong");
	prepare_skill("hand", "lanhua-shou");

	create_family("桃花岛", 0, "前辈");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "sword.bihai" :),
		(: perform_action, "sword.tianwai" :),
		(: perform_action, "hand.fuxue" :),
		(: perform_action, "finger.jinglei" :),
		(: exert_function, "recover" :),
	}));

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang/obj/whiterobe")->wear();
}
