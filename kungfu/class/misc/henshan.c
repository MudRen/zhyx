// henshan.c 

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("��ɽ����", ({ "henshan laoren", "laoren" }));
	set("long",  "������ȥ�ɷ���ǣ���ò���ס�\n");
	set("gender", "����");
	set("age", 60);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 33);
	set("int", 38);
	set("con", 34);
	set("dex", 31);
	
	set("max_qi", 6000);
	set("max_jing", 3000);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 10);
	set("combat_exp", 25000000);
	set("score", 10000000);

        set_skill("force", 540);
        set_skill("henshan-xinfa", 540);   
	set_skill("zhenyue-jue", 540);
        set_skill("dodge", 540);
        set_skill("henshan-shenfa", 540);
        set_skill("cuff", 540);
        set_skill("henshan-quan", 540);
        set_skill("sword", 560);
        set_skill("henshan-jian", 560); 
        set_skill("wushen-jian", 560);
        set_skill("strike", 540);
        set_skill("biluo-zhang", 540);
        set_skill("liuyun-zhang", 540); 
        set_skill("parry", 540);
        set_skill("literate", 540);
	set_skill("tanqin-jifa", 300);
        set_skill("xiaoxiang-yeyu", 300);
        set_skill("martial-cognize", 520);

        map_skill("strike", "liuyun-zhang");
        map_skill("cuff", "henshan-quan");
        map_skill("sword", "wushen-jian");
        map_skill("force", "zhenyue-jue");
        map_skill("dodge", "henshan-shenfa");
        map_skill("parry", "shilin-jian");
	map_skill("tanqin-jifa", "xiaoxiang-yeyu");

        prepare_skill("strike", "liuyun-zhang");
             
        create_family("��ɽ��", 0, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.qian" :),
                (: perform_action, "sword.hui" :),
                (: perform_action, "strike.pai" :),
		(: perform_action, "strike.die" :),
                (: exert_function, "recover" :),
        }));

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/misc/cloth")->wear();
}
