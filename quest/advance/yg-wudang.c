// bula and mon@xyj
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";
#include <ansi.h>

// here should be this NPC specific skills.

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

        set("title",HIG"�䵱��ͽ"NOR);

        me->set_skill("force", j+random(15));
        me->set_skill("taiji-shengong", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("tiyunzong", j+random(15));
        me->set_skill("sword", j+random(15));
        me->set_skill("taiji-jian", j+random(15));
        me->set_skill("hand", j+random(15));
        me->set_skill("paiyun-shou", j+random(15));
        me->set_skill("unarmed", j+random(15));
        me->set_skill("taiji-quan", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("martial-cognize", j+random(15));
        me->set_skill("taoism", j+random(15));

        map_skill("parry", "taiji-jian");
        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("sword", "taiji-jian");
        map_skill("hand", "paiyun-shou");
        map_skill("unarmed", "taiji-quan");

        prepare_skill("hand", "paiyun-shou");
        prepare_skill("unarmed", "taiji-quan");

        set("chat_chance_combat", 80);

        set("class", "taoist");

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();
}
