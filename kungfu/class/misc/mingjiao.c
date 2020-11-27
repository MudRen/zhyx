// mingjiao.c
#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("������", ({ "yang dingtian", "yang" }));
	set("long",  "�����ǵ�ǰ�ν��������졣\n");
	set("gender", "����");
	set("age", 85);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 32);
	set("int", 33);
	set("con", 32);
	set("dex", 31);
	
	set("max_qi", 6000);
	set("max_jing", 3000);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 10);
	set("combat_exp", 25000000);
	set("score", 10000000);
	
	set_skill("force", 600);
	set_skill("dodge", 560);
	set_skill("parry", 600);
	set_skill("cuff", 550);
	set_skill("sword", 560);
	set_skill("shenghuo-shengong", 600);
	set_skill("qiankun-danuoyi", 550);
	set_skill("shenghuo-bu", 540);
	set_skill("qishang-quan", 540);
	set_skill("shenghuo-ling", 560);

	map_skill("force", "shenghuo-shengong");
	map_skill("dodge", "qiankun-danuoyi");
	map_skill("cuff", "qishang-quan");
	map_skill("sword", "shenghuo-ling");
	map_skill("parry", "qiankun-danuoyi");

	prepare_skill("cuff", "qishang-quan");

	create_family("����", 0, "����");

	set("chat_chance_combat", 120); 
	set("chat_msg_combat", ({
		(: command("perform sword.hua") :),
		(: command("perform sword.lian") :),
		(: command("perform sword.can") :),
		(: command("perform cuff.shang") :),
		(: command("perform cuff.fei") :),
		(: command("yun recover") :),
	}) );


	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang/obj/whiterobe")->wear();
}
