// laonu.c ��ū

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("��ū", ({ "lao nu", "laonu" }));
	set("long",  "������ȥ�׷��Բԣ�һ�����˴�磬������������ӡ�\n");
	set("gender", "����");
	set("age", 72);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 32);
	set("int", 33);
	set("con", 38);
	set("dex", 32);
	
	set("max_qi", 6000);
	set("max_jing", 3000);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 10);
	set("combat_exp", 25000000);
	set("score", 10000000);

        set_skill("force", 560);
        set_skill("wuzheng-xinfa", 540);
        set_skill("xuantian-wujigong", 560);
        set_skill("dodge", 560);
        set_skill("meihua-zhuang", 560);
        set_skill("parry", 560);
        set_skill("sword", 560);
        set_skill("unarmed", 560);
        set_skill("qixian-wuxingjian", 560);
        set_skill("cuff", 540);
        set_skill("zuiquan-sanda", 540);
        set_skill("claw", 500);
        set_skill("longzhua-gong", 500);
        set_skill("strike", 540);
        set_skill("qingmang-zhang", 540);
        set_skill("literate", 240);
        set_skill("buddhism", 150);
        set_skill("tanqin-jifa", 300);
        set_skill("guangling-san", 300);
        set_skill("qingxin-pushan", 300);
        set_skill("martial-cognize", 540);

        map_skill("force", "xuantian-wujigong");
        map_skill("dodge", "meihua-zhuang");
        map_skill("parry", "qixian-wuxingjian");
        map_skill("sword", "qixian-wuxingjian");
        map_skill("unarmed", "qixian-wuxingjian");
        map_skill("strike", "qingmang-zhang");
        map_skill("cuff", "zuiquan-sanda");
        map_skill("claw", "longzhua-gong");
        map_skill("tanqin-jifa", "guangling-san");

        prepare_skill("unarmed", "qixian-wuxingjian");

	create_family("÷ׯ", 0, "��ū");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
                (: perform_action, "unarmed.yin" :),
                (: perform_action, "unarmed.shan" :),
		(: perform_action, "unarmed.zhu" :),
		(: exert_function, "recover" :),
	}));

	setup();
	carry_object("/clone/misc/cloth")->wear();
}
