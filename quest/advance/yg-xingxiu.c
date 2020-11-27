//created by vikee
//2000-12-9 23:35
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>


void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

        me->set("title",HIM"���޶�ħ"NOR);
        me->set_skill("force", j+random(15));
        me->set_skill("huagong-dafa", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("zhaixinggong", j+random(15));
        me->set_skill("strike", j+random(15));
        me->set_skill("chousui-zhang", j+random(15));
        me->set_skill("claw", j+random(15));
        me->set_skill("sanyin-wugongzhao", j+random(15));
        me->set_skill("whip", j+random(15));
        me->set_skill("chanhun-suo", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("staff", j+random(15));
        me->set_skill("tianshan-zhang", j+random(15));
        me->set_skill("throwing", j+random(15));
        me->set_skill("feixing-shu", j+random(15));
        me->set_skill("poison", j+random(15));
        me->set_skill("xingxiu-qishu", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("martial-cognize", j+random(15));

        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixinggong");
        map_skill("strike", "chousui-zhang");
        map_skill("claw", "sanyin-wugongzhao");
        map_skill("whip", "chanhun-suo");
        map_skill("parry", "tianshan-zhang");
        map_skill("staff", "tianshan-zhang");
        map_skill("poison", "xingxiu-qishu");

        prepare_skill("strike", "chousui-zhang");
        prepare_skill("claw", "sanyin-wugongzhao");

        set("chat_chance_combat", 80);

        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/misc/cloth")->wear();
}