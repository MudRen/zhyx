//created by lestat
//modified by huarong 2004/2

inherit __DIR__"yaoguai.c";

#include <ansi.h>
void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;
        me->set("title",HIB"��������"NOR);
        me->set_skill("unarmed", j);
        set("gender", "Ů��");
        me->set_skill("force", j+random(15));
        me->set_skill("emei-xinfa", j+random(15));
        me->set_skill("emei-jiuyang", j+random(15));
        me->set_skill("linji-zhuang", j+random(15));
        me->set_skill("dodge", j+random(15));
        me->set_skill("zhutian-bu", j+random(15));
        me->set_skill("finger", j+random(15));
        me->set_skill("tiangang-zhi", j+random(15));
        me->set_skill("hand", j+random(15));
        me->set_skill("jieshou-jiushi", j+random(15));
        me->set_skill("strike", j+random(15));
        me->set_skill("jinding-zhang", j+random(15));
        me->set_skill("piaoxue-zhang", j+random(15));
        me->set_skill("sixiang-zhang", j+random(15));
        me->set_skill("sword", j+random(15));
        me->set_skill("huifeng-jian", j+random(15));
        me->set_skill("emei-jian", j+random(15));
        me->set_skill("yitian-jian", j+random(15));
        me->set_skill("blade", j+random(15));
        me->set_skill("yanxing-dao", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("martial-cognize", j+random(15));
        me->set_skill("literate", j+random(15));
        me->set_skill("mahayana", j+random(15));
        me->set_skill("buddhism", j+random(15));

        map_skill("force", "linji-zhuang");
        map_skill("dodge", "zhutian-bu");
        map_skill("finger", "tiangang-zhi");
        map_skill("hand", "jieshou-jiushi");
        map_skill("strike", "jinding-zhang");
        map_skill("sword", "huifeng-jian");
        map_skill("blade", "yanxing-dao");
        map_skill("parry", "yitian-jian");

        prepare_skill("strike", "jinding-zhang");
        prepare_skill("hand", "jieshou-jiushi");

        create_family("������", 4, "����");

        set("chat_chance_combat", 120);


        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/city/obj/cloth")->wear();
}