// by xiner 26/04/2009
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIR "红袖" HIW "添" HIR "香" NOR, ({ "hongxiu book", "book" }));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long",
			"这是一本关于红袖添香功法的秘笈。\n"
			"\n你可以试着研习(read)一下。");
		set("value", 0);
		set("no_sell", 1);
		set("no_steal",1);
		set("no_put", 1);
		set("material", "silk");
	}
}

void init()
{
	if( this_player() == environment() )
	{
		add_action("do_study", "read");
	}
}

int do_study(string arg)
{
	object me = this_player();
	int cost;	

	if ( arg != "hongxiu book" && arg !="book" )
		return notify_fail("你要读什么？\n");

	if( (int)me->query("jing") < 100 )
	{
		write("你现在过于疲倦，无法专心下来研读新知。\n");
		return 1;
	}

	if( (int)me->query("neili") < 100 )
	{
		write("你现在内力不足，无法专心下来研读新知。\n");
		return 1;
	}

	if (me->is_busy()) return notify_fail("你现在正忙着呢。\n");

	if ( me->is_fighter())
		return notify_fail("战斗中无法阅读新知！\n");

	if (me->query("int") < 30 && me->query_int() < 80)
		return notify_fail("你的悟性不足无法学习！\n");

	if (me->query("mask/freequest/sew") < 301)
		return notify_fail("你的女红太差了不能领会其中奥妙！\n");		

	if( (int)me->query_skill("literate",1) < 200 )
		return notify_fail("你的读书写字太生疏，无法理解红袖添香。\n");

	if( (int)me->query_skill("martial-cognize",1) < 100 )
		return notify_fail("你的武学修养不够，没有办法理解红袖添香。\n");

	if (!me->query("reborn")) return notify_fail("你觉得秘笈上所说的东西太深奥了!\n");

	if ( (int)me->query_skill("hongxiu-tianxiang",1) < 180 &&
		me->can_improve_skill("hongxiu-tianxiang") &&
		SKILL_D("hongxiu-tianxiang")->valid_learn(me))
	{
	    cost = 100 + random(100);
	    if ((int)me->query("jing")>cost)
	       	{
			me->receive_damage("qi", cost / 2);
			me->receive_damage("jing", cost);
			me->add("neili", -cost);
			me->improve_skill("hongxiu-tianxiang", (me->query_skill("hongxiu-tianxiang",1)+me->query("int")));
			message_vision("$N正在专心研读红袖添香。\n", me);
			return 1;
		}
	    else
		{
			cost=me->query("jing");
			write("你现在过于疲倦，无法专心下来研读红袖添香。\n");
		}
	}
	return notify_fail("你无法从书上学到任何东西。\n");
}
