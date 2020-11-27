// tonglao.c

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("��ɽͯ��", ({ "tonglao", "lao" }));
	set("long", @LONG
������ȥֻ��һ��СС�ĺ�ͯ��������ò��Ȼ���ϡ�
LONG );
	set("gender", "Ů��");
	set("age", 96);
	set("attitude", "peaceful");

	set("str", 36);
	set("int", 31);
	set("con", 45);
	set("dex", 33);

	set("qi", 6000);
	set("max_qi", 6000);
	set("jing", 3000);
	set("max_jing", 3000);
	set("neili", 8000);
	set("max_neili", 8000);
	set("jiali", 200);

	set("combat_exp", 26000000);
	set("score", 10000000);

	set_skill("force", 570);
	set_skill("dodge", 570);
	set_skill("parry", 570);
	set_skill("hand", 570);
	set_skill("strike", 570);

	set_skill("zhemei-shou", 570);
	set_skill("liuyang-zhang", 570);
	set_skill("yueying-wubu", 570);
	set_skill("bahuang-gong", 570);

	map_skill("force", "bahuang-gong");
	map_skill("strike", "liuyang-zhang");
	map_skill("dodge", "yueying-wubu");
	map_skill("hand", "zhemei-shou");
	map_skill("parry", "liuyang-zhang");

	prepare_skill("hand","zhemei-shou");
	prepare_skill("strike","liuyang-zhang");	

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.jiubu" :),
                (: perform_action, "strike.jiutian" :),
                (: perform_action, "strike.pori" :),
                (: exert_function, "recover" :),
        }));

	create_family("���չ�", 0, "����");
	setup();
	carry_object("/d/lingjiu/obj/changpao")->wear();
}
