// bula and mon@xyj
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>

// here should be this NPC specific skills.

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;
       me->set_skill("force", j+random(15));
        me->set_skill("huntian-qigong", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("feiyan-zoubi", j+random(15));
        me->set_skill("staff", j+random(15));
        me->set_skill("dagou-bang", j+random(15));
        me->set_skill("strike", j+random(15));
        me->set_skill("xianglong-zhang", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("martial-cognize", j+random(15));

        map_skill("force", "huntian-qigong");
        map_skill("parry", "dagou-bang");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("staff", "dagou-bang");
        map_skill("strike", "xianglong-zhang");

        prepare_skill("strike", "xianglong-zhang");

        set("chat_chance_combat", 80);

        set("class", "begger");

        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

