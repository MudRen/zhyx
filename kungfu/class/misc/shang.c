// mingjiao.c
#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("����", ({ "lao pu", "pu" }));
	set("long",  "�����̼ұ��Ļ������͡�\n");
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
	
        set_skill("force", 540);
        set_skill("nei-bagua", 540);
        set_skill("parry", 520);
        set_skill("wai-bagua", 520);
        set_skill("dodge", 500);
        set_skill("bagua-bu", 500);
        set_skill("unarmed", 500);
        set_skill("tan-tui", 500);
        set_skill("strike", 540);
        set_skill("bagua-zhang", 540);
        set_skill("cuff", 500);
        set_skill("bagua-quan", 500);
        set_skill("blade", 540);
        set_skill("bagua-dao", 540);
        set_skill("literate", 540);
        set_skill("martial-cognize", 520);

        map_skill("unarmed", "tan-tui");
        map_skill("dodge", "bagua-bu");
        map_skill("force", "nei-bagua");
        map_skill("strike", "bagua-zhang");
        map_skill("blade", "bagua-dao");
        map_skill("cuff", "bagua-quan");
        map_skill("parry", "wai-bagua");
        map_skill("throwing", "jinbiao-jue");

        prepare_skill("cuff", "bagua-quan");
        prepare_skill("strike", "bagua-zhang");

        create_family("�̼ұ�", 0, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.mang" :),
                (: perform_action, "blade.sha" :),
                (: perform_action, "strike.ding" :),
                (: perform_action, "cuff.gua" :),
                (: exert_function, "recover" :),
        }) );

	setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
