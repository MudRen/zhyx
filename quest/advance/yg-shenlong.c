//created by vikee
//2000-12-9 23:35
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

        me->set("title",CYN"��������"NOR);
        me->set_skill("force", j+random(15));
        me->set_skill("shenlong-xinfa", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("yixingbu", j+random(15));
        me->set_skill("hand", j+random(15));
        me->set_skill("shenlong-bashi", j+random(15));
        me->set_skill("strike", j+random(15));
        me->set_skill("huagu-mianzhang", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("staff", j+random(15));
        me->set_skill("sword", j+random(15));
        me->set_skill("shedao-qigong", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("martial-cognize", j+random(15));

        map_skill("force", "shenlong-xinfa");
        map_skill("dodge", "yixingbu");
        map_skill("hand", "shenlong-bashi");
        map_skill("strike", "huagu-mianzhang");
        map_skill("parry", "shedao-qigong");
        map_skill("staff", "shedao-qigong");

        prepare_skill("strike", "huagu-mianzhang");
        prepare_skill("hand", "shenlong-bashi");

        set("chat_chance_combat", 80);

        carry_object("/clone/misc/cloth")->wear();
}

