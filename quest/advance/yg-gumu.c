// bula and mon@xyj
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>

// here should be this NPC specific skills.

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

        set("title",HIW"��Ĺ����"NOR);
				set("gender", "Ů��");
        me->set_skill("force", j+random(15));
        me->set_skill("yunv-xinjing", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("yunv-shenfa", j+random(15));
        me->set_skill("unarmed", j+random(15));
        me->set_skill("meinv-quan", j+random(15));
        me->set_skill("strike", j+random(15));
        me->set_skill("fireice-strike", j+random(15));
        me->set_skill("tianluo-diwang", j+random(15));
        me->set_skill("throwing", j+random(15));
        me->set_skill("yufeng-zhen", j+random(15));
        me->set_skill("sword", j+random(15));
        me->set_skill("yunv-jian", j+random(15));
        me->set_skill("quanzhen-jian", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("martial-cognize", j+random(15));

        map_skill("force", "yunv-xinjing");
        map_skill("sword", "yunv-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "meinv-quan");
        map_skill("unarmed", "meinv-quan");
        map_skill("strike", "tianluo-diwang");
        map_skill("throwing", "yufeng-zhen");

        prepare_skill("unarmed", "meinv-quan");
        prepare_skill("strike", "tianluo-diwang");

        set("chat_chance_combat", 80);

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
        weapon = carry_object("/d/gumu/obj/yufeng-zhen");
        weapon->set_amount(30);
        set_temp("handing", weapon);
}
