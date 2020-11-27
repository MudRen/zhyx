// guoxiang.c

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("����", ({ "guo xiang", "guo" }));
        set("long", "���Ƕ����ɵĿ�ɽ��ʦ��\n");
        set("nickname", HIM "С��а" NOR);
        set("gender", "Ů��");
        set("age", 54);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "bonze");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.mie" :),
                (: perform_action, "strike.bashi" :),
                (: exert_function, "recover" :),
        }));

        set("str", 59);
        set("int", 39);
        set("con", 37);
        set("dex", 37);

        set("max_qi", 6000);
        set("max_jing", 3000);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jingli", 150);

        set("combat_exp", 24000000);
	set("score", 10000000);

        set_skill("force", 570);
        set_skill("dodge", 570);
        set_skill("finger", 570);
        set_skill("parry", 570);
        set_skill("strike", 570);
        set_skill("sword", 570);
        set_skill("literate", 250);
        set_skill("mahayana", 250);
        set_skill("buddhism", 250);
        set_skill("jinding-zhang", 570);
        set_skill("tiangang-zhi", 570);
        set_skill("huifeng-jian", 570);
        set_skill("zhutian-bu", 570);
        set_skill("emei-xinfa", 570);
        set_skill("linji-zhuang", 570);

        map_skill("force","linji-zhuang");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("sword","huifeng-jian");
        map_skill("parry","huifeng-jian");

	prepare_skill("strike", "jinding-zhang");
	prepare_skill("finger","tiangang-zhi");

        create_family("������", 1, "��ɽ��ʦ");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "strike.bashi" :),
		(: perform_action, "finger.ling" :),
		(: perform_action, "sword.jue" :),
		(: perform_action, "sword.mie" :),
		(: exert_function, "recover" :),
	}));

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/city/obj/cloth.c")->wear();
}
