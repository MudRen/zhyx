// liumang.c ��å

inherit BUNCH_NPC;

void create()
{
        set_name("�ӻ����ϰ�", ({ "boss", "zhp", "laoban" }));
	set("gender", "����");
	set("age", 19);
        set("long", "��������һ���������ֺ��е���å��������֪�������﷢��һ�ʺ�ƿ�������ӻ��̡�\n");
	
	set("combat_exp", 1000);
	set("shen_type", -1);

	set("attitude", "peaceful");
	
	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set_temp("apply/attack", 10);
	set_temp("apply/defense", 10);

	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver",2);
}
