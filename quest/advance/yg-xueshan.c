// bula and mon@xyj
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>
// here should be this NPC specific skills.

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

        me->set("title",HIW"ѩɽ����"NOR);
       me->set_skill("force", j+random(15));
        me->set_skill("longxiang-gong", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("shenkong-xing", j+random(15));
        me->set_skill("hammer", j+random(15));
        me->set_skill("riyue-lun", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("unarmed", j+random(15));
        me->set_skill("lamaism", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("martial-cognize", j+random(15));

        map_skill("force", "longxiang-gong");
        map_skill("dodge", "shenkong-xing");
        map_skill("unarmed", "longxiang-gong");
        map_skill("parry", "riyue-lun");
        map_skill("hammer", "riyue-lun");

        prepare_skill("unarmed", "longxiang-gong");

        set("chat_chance_combat", 80);

        set("class", "bonze");

        carry_object("/d/xueshan/obj/yinlun")->wield();
        carry_object("/clone/misc/cloth")->wear();
}