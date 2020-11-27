//modified by vikee
//2000-12-9 23:34
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>

// here should be this NPC specific skills.

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

        set("title",RED"��ڤʹ��"NOR);
        me->set_skill("parry", j+random(15));
        me->set_skill("xuanming-shengong", j+random(15));
        me->set_skill("force", j+random(15));
        me->set_skill("minggu-xinfa", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("liuying-bu", j+random(15));
        me->set_skill("strike", j+random(15));
        me->set_skill("xuanming-zhang", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("martial-cognize", j+random(15));

        map_skill("dodge", "liuying-bu");
        map_skill("force", "xuanming-shengong");
        map_skill("strike", "xuanming-zhang");
        map_skill("parry", "xuanming-zhang");

        prepare_skill("strike", "xuanming-zhang");

        set("chat_chance_combat", 50);

        carry_object("/clone/misc/cloth")->wear();
}
