//created by vikee
//2000-12-9 23:35
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>


void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

        me->set("title",HIM"������"NOR);
        me->set_skill("force", j+random(15));
        me->set_skill("beiming-shengong", j+random(15));
        me->set_skill("finger", j+random(15));
        me->set_skill("yiyang-zhi", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("lingbo-weibu", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("chess", j+random(15));
        me->set_skill("buddhism", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("lamaism", j+random(15));
        me->set_skill("jingluo-xue", j+random(15));
        me->set_skill("martial-cognize", j+random(15));

        map_skill("force", "beiming-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("parry", "liumai-shenjian");
        map_skill("finger", "yiyang-zhi");

        prepare_skill("finger", "yiyang-zhi");

        set("chat_chance_combat", 120);
        carry_object("/clone/misc/cloth")->wear();
}