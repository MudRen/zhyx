// laoseng.c ѩɽ��ɮ

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("ѩɽ��ɮ", ({ "lao seng", "seng" }));
	set("long",  "����һ��ѩɽ�ɵĴ�磬���Ʈ�ݣ�һ�����ǵõ���ɮ��\n");
	set("gender", "����");
	set("age", 62);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 33);
	set("int", 36);
	set("con", 34);
	set("dex", 33);
	
	set("max_qi", 6000);
	set("max_jing", 3000);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 150);
	set("combat_exp", 25000000);
	set("score", 10000000);

        set_skill("force", 570);
        set_skill("xiaowuxiang", 570);
        set_skill("mizong-neigong", 570);
        set_skill("dodge", 540);
        set_skill("shenkong-xing", 540);
        set_skill("parry", 570);
        set_skill("sword", 520);
        set_skill("mingwang-jian", 520);
        set_skill("lamaism", 550);
        set_skill("literate", 520);
        set_skill("strike", 570 );
        set_skill("huoyan-dao", 570);
	set_skill("cuff", 560);
	set_skill("yujiamu-quan", 560);
	set_skill("hand", 570);
	set_skill("dashou-yin", 570);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "mingwang-jian");
        map_skill("sword", "mingwang-jian");
        map_skill("strike","huoyan-dao");
	map_skill("cuff", "yujiamu-quan");

        prepare_skill("strike", "huoyan-dao");
	prepare_skill("hand", "dashou-yin");

	create_family("������", 0, "��ɮ");
        set("class", "bonze");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "sword.bei" :),
		(: perform_action, "strike.fen" :),
		(: perform_action, "cuff.chen" :),
		(: exert_function, "recover" :),
	}));

	setup();
	carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/xueshan/obj/y-jiasha")->wear();
}
