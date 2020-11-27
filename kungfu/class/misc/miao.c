// miao.c
#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("������", ({ "miao renlong", "miao" }));
	set("long",  "��������ԭ��ҵ�ǰ����\n");
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

        set_skill("force", 560);
        set_skill("miaojia-neigong", 560);
        set_skill("dodge", 540);
        set_skill("chaoyang-fengwu", 540);
        set_skill("sword", 560);
        set_skill("suqin-beijian", 560);
        set_skill("baxian-jian", 560);
        set_skill("tianlong-jian", 560);
        set_skill("miaojia-jian", 560);
        set_skill("blade", 540);
        set_skill("hujia-daofa", 540);
        set_skill("strike", 560);
        set_skill("miaojia-zhang", 560);
        set_skill("chongtian-zhang", 560);
        set_skill("claw", 560);
        set_skill("panlong-zhao", 560);
        set_skill("da-qinna", 540);
        set_skill("xiao-qinna", 540);
        set_skill("unarmed", 540);
        set_skill("pobei-tui", 540);
        set_skill("parry", 560);
        set_skill("literate", 240);
        set_skill("martial-cognize", 260);

        map_skill("force", "miaojia-neigong");
        map_skill("dodge", "chaoyang-fengwu");
        map_skill("sword", "miaojia-jian");
        map_skill("blade", "hujia-daofa");
        map_skill("parry", "tianlong-jian");
        map_skill("strike", "chongtian-zhang");
        map_skill("claw", "panlong-zhao");
        map_skill("unarmed", "pobei-tui");

        prepare_skill("claw", "panlong-zhao");
        prepare_skill("strike", "chongtian-zhang");

        create_family("��ԭ���", 0, "ǰ��");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
	        (: perform_action, "sword.zhai" :),
	        (: perform_action, "sword.zhu" :),
	        (: perform_action, "sword.jian" :),
	        (: perform_action, "sword.gan" :),
	        (: perform_action, "strike.zhan" :),
	        (: perform_action, "claw.tan" :),
		(: exert_function, "recover" :),
	}));

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang/obj/whiterobe")->wear();
}
