// liuqiushui.c

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("����ˮ", ({ "li qiushui", "li" }));
	set("long",  "����̬��ӯ���������ֻ����������һ����ɴ���������С�\n");
	set("gender", "Ů��");
	set("age", 88);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 34);
	set("int", 39);
	set("con", 38);
	set("dex", 37);
	
	set("max_qi", 6000);
	set("max_jing", 3000);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 150);
	set("combat_exp", 25000000);
	set("score", 10000000);

	set_skill("force", 570);
        set_skill("xiaowuxiang", 570);
	set_skill("dodge", 570);
	set_skill("lingbo-weibu", 570);
	set_skill("liuyang-zhang", 540);
	set_skill("parry", 570);
	set_skill("zhemei-shou", 540);
	set_skill("hand", 540);
        set_skill("strike", 540);
	set_skill("literate", 500);
	set_skill("medical", 590);
	set_skill("xiaoyao-qixue", 590);

	map_skill("force", "xiaowuxiang");
	map_skill("dodge", "lingbo-weibu");
	map_skill("hand", "zhemei-shou");
	map_skill("strike", "liuyang-zhang");
	map_skill("parry", "zhemei-shou");

	prepare_skill("hand","zhemei-shou");
	prepare_skill("strike","liuyang-zhang");

	create_family("��ң��", 0, "ǰ��");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "hand.jiubu" :),
		(: perform_action, "strike.jiutian" :),
		(: perform_action, "dodge.lingbo" :),
		(: exert_function, "recover" :),
	}));

	setup();
	carry_object("/clone/misc/cloth")->wear();
}
