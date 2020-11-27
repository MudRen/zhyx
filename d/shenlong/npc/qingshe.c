//qingshe.c

#include <ansi.h>

inherit SNAKE;

void create()
{
	set_name("��Ҷ����", ({ "qing she", "she" }) );
	set("race", "����");
	set("age", 2);
	set("long", "һֻ���˿�����Ƥ������Ҷ���ߡ�\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("con", 20);
	set("limbs", ({ "ͷ��", "����", "�ߴ�", "β��" }) );
	set("verbs", ({ "bite" }) );

        set("snake_poison", ([
                "level"  : 40,
                "perhit" : 20,
                "remain" : 40,
                "maximum": 40,
                "supply" : 2,
        ]));

	set("combat_exp", 5000 + random(4000));

	set_temp("apply/attack", 18);
	set_temp("apply/damage", 15);
	set_temp("apply/armor", 12);
	set_temp("apply/defence",16);

	setup();
}

void die()
{
	object ob;
	message_vision("$N���ڵ��ϣ����ˣ�\n", this_object());
	ob = new("/d/baituo/obj/qingdan");
	ob->move(environment(this_object()));
	::die();
}

int convert(string arg)
{
	object me = this_player();
	object ob;

	if (arg!="snake" && arg!="she" && arg!="qing she") return 0;
	if (me->query("family/family_name") != "ŷ������") 
		return notify_fail("�㲻�ܻ���Ϊ�ȡ�\n");
	return notify_fail("��Ҷ�����ϸС�����ܻ�Ϊ�ȡ�\n");
}