// xiaoxian.c ����С��

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("����С��", ({ "xingxiu xiaoxian", "xiaoxian" }));
	set("long",  "����һ��СŮ��������ȥ��Ͳ���\n");
	set("gender", "Ů��");
	set("age", 24);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 30);
	set("int", 36);
	set("con", 38);
	set("dex", 33);
	
	set("max_qi", 6000);
	set("max_jing", 3000);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 150);
	set("combat_exp", 25000000);
	set("score", 10000000);

        set_skill("force", 520);
        set_skill("huagong-dafa", 520);
        set_skill("guixi-gong", 500);
        set_skill("throwing", 510);
        set_skill("feixing-shu", 510);
        set_skill("dodge", 480);
        set_skill("zhaixinggong", 480);
        set_skill("strike", 485);
        set_skill("chousui-zhang", 485);
        set_skill("claw", 480);
        set_skill("sanyin-wugongzhao", 480);
        set_skill("whip", 480);
        set_skill("chanhun-suo", 480);
        set_skill("parry", 485);
        set_skill("staff", 490);
        set_skill("poison", 300);
        set_skill("tianshan-zhang", 490);
        set_skill("literate", 120);

        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixinggong");
        map_skill("strike", "chousui-zhang");
        map_skill("claw", "sanyin-wugongzhao");
        map_skill("whip", "chanhun-suo");
        map_skill("parry", "tianshan-zhang");
        map_skill("staff", "tianshan-zhang");

        prepare_skill("strike", "chousui-zhang");
        prepare_skill("claw", "sanyin-wugongzhao");

	create_family("������", 0, "����");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "staff.fugu" :),
		(: perform_action, "staff.xue" :),
		(: perform_action, "claw.zhua" :),
		(: exert_function, "recover" :),
	}));

	setup();
	carry_object("/clone/weapon/gangzhang")->wield();
	carry_object("/clone/misc/cloth")->wear();
}
