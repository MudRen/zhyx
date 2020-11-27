// bula and mon@xyj
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>

// here should be this NPC specific skills.

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

        me->set("title",HIR"ŷ������"NOR);
       me->set_skill("force", j+random(15));
        me->set_skill("hamagong", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("chanchu-bufa", j+random(15));
        me->set_skill("staff", j+random(15));
        me->set_skill("lingshe-zhangfa", j+random(15));
        me->set_skill("cuff", j+random(15));
       me->set_skill("lingshe-quan", j+random(15));
       me->set_skill("finger", j+random(15));
       me->set_skill("shedu-qiqiao", j+random(15));
       me->set_skill("literate", j+random(15));
       me->set_skill("martial-cognize", j+random(15));

        map_skill("force", "hama-gong");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("dodge", "chanchu-bufa");
        map_skill("staff", "lingshe-zhangfa");
        map_skill("cuff", "lingshe-quan");
        map_skill("finger", "shedu-qiqiao");

        prepare_skill("cuff", "lingshe-quan");
        prepare_skill("finger", "shedu-qiqiao");

        set("chat_chance_combat", 100);

        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}