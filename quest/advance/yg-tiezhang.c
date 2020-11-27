// bula and mon@xyj
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";
#include <ansi.h>

// here should be this NPC specific skills.

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

        set("title",HIG"����ˮ��Ʈ"NOR);
        me->set_skill("force", j+random(15));
        me->set_skill("tianlei-shengong", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("dengping-dushui", j+random(15));
        me->set_skill("strike", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("tie-zhang", j+random(15));
        me->set_skill("feilong-zhang", j+random(15));
        me->set_skill("staff", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("martial-cognize", j+random(15));

        map_skill("force", "tianlei-shengong");
        map_skill("strike", "tie-zhang");
        map_skill("parry", "tie-zhang");
        map_skill("dodge", "dengping-dushui");
        map_skill("staff", "feilong-zhang");

        prepare_skill("strike", "tie-zhang");

        set("chat_chance_combat", 80);


        carry_object("/clone/misc/cloth")->wear();
}
