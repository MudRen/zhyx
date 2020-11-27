// songshan.c
#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("��ɽ����", ({ "songshan jiankuang", "song" }));
	set("long",  "��������ɽ��һ������\n");
	set("gender", "����");
	set("age", 85);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 32);
	set("int", 33);
	set("con", 32);
	set("dex", 31);
	
	set("max_qi", 6000);
	set("max_jing", 3000);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 10);
	set("combat_exp", 25000000);
	set("score", 10000000);
		      
        set_skill("cuff", 540);
        set_skill("strike", 560);       
        set_skill("sword", 560);
        set_skill("force", 580);
        set_skill("parry", 540);
        set_skill("dodge", 540);
        set_skill("lingxu-bu", 540);
        set_skill("songshan-jian", 560);
        set_skill("lingyun-jian", 560);
        set_skill("chuanyue-jian", 560);
        set_skill("jiuqu-jian", 560);
        set_skill("poyang-jian", 560);      
        set_skill("songshan-xinfa", 580);
        set_skill("hanbing-zhenqi", 580);
        set_skill("hanbing-zhang", 560);
        set_skill("songshan-zhang", 560);
        set_skill("songshan-quan", 540);
        set_skill("literate", 220);
        set_skill("martial-cognize", 500);

        map_skill("force", "hanbing-zhenqi");
        map_skill("sword", "poyang-jian");
        map_skill("parry", "poyang-jian");
        map_skill("strike", "hanbing-zhang");
        map_skill("cuff", "songshan-quan");
        map_skill("dodge", "lingxu-bu");

        prepare_skill("strike", "hanbing-zhang");
             
        create_family("��ɽ��", 0, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.long" :),
                (: perform_action, "sword.xian" :),
                (: perform_action, "strike.heng" :),
                (: perform_action, "strike.han" :),
                (: exert_function, "recover" :),
        }));


	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang/obj/whiterobe")->wear();
}
