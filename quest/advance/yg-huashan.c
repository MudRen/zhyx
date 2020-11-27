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

        set("title",RED"½£ħ"NOR);
        me->set_skill("force", j+random(15));
        me->set_skill("zixia-shengong", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("feiyan-huixiang", j+random(15));
        me->set_skill("sword", j+random(15));
        me->set_skill("huashan-sword", j+random(15));
        me->set_skill("cuff", j+random(15));
        me->set_skill("poyu-quan", j+random(15));
        me->set_skill("strike", j+random(15));
        me->set_skill("hunyuan-zhang", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("martial-cognize", j+random(15));

        map_skill("parry", "huaxian-sword");
        map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("sword", "huashan-sword");
        map_skill("cuff", "poyu-quan");
        map_skill("strike", "hunyuan-zhang");

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("strike", "hunyuan-zhang");

        set("chat_chance_combat", 100);
        set("class", "fighter");

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}
