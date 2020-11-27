// jueqing.c 

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("�������", ({ "hu yidao", "hu" }));
	set("long",  "��������Ӷ���ľ����ǰ�ι�����\n");
	set("gender", "����");
	set("age", 88);
	set("attitude", "peaceful");
	set("shen_type", 0);
	set("str", 38);
	set("int", 31);
	set("con", 32);
	set("dex", 36);
	
	set("max_qi", 6000);
	set("max_jing", 3000);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 10);
	set("combat_exp", 25000000);

        set_skill("force", 240);

	set_skill("fenxin-jue", 240);
        set_skill("dodge", 240);
        set_skill("jueqing-shenfa", 240);
        set_skill("strike", 240);
        set_skill("jueqing-zhang", 240);
        set_skill("cuff", 240);   
        set_skill("pokong-quan", 240);
        set_skill("sword", 260);
        set_skill("yinyang-ren", 260); 
        set_skill("blade", 260);
        set_skill("parry", 240);
        set_skill("literate", 240);
        set_skill("medical", 240);
        set_skill("jueqing-yaoli", 240);
        set_skill("martial-cognize", 220);

        map_skill("strike", "jueqing-zhang");
        map_skill("sword", "yinyang-ren");
        map_skill("blade", "yinyang-ren");
        map_skill("force", "fenxin-jue");
        map_skill("cuff", "pokong-quan");
        map_skill("dodge", "jueqing-shenfa");
        map_skill("parry", "yinyang-ren");

        prepare_skill("strike", "jueqing-zhang");

        create_family("�����", 0, "����");

	set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.huan" :),
                (: perform_action, "blade.heng" :),
                (: perform_action, "strike.hun" :),
		(: perform_action, "strike.wan" :),
                (: exert_function, "recover" :),
        }));

	setup();
	carry_object("/clone/weapon/gangdao")->wield();
	carry_object("/clone/misc/cloth")->wear();
}
