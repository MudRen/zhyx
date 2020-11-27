// xuanming.c ��ڤ����
#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("��ڤ����", ({ "xuanming guzhu", "guzhu" }));
	set("long",  "��������ڤ�ȵĹ�����\n");
	set("gender", "����");
	set("age", 60);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 37);
	set("int", 32);
	set("con", 35);
	set("dex", 36);
	
	set("max_qi", 6000);
	set("max_jing", 3000);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 10);
	set("combat_exp", 25000000);
	set("score", -10000);

        set_skill("force", 600);
        set_skill("xuanming-shengong", 600);
        set_skill("dodge", 600);
        set_skill("liuying-bu", 600);
        set_skill("strike", 600);
        set_skill("xuanming-zhang", 580);
        set_skill("cuff", 500);
        set_skill("piaofeng-quan", 500);
        set_skill("parry", 550);
        set_skill("claw", 520);
        set_skill("dagger", 520);
        set_skill("jingyue-bifa", 520);
        set_skill("hexing-bifa", 520);
        set_skill("dulong-shenzhua", 520);
        set_skill("literate", 260);
        set_skill("martial-cognize", 220);
        
        map_skill("strike", "xuanming-zhang");
        map_skill("force",  "xuanming-shengong");
        map_skill("dodge",  "liuying-bu");
        map_skill("parry",  "xuanming-zhang");
        map_skill("cuff",  "piaofeng-quan");
        map_skill("claw", "dulong-shenzhua");

        prepare_skill("strike", "xuanming-zhang");
             
        create_family("��ڤ��", 0, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({               
                (: perform_action, "strike.ying" :),
                (: perform_action, "strike.lang" :),
                (: perform_action, "strike.zhe" :),
                (: exert_function, "recover" :),
        }));


	setup();
        carry_object("/clone/cloth/baipao")->wear();
}
