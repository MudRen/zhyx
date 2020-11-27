// bula and mon@xyj
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>

// here should be this NPC specific skills.

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

        set("title",HIW"�ɶ�����"NOR);
	set("gender", "����");
       me->set_skill("force", j+random(15));
        me->set_skill("lengyue-shengong", j+random(15));
        me->set_skill("blade", j+random(15));
        me->set_skill("liuhe-dao", j+random(15));
        me->set_skill("chuangwang-dao", j+random(15));
        me->set_skill("baisheng-daofa", j+random(15));
        me->set_skill("hujia-daofa", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("sixiang-bufa", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("throwing", j+random(15));
        me->set_skill("mantian-xing", j+random(15));
        me->set_skill("strike", j+random(15));
        me->set_skill("liuhe-zhang", j+random(15));
        me->set_skill("chuncan-zhang", j+random(15));
        me->set_skill("cuff", j+random(15));
        me->set_skill("hua-quan", j+random(15));
        me->set_skill("hujia-quan", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("sword", j+random(15));
        me->set_skill("martial-cognize", j+random(15));

        map_skill("force", "lengyue-shengong");
        map_skill("blade", "hujia-daofa");
        map_skill("dodge", "sixiang-bufa");
        map_skill("parry", "hujia-daofa");
        map_skill("throwing", "mantian-xing");
        map_skill("strike", "chuncan-zhang");
        map_skill("cuff", "hujia-quan");

        prepare_skill("strike", "chuncan-zhang");
        prepare_skill("cuff",   "hujia-quan");

        create_family("�������", 7, "����");

        set("chat_chance_combat", 120);
     
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}
