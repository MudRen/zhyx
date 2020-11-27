//created by vikee
//2000-12-9 23:35
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

        me->set("title",CYN"�컨�޵�"NOR);
        me->set_skill("force", j+random(15));
        me->set_skill("zhanshen-xinjing", j+random(15));
        me->set_skill("tianchi-neigong", j+random(15));
        me->set_skill("honghua-xinfa", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("zhuangzi-wu", j+random(15));
        me->set_skill("yanzi-chuanyun", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("unarmed", j+random(15));
        me->set_skill("baihua-cuoquan", j+random(15));
        me->set_skill("claw", j+random(15));
        me->set_skill("strike", j+random(15));
        me->set_skill("cuff", j+random(15));
        me->set_skill("blade", j+random(15));
        me->set_skill("hanwang-qingdao", j+random(15));
        me->set_skill("sword", j+random(15));
        me->set_skill("sanfen-jianshu", j+random(15));
        me->set_skill("whip", j+random(15));
        me->set_skill("jiandun-zhusuo", j+random(15));
        me->set_skill("martial-cognize", j+random(15));
        me->set_skill("literate", j+random(15));

        map_skill("dodge", "zhuangzi-wu");
        map_skill("force", "zhanshen-xinjing");
        map_skill("unarmed", "baihua-cuoquan");
        map_skill("parry", "baihua-cuoquan");
        map_skill("sword", "sanfen-jianshu");
        map_skill("whip", "jiandun-zhusuo");
        map_skill("blade", "hanwang-qingdao");

        prepare_skill("unarmed", "baihua-cuoquan");

        create_family("�컨��", 4, "����");

        set("chat_chance_combat", 100);

        carry_object("/d/city/npc/cloth/fu-cloth")->wear();
        carry_object("/d/city/npc/cloth/jade-belt")->wear();
        carry_object("/d/city/npc/cloth/scarf")->wear();
        add_money("gold", 2);
}