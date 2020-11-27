//fushe.c

inherit SNAKE;
#include <ansi.h>

void create()
{
	set_name("����", ({ "fu she", "she", "fu" }) );
	set("race", "����");
	set("age", random(10));
	set("long", "ֻ����ȫ��Ѫ�죬ͷ�����ǣ��������£��������졣\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("con", 20);
	set("limbs", ({ "ͷ��", "����", "�ߴ�", "β��" }) );
	set("verbs", ({ "bite" }) );

        set("snake_poison", ([
                "level"  : 120,
                "perhit" : 10,
                "remain" : 20,
                "maximum": 20,
                "supply" : 1,
        ]));

	set("combat_exp", 50000 + random(50000));

	set_temp("apply/attack", 20+random(10));
	set_temp("apply/damage", 10+random(10));
	set_temp("apply/armor",  15+random(10));
	set_temp("apply/defence",50+random(50));
	setup();
}

void die()
{
	object ob;
	message_vision("$N���ڵ��ϣ����ˣ�\n", this_object());
	ob = new("/clone/misc/shedan");
	ob->move(environment(this_object()));
	::die();
}

int convert(string arg)
{
	object me = this_player();
	object ob;

	if (arg!="snake" && arg!="she" && arg!="fu she" && arg!="fu") return 0;
	if (me->query("family/family_name") != "ŷ������") 
		return notify_fail("�㲻�ܻ���Ϊ�ȡ�\n");
	if (random(me->query_skill("training",1)) <20) {
		kill_ob(me);
		return 1;
	}
	message_vision("$N���ְ�ס���ߵ�ͷ�������ḧ���ߴ磬���������дʣ�Ƭ�̼佫�߻�Ϊһ�����ȡ�\n",
		me,);
	        ob = new("/d/baituo/obj/shezhang");
        ob->move(environment(this_object()));
        destruct(this_object());
	return 1;
}