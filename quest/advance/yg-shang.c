// bula and mon@xyj
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>

// here should be this NPC specific skills.

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

        me->set("title",HIB"���Խ�"NOR);
        me->set_skill("parry", j+random(15));
        me->set_skill("wai-bagua", j+random(15));
        me->set_skill("force", j+random(15));
        me->set_skill("nei-bagua", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("bagua-bu", j+random(15));
        me->set_skill("strike", j+random(15));
        me->set_skill("bagua-zhang", j+random(15));
        me->set_skill("cuff", j+random(15));
        me->set_skill("bagua-quan", j+random(15));
        me->set_skill("blade", j+random(15));
        me->set_skill("bagua-dao", j+random(15));
        me->set_skill("throwing", j+random(15));
        me->set_skill("bagua-biao", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("martial-cognize", j+random(15));

        map_skill("dodge", "bagua-bu");
        map_skill("force", "nei-bagua");
        map_skill("strike", "bagua-zhang");
        map_skill("blade", "bagua-dao");
        map_skill("cuff", "bagua-quan");
        map_skill("parry", "wai-bagua");
        map_skill("throwing", "bagua-biao");

        prepare_skill("cuff", "bagua-quan");
        prepare_skill("strike", "bagua-zhang");

        set("chat_chance_combat", 80);

        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/misc/cloth")->wear();
        weapon = carry_object("/clone/weapon/feihuangshi");
        weapon->set_amount(80);
        set_temp("handing", weapon);
}