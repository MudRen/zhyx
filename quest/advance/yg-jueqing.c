// bula and mon@xyj
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>

// here should be this NPC specific skills.
void set_skills(int j, int level)
{
        object me=this_object();
	object weapon;

        set("title",YEL"�������"NOR);
        me->set_skill("force", j+random(15));
        me->set_skill("jueqing-xinfa", j+random(15));   
	me->set_skill("fenxin-jue", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("jueqing-shenfa", j+random(15));
        me->set_skill("strike", j+random(15));
        me->set_skill("jueqing-zhang", j+random(15));
        me->set_skill("guhong-zhang", j+random(15));
        me->set_skill("cuff", j+random(15));   
        me->set_skill("pokong-quan", j+random(15));
        me->set_skill("medical", j+random(15));
        me->set_skill("jueqing-yaoli", j+random(15));
        me->set_skill("sword", 260);
        me->set_skill("yinyang-ren", 260); 
        me->set_skill("zilei-jian", 260);
        me->set_skill("guxing-jian", 260);
        me->set_skill("blade", 260);
        me->set_skill("tianjue-dao", 260);
        me->set_skill("luoyun-dao", 260);
        me->set_skill("poguang-dao", 260);
        me->set_skill("parry", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("medical", j+random(15));
        me->set_skill("jueqing-yaoli", j+random(15));
        me->set_skill("martial-cognize", 220);

        map_skill("strike", "jueqing-zhang");
        map_skill("sword", "yinyang-ren");
        map_skill("blade", "yinyang-ren");
        map_skill("force", "fenxin-jue");
        map_skill("dodge", "jueqing-shenfa");
        map_skill("parry", "yinyang-ren");
        map_skill("parry", "jueqing-yaoli");

        prepare_skill("strike", "jueqing-zhang");
             
        create_family("�����", 5, "����");

        set("chat_chance_combat", 120);
      carry_object("/clone/weapon/gangdao")->wield();        
        carry_object("/clone/cloth/cloth")->wear();
}        