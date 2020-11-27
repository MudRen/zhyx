// wolfdog.c

inherit NPC;

void create()
{
	set_name("���ǹ�", ({ "wolf dog", "dog" }) );
	set("race", "Ұ��");
	set("age", 4);
	set("long", "һֻ����ͦ�أ����ų���ͷ�Ĵ��ǹ������ǲ����������ĳ��\n");
	set("attitude", "peaceful");
	
	set("str", 26);
	set("cor", 30);

	set("limbs", ({ "ͷ��", "����", "ǰ��", "���", "β��" }) );
	set("verbs", ({ "bite", "claw" }) );

	set("combat_exp", 1000);
	
	set("chat_msg_combat", ({
		(: this_object(), "random_move" :),
		"���ǹ������ͽУ�������������������������\n",
		"���ǹ�ͻȻ����������������ҧ��ȴ��֪������ҧ˭��\n"
	}) );
		
	set_temp("apply/attack", 15);
	set_temp("apply/damage", 6);
	set_temp("apply/armor", 2);

	setup();
}

void init()
{
	object ob;

        if (! living(this_object()))
                return;

	::init();

	if (interactive(ob = this_player()))
	{
			remove_call_out("kill_ob");
			call_out("kill_ob", 1, ob); 
	}	
}
