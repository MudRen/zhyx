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

	set("title",HIW"���¹��"NOR);
	set("gender", "����");
    me->set_skill("force", j+random(15));
    me->set_skill("unarmed", j+random(15));
    me->set_skill("dodge", j+random(15));
    me->set_skill("parry", j+random(15));
    me->set_skill("cuff", j+random(15));
    me->set_skill("sword", j+random(15));
    me->set_skill("jiuyang-shengong", j+random(15));
    me->set_skill("shenghuo-shengong", j+random(15));
    me->set_skill("shenghuo-xinfa", j+random(15));
    me->set_skill("qiankun-danuoyi", j+random(15));
    me->set_skill("shenghuo-bu", j+random(15));
    me->set_skill("qishang-quan", j+random(15));
    me->set_skill("taiji-quan", j+random(15));
    me->set_skill("taiji-jian", j+random(15));
    me->set_skill("shenghuo-ling", j+random(15));
    me->set_skill("literate", j+random(15));

    map_skill("force", "shenghuo-shengong");
    map_skill("dodge", "qiankun-danuoyi");
    map_skill("unarmed", "jiuyang-shengong");
    map_skill("cuff", "qishang-quan");
    map_skill("sword", "shenghuo-ling");
    map_skill("parry", "qiankun-danuoyi");

    create_family("����", 36, "ʹ��");

    prepare_skill("cuff", "qishang-quan");

    set("chat_chance_combat", 120); 
    carry_object("/d/mingjiao/obj/baipao")->wear();
    carry_object("/clone/weapon/gangjian")->wield();

}