// ��������
//lestat 2001
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>

// here should be this NPC specific skills.

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

	set("title",HIW"�������"NOR);
	set("gender", "����");
       me->set_skill("force", j+random(15));
        me->set_skill("bibo-shengong", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("anying-fuxiang", j+random(15));
        me->set_skill("finger", j+random(15));
        me->set_skill("throwing", j+random(15));
        me->set_skill("tanzhi-shentong", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("sword", j+random(15));
        me->set_skill("yuxiao-jian", j+random(15));
        me->set_skill("qimen-wuxing", j+random(15));
        me->set_skill("count", j+random(15));
        me->set_skill("jingluo-xue", j+random(15));
        me->set_skill("mathematics", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("martial-cognize", j+random(15));

        map_skill("force", "bibo-shengong");
        map_skill("finger", "tanzhi-shentong");
        map_skill("dodge", "anying-fuxiang");
        map_skill("parry", "tanzhi-shentong");
        map_skill("sword", "yuxiao-jian");
        map_skill("throwing", "tanzhi-shentong");

        prepare_skill("finger" , "tanzhi-shentong");

        set("chat_chance_combat", 80);

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
        weapon = carry_object("/d/taohua/obj/huaban");
        weapon->set_amount(80);
        set_temp("handing", weapon);
}
