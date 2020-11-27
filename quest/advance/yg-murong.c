// bula and mon@xyj
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>

// here should be this NPC specific skills.

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

	set("titile", "����Ľ��");
	me->set_skill("force", j+random(15));
	me->set_skill("literate", j+random(15));
	me->set_skill("cuff", j+random(15));
	me->set_skill("sword", j+random(15));
	me->set_skill("blade", j+random(15));
	me->set_skill("dodge", j+random(15));
	me->set_skill("parry", j+random(15));
	me->set_skill("murong-xinfa", j+random(15));
	me->set_skill("douzhuan-xingyi", j+random(15));
	me->set_skill("beidou-xianzong", j+random(15));
	me->set_skill("qixing-quan", j+random(15));
	me->set_skill("murong-jian", j+random(15));
    me->set_skill("martial-cognize", j+random(15));
    me->set_skill("longcheng-shendao", j+random(15));

	map_skill("force", "murong-xinfa");
	map_skill("dodge", "beidou-xianzong");
	map_skill("cuff",  "qixing-quan");
	map_skill("parry", "douzhuan-xingyi");
	map_skill("sword", "murong-jian");
	map_skill("blade", "longcheng-shendao");

        prepare_skill("cuff", "qixing-quan");

	set("chat_chance_combat", 120);

	create_family("Ľ������", 16, "����");

        carry_object("/clone/weapon/gangdao")->wield();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 200);
}