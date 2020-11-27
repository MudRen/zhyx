// murenqing.c

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("������", ({ "mu renqing", "mu", "renqing" }));
	set("title", HIY "ȭ����˫" NOR);

	set("gender", "����");
	set("attitude", "peaceful");
	set("shen_type", 1);

	set("age", 56);

	set("str", 33);
	set("int", 36);
	set("con", 31);
	set("dex", 34);

	set("qi", 6000);
	set("max_qi", 5000);
	set("jing", 3000);
	set("max_jing", 3000);
	set("neili", 7200);
	set("max_neili", 7200);
	set("jiali", 150);

	set("combat_exp", 24000000);
	set("score", 10000000);

	set_skill("cuff", 570);
	set_skill("force", 570);
	set_skill("sword", 580);
	set_skill("dodge", 580);
	set_skill("parry", 570);
	set_skill("strike", 570);
	set_skill("zixia-shengong", 570);
	set_skill("poyu-quan", 570);
	set_skill("huashan-sword", 580);
	set_skill("hunyuan-zhang", 570);
        set_skill("feiyan-huixiang", 580);
	set_skill("literate", 120);

	prepare_skill("cuff", "poyu-quan");
	prepare_skill("strike", "hunyuan-zhang");

	map_skill("cuff", "poyu-quan");
	map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry", "huashan-sword");
	map_skill("sword", "huashan-sword");
	map_skill("strike", "hunyuan-zhang");

	create_family("��ɽ��", 18, "����");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "strike.wuji" :),
		(: perform_action, "cuff.poshi" :),
		(: perform_action, "sword.jianzhang" :),
		(: perform_action, "sword.sanxian" :),
		(: exert_function, "recover" :),
	}));

	setup();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/changjian")->wield();
}
