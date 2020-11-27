//tiezhang.c �Ϲٽ���
#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("�Ϲٽ���", ({ "shangguan jiannan", "shangguan" }));
	set("long",  "���������ư�ĵ�һ��������\n");
	set("gender", "����");
	set("age", 50);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 37);
	set("int", 32);
	set("con", 35);
	set("dex", 36);
	
	set("max_qi", 6000);
	set("max_jing", 3000);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 10);
	set("combat_exp", 25000000);
	set("score", -10000);

        set_skill("force", 580);
        set_skill("tianlei-shengong", 580);
        set_skill("dodge", 610);
        set_skill("dengping-dushui", 610);
        set_skill("strike", 320);
        set_skill("parry", 580);
        set_skill("tie-zhang", 320);
        set_skill("chuanxin-zhang", 580);
        set_skill("cuff", 580);
        set_skill("tiexian-quan", 580);
        set_skill("unarmed", 580);
        set_skill("blade", 560);
        set_skill("tianlei-dao", 560);
        set_skill("literate", 200);
        set_skill("martial-cognize", 500);

        map_skill("force", "tianlei-shengong");
        map_skill("unarmed", "chuanxin-zhang");
        map_skill("strike", "tie-zhang");
        map_skill("cuff", "tiexian-quan");
        map_skill("parry", "tie-zhang");
        map_skill("dodge", "dengping-dushui");

        prepare_skill("strike", "tie-zhang");

        create_family("���ư�", 0, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.juesha" :),
                (: perform_action, "strike.lei" :),
                (: perform_action, "strike.yin" :),
                (: perform_action, "cuff.kai" :),
                (: perform_action, "unarmed.zhui" :),
                (: exert_function, "recover" :),
        }) );


	setup();
        carry_object("/clone/cloth/baipao")->wear();
}
