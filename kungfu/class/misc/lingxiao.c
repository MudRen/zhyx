// lingxiao.c
#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("������", ({ "lingxiao zi", "zi" }));
	set("long",  "�������������صĽ��ɣ�ƮƮ���ɡ�\n");
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
        set_skill("wuwang-shengong", 600);
        set_skill("dodge", 560);
        set_skill("taxue-wuhen", 560);
        set_skill("cuff", 560);
        set_skill("lingxiao-quan", 560);
        set_skill("strike", 560);
        set_skill("piaoxu-zhang", 560);
        set_skill("sword", 580);
        set_skill("xueshan-jian", 580);
        set_skill("parry", 560);
        set_skill("literate", 250);
        set_skill("martial-cognize", 550);

        map_skill("force", "wuwang-shengong");
        map_skill("dodge", "taxue-wuhen");
        map_skill("cuff", "lingxiao-quan");
        map_skill("strike", "piaoxu-zhang");
        map_skill("sword", "xueshan-jian");
        map_skill("parry", "xueshan-jian");

        prepare_skill("strike", "piaoxu-zhang");
        prepare_skill("cuff", "lingxiao-quan");

        create_family("������", 0, "ǰ��");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.chu" :),
                (: perform_action, "sword.feng" :),
                (: perform_action, "cuff.san" :),
		(: exert_function, "recover" :),
	}));

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang/obj/whiterobe")->wear();
}
