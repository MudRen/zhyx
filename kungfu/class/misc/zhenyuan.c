// zhenyuan.c
#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("����ͷ", ({ "wang biaotou", "wang" }));
	set("long",  "������Զ�ھ�����ͷ��\n");
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
	
  	set_skill("force", 560);
  	set_skill("nei-bagua", 560);
  	set_skill("parry", 560);
  	set_skill("wai-bagua", 560);
  	set_skill("dodge", 540);
  	set_skill("bagua-bu", 540);
  	set_skill("unarmed", 540);
  	set_skill("youshen-zhang", 540);
  	set_skill("strike", 540);
  	set_skill("bagua-zhang", 540);
  	set_skill("bazhen-zhang", 540);
  	set_skill("cuff", 540);
  	set_skill("bagua-quan", 540);
  	set_skill("yanqing-quan", 540);
  	set_skill("blade", 560);
  	set_skill("bagua-dao", 560);
  	set_skill("kuimang-dao", 540);
  	set_skill("throwing", 540);
  	set_skill("bagua-biao", 540);
  	set_skill("literate", 220);
  	set_skill("martial-cognize", 540);

	map_skill("unarmed", "youshen-zhang");
	map_skill("dodge", "bagua-bu");
	map_skill("force", "nei-bagua");
	map_skill("strike", "bazhen-zhang");
	map_skill("blade", "bagua-dao");
	map_skill("cuff", "bagua-quan");
	map_skill("parry", "wai-bagua");
	map_skill("throwing", "bagua-biao");

	prepare_skill("unarmed", "youshen-zhang");
        set("class", "fighter");

  	create_family("������", 0, "��ͷ");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.mang" :),
                (: perform_action, "blade.tian" :),
                (: perform_action, "unarmed.fan" :),
                (: perform_action, "parry.zhen" :),
                (: perform_action, "throwing.zhi" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );


	setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
