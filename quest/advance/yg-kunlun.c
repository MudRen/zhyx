// bula and mon@xyj
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>

// here should be this NPC specific skills.

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

        me->set("title",YEL"������ʥ"NOR);
        me->set_skill("force", j+random(15));
        me->set_skill("liangyi-shengong", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("chuanyun-bu", j+random(15));
        me->set_skill("strike", j+random(15));
        me->set_skill("kunlun-zhang", j+random(15));
        me->set_skill("cuff", j+random(15));
        me->set_skill("zhentian-quan", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("sword", j+random(15));
        me->set_skill("zhengliangyi-jian", j+random(15));
        me->set_skill("qiankun-jian", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("martial-cognize", j+random(15));

        map_skill("force", "liangyi-shengong");
        map_skill("dodge", "chuanyun-bu");
        map_skill("parry", "zhengliangyi-jian");
        map_skill("sword", "qiankun-jian");
        map_skill("strike", "kunlun-zhang");
        map_skill("cuff", "zhentian-quan");

        prepare_skill("strike", "kunlun-zhang");
        prepare_skill("cuff", "zhentian-quan");

        set("chat_chance_combat", 80);

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
