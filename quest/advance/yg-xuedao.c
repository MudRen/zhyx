// bula and mon@xyj
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>

// here should be this NPC specific skills.
void set_skills(int j, int level)
{
        object me=this_object();
	object weapon;

        set("title",YEL"Ѫ������"NOR);
        me->set_skill("force", j+random(15));
        me->set_skill("xuedao-dafa", j+random(15));
        me->set_skill("blade", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("shenkong-xing", j+random(15));
        me->set_skill("hand", j+random(15));
        me->set_skill("dashou-yin", j+random(15));
        me->set_skill("cuff", j+random(15));
        me->set_skill("yujiamu-quan", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("lamaism", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("martial-cognize", j+random(15));

        map_skill("force", "xuedao-dafa");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "xuedao-dafa");
        map_skill("blade", "xuedao-dafa");
        map_skill("sword", "mingwang-jian");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

        set("chat_chance_combat", 80);

        set("class", "bonze");

        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
