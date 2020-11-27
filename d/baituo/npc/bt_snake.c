// Code of JHSH
// baituo snake ����ɽ�߹ȵ���
// ע�⣺ǧ�򲻿������߹�����ķ��䣡
// by maco 
#include <ansi.h>

inherit "/inherit/char/trainee.c";
void set_kind(int);
void query_lord();
void create()
{
	set("race", "����");
	set("age", 4);
	set("attitude", "peaceful");

	set("msg_fail", "$n��$N˻��һ����ͷ");
	set("msg_succ", "$n˻˻���죬��ͷ����$N���ֶ�������");
	set("msg_trained","$n������Ϣ���ε�$N�Ľ��²�����");
	set("wildness", 9);

	set("str", 26);
	set("cor", 30);

	set("combat_exp", 1000);

	set_temp("apply/attack", 15);
	set_temp("apply/damage", 6);
	set_temp("apply/armor", 2);
	set_kind(random(8));
	setup();
}

void set_kind(int poison)
{
	int s;

	if(poison > 7) poison = 7;

	s = random(40);

	switch( poison )
	{
	case 0:
		set_name("����", ({ "snake", "she" }) );
		set("long", "һֻ�����������Դ����ߣ�β��ɳɳ���졣\n");
		set("combat_exp", 1000);
		break;
	case 1:
		set_name("����", ({ "hei she", "snake" ,"she" }) );
		set("long", "�����������Ӻڵ÷��������ϰ׵�Ҳ���������⣬�ſ���ڣ�¶���ĸ������\n");
		break;
	case 2:
		set_name("��Ҷ��", ({ "zhuye qing", "snake" }) );
		set("long", "һֻ������̵��ߣ��Ե��ر�ϸС��\n");
		break;
	case 3:
		set_name("�ٲ���", ({ "baibu she", "she", "snake" }) );
		set("long", "һ����ɫ���ߣ����۸��塣��˵���ٲ���ҧ�ˣ��߳�һ�ٲ��������ɡ�\n");
		break;
	case 4:
		set_name("�໨��", ({ "qinghua she", "she", "snake" }) );
		set("long", "һ������������Ķ��ߣ�������������ͷ��⣬������֮�Σ��Ծ߾綾��\n");
		break;
	case 5:
		set_name("����", ({ "fu she", "she", "snake" }) );
		set("long", "һ��ϸ����������ߡ�\n");
		break;
	case 6:
		set_name("������", ({ "chilian she", "chilian", "she", "snake" }) );
		set("long", "һ�������ĳ����ߣ�����쵣����ǿɲ���\n");
		break;
	case 7:
		set_name("������", ({ "jinxian she", "she", "snake" }) );
		set("long", "һ����ͷС�ߣ�ȫ�����۸��壬һ���������߸����¡�\n");
		break;
	}
	set_weight(poison*600 + 9000);
	set("str", 30 + poison );
	set("con", 30 + poison );
	set("int", 20);
	set("dex", 30 + poison );
	
	set("max_jing", 800 + poison*200);
	set("max_qi", 800 + poison*200);
	set("eff_jing", 800 + poison*200);
	set("eff_qi", 800 + poison*200);
	set("jing", 800 + poison*200);
	set("qi", 800 + poison*200);

	set("combat_exp", (poison + 1)*60000);

	set_temp("apply/attack", 30 + s + poison*10 );
	set_temp("apply/damage", 30 + s + poison*10 );
	set_temp("apply/armor", 30 + s + poison*10 );

	set("snake_poison", 60 + poison*40 +random(61));
	set("bt_snake", 1);
}

void init()
{
	object ob;
	::init();
	add_action("convert","bian");
	if (interactive(ob = this_player()) &&
	    ob->query("family/family_name") != "ŷ������" &&
		random(ob->query_kar() + ob->query_per()) < 30) {
			remove_call_out("kill_ob");
			call_out("kill_ob", 1, ob); 
		return;
	}
	if ( query("frightened") && !query_lord() ) {
			remove_call_out("kill_ob");
			call_out("kill_ob", 1, ob); 
		return;
	}
}

void die()
{
	object ob;
	message_vision("$Nȫ��Ť�������ڻ��裬ȫ�������ɢ�˿�����\n", this_object());
	ob = new(DRUG_D("shedan"));
	ob->move(environment(this_object()));
	destruct(this_object());
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
       int poison;
       poison = me->query("snake_poison");

	if( poison > 0 && !victim->query("snake_poison")) 
             victim->affect_by("snake_poison",
                              ([ "level" : poison/5 + random(poison/5),
                                 "id"    : me->query("id"),
                                 "duration" :  poison/20 ]));
       return HIR "ֻ��$nʹ����һ���������ߺݺݵ�ҧ��һ�ڣ�\n" NOR;
}

int convert(string arg)
{
	object me = this_player();
	object ob;

	if (arg!="snake" && arg!="she") return 0;
	if (me->query("family/family_name") != "ŷ������") 
		return notify_fail("�㲻�ܻ���Ϊ�ȡ�\n");

	if (this_object()->query("name") != "����") 
		return notify_fail(this_object()->name()+"���ʺϻ�Ϊ���ȡ�\n");

	if (random(me->query_skill("training",1)) <20) {
		kill_ob(me);
		return 1;
	}
	message_vision("$N���ְ�ס��ͷ�������ḧ���ߴ磬���������дʣ�Ƭ�̼佫�߻�Ϊһ�����ȡ�\n",
		me,);
                ob = new("/d/baituo/obj/shezhang");
	ob->move(environment(this_object()));
	destruct(this_object());
	return 1;
}
