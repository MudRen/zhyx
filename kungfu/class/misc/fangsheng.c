// fangsheng.c

inherit "/inherit/char/punisher";

void create()
{
	set_name("����", ({ "fang sheng", "fang" }));
	set("long", "����Ŀ�Ⱥͣ���Ȼ��һ�õ���ɮ��\n");

	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 40);
	set("shen_type", 1);
	set("str", 35);
	set("int", 31);
	set("con", 37);
	set("dex", 32);
	set("max_qi", 6000);
	set("max_jing", 3000);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 150);
	set("combat_exp", 24500000);
	set("score", 10000000);

	set_skill("force", 570);
	set_skill("hunyuan-yiqi", 570);
	set_skill("dodge", 560);
	set_skill("shaolin-shenfa", 560);
	set_skill("finger", 570);
	set_skill("strike", 570);
	set_skill("hand", 560);
	set_skill("claw", 560);
	set_skill("parry", 560);
	set_skill("nianhua-zhi", 570);
	set_skill("sanhua-zhang", 570);
	set_skill("fengyun-shou", 560);
	set_skill("longzhua-gong", 560);
	set_skill("buddhism", 260);
	set_skill("literate", 120);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("finger", "nianhua-zhi");
	map_skill("strike", "sanhua-zhang");
	map_skill("hand", "fengyun-shou");
	map_skill("claw", "longzhua-gong");
	map_skill("parry", "nianhua-zhi");

	prepare_skill("finger", "nianhua-zhi");
	prepare_skill("strike", "sanhua-zhang");

	create_family("������", 0, "��ɮ");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "strike.san" :),
		(: perform_action, "hand.qinna" :),
		(: perform_action, "claw.zhua" :),
		(: exert_function, "recover" :),
	}));

	setup();
        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}
