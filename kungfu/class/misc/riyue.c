// riyue.c ������̳���

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("���̳���", ({ "riyue zhanglao", "zhanglao" }));
	set("long",  "������������̵�ʮ����֮һ��\n");
	set("gender", "����");
	set("age", 90);
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
		      
	set_skill("force", 580);
	set_skill("xixing-dafa", 580);
	set_skill("dodge", 550);
	set_skill("feiyan-zoubi", 550);
	set_skill("strike", 570);
        set_skill("guzhuo-zhang", 570);
	set_skill("parry", 570);
	set_skill("sword", 570);
	set_skill("literate", 100);


	map_skill("force", "xixing-dafa");
	map_skill("dodge", "feiyan-zoubi");
	map_skill("parry", "guzhuo-zhang");
	map_skill("strike", "guzhuo-zhang");

        prepare_skill("strike", "guzhuo-zhang");

	create_family("�������", 0, "����");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
                (: perform_action, "strike.zhuo" :),
                (: perform_action, "strike.yu" :),
                (: perform_action, "strike.zhen" :),
		(: exert_function, "recover" :),
	}));

	setup();
	carry_object("/d/wudang/obj/whiterobe")->wear();
}
