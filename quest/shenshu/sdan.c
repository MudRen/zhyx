#include <ansi.h>
inherit ITEM;

void setup()
{}

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name(HIY"��ת��"NOR, ({"jin dan", "jindan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�ž�ת�𵤡�\n");
		set("value", 50000);
set("no_pawn",1);
	}
	setup();
}

int do_eat(string arg)
{
	int exp,pot,score;
        object me = this_player();
 	if (!id(arg))
	return notify_fail("��Ҫ��ʲô��\n");

        if ( (int)me->query_condition("medicine") > 0 )
	{
		me->add("max_neili", -1);
		message_vision(HIR "$N����һ�ž�ת�𵤣�ֻ����ͷ�ؽ��ᣬҡҡ������ԭ����ʳ̫��̫�࣬ҩЧ�ʵ��䷴��\n" NOR, me);
	}
	else
	{
	exp = 2100+random(2000);
	             pot = exp/3;
             score = random(200)+100;
             me->add("combat_exp",exp);
             me->add("potential",pot);
             me->add("score",score);
tell_object(me,HIY"�㱻�����ˣ�50����������\n" +
             chinese_number(exp) + "��ʵս����\n"+
             chinese_number(pot) + "��Ǳ��\n" +
            chinese_number(score)+"�㽭������\n"NOR);
        me->add("max_neili", 50);
        message_vision(HIY "$N����һ�ž�ת�𵤣�ֻ������������ԴԴ��������������һ�����Ƶ�!\n" NOR, me);
	}

        me->apply_condition("medicine", 60);
	
	destruct(this_object());
	return 1;
}