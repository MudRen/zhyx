// bula and mon@xyj
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>

// here should be this NPC specific skills.

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

        me->set("title",HIC"������"NOR);

        me->set_skill("force", j+random(15));
        me->set_skill("hunyuan-yiqi", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("shaolin-shenfa", j+random(15));
        me->set_skill("sword", j+random(15));
        me->set_skill("damo-jian", j+random(15));
        me->set_skill("finger", j+random(15));
        me->set_skill("nianhua-zhi", j+random(15));
        me->set_skill("strike", j+random(15));
        me->set_skill("sanhua-zhang", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("martial-cognize", j+random(15));
        me->set_skill("buddhism", j+random(15));

        map_skill("parry", "damo-jian");
        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("sword", "damo-jian");
        map_skill("finger", "nianhua-zhi");
        map_skill("strike", "sanhua-zhang");

        prepare_skill("finger", "nianhua-zhi");
        prepare_skill("strike", "sanhua-zhang");

        set("chat_chance_combat", 100);
        set("class", "bonze");

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}
