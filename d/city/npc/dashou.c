// liumang.c ��å

inherit "/inherit/char/b_npc.c";   

void create()
{
        set_name("����", ({ "da shou", "da", "shou" }));
	set("gender", "����");
	set("age", 19);
        set("long", "����һ���������ֺ��е���å������ǿ���˼ҵ��̣�\n");
	
        set("combat_exp", 4000000);
	set("shen_type", -1);

	set("attitude", "peaceful");
	
	set_skill("unarmed", 200);
	set_skill("dodge", 200);
	set_temp("apply/attack", 10);
	set_temp("apply/defense", 10);

	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver",2);
}
