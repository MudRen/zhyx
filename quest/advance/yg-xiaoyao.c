//created by lestat
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>
void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;
        me->set("title",HIB"��ңɢ��"NOR);
        me->set_skill("unarmed", j);
        set("gender", "����");
        me->set_skill("force", j+random(15));
        me->set_skill("beiming-shengong", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("feiyan-zoubi", j+random(15));
        me->set_skill("liuyang-zhang", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("sword", j+random(15));
        me->set_skill("liuyue-jian", j+random(15));
        me->set_skill("zhemei-shou", j+random(15));
        me->set_skill("hand", j+random(15));
        me->set_skill("strike", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("martial-cognize", j+random(15));

        map_skill("force", "beiming-shengong");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("hand", "zhemei-shou");
        map_skill("strike", "liuyang-zhang");
        map_skill("parry", "liuyue-jian");
        map_skill("sword", "liuyue-jian");

        prepare_skill("hand","zhemei-shou");
        prepare_skill("strike","liuyang-zhang");

        set("class", "taoist");

        set("chat_chance_combat", 80);

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
