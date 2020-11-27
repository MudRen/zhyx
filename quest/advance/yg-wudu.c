//bula and mon@xyj
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>

// here should be this NPC specific skills.

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

        set("title",HIY"�嶾����"NOR);
        me->set_skill("force", j+random(15));
        me->set_skill("xiuluo-yinshagong", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("jinshe-youshenbu", j+random(15));
        me->set_skill("strike", j+random(15));
        me->set_skill("tianchan-zhang", j+random(15));
        me->set_skill("claw", j+random(15));
        me->set_skill("wusheng-zhao", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("whip", j+random(15));
        me->set_skill("ruanhong-zhusuo", j+random(15));
        me->set_skill("poison", j+random(15));
        me->set_skill("wudu-qishu", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("martial-cognize", j+random(15));

        map_skill("force", "xiuluo-yinshagong");
        map_skill("dodge", "jinshe-youshenbu");
        map_skill("strike", "tianchan-zhang");
        map_skill("claw", "wusheng-zhao");
        map_skill("parry", "ruanhong-zhusuo");
        map_skill("whip", "ruanhong-zhusuo");
        map_skill("poison", "wudu-qishu");

        prepare_skill("claw", "wusheng-zhao");
        prepare_skill("strike", "tianchan-zhang");

        set("chat_chance_combat", 80);

        carry_object("/clone/weapon/changbian")->wield();
        carry_object("/clone/misc/cloth")->wear();
}