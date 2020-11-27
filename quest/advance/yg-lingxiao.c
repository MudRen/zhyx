// bula and mon@xyj
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>

// here should be this NPC specific skills.

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

        me->set("title",HIC"����"NOR);
        me->set_skill("force", j+random(15));
        me->set_skill("wuwang-shengong", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("taxue-wuhen", j+random(15));
        me->set_skill("cuff", j+random(15));
        me->set_skill("lingxiao-quan", j+random(15));
        me->set_skill("strike", j+random(15));
        me->set_skill("piaoxu-zhang", j+random(15));
        me->set_skill("sword", j+random(15));
        me->set_skill("xueshan-jian", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("martial-cognize", j+random(15));

        map_skill("force", "wuwang-shengong");
        map_skill("dodge", "taxue-wuhen");
        map_skill("cuff", "lingxiao-quan");
        map_skill("strike", "piaoxu-zhang");
        map_skill("sword", "xueshan-jian");
        map_skill("parry", "xueshan-jian");

        prepare_skill("strike", "piaoxu-zhang");
        prepare_skill("cuff", "lingxiao-quan");

        set("chat_chance_combat", 80);

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
}