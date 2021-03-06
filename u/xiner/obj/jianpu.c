// jianpu.c
// Modified by xiner 01/3/2009 开放残月剑法

inherit ITEM;

void create()
{
	set_name("残月剑谱", ({ "canyue book", "jianpu", "book" }));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long",
			"这是一本关于残月剑法的剑谱。\n"
			"\n你可以试着研习(read)一下。");
		set("value", 500);
		set("no_sell", 1);
		set("no_steal",1);
		set("no_put", 1);
		set("no_drop", 1);
		set("material", "silk");
	}
}

void init()
{
	if( this_player() == environment() )
	{
		add_action("do_study", "read");
		remove_call_out("destroy");
		call_out("destroy", 900);
	}
}

int do_study(string arg)
{
	object me = this_player();
	int cost=10,myskill;	

	if ( arg != "canyue book" && arg != "jianpu" && arg !="book" )
		return notify_fail("你要读什么？\n");

	if( (int)me->query("jing") < 100 )
	{
		write("你现在过于疲倦，无法专心下来研读新知。\n");
		return 1;
	}

	if (me->is_busy()) return notify_fail("你现在正忙着呢。\n");

	if ( me->is_fighter())
		return notify_fail("战斗中无法阅读新知！\n");

	if (me->query("int") < 30)
		return notify_fail("你的先天悟性不足无法学习！\n");

	if( (int)me->query_skill("literate",1) < 100 )
		return notify_fail("你的读书写字太生疏，无法理解残月剑法。\n");

	if( (int)me->query_skill("martial-cognize",1) < 250 )
		return notify_fail("你的武学修养不够，没有办法练残月剑法。\n");

//	if (!me->query("reborn")) return notify_fail("你觉得剑谱上所说的东西太深奥了!\n");

	if ( (int)me->query_skill("canyue-sword",1) < 50)
	{
	    if ((int)me->query("jing")>cost)
	       	{
			me->receive_damage("qi", random(50) + 50);
			me->receive_damage("jing", random(50) + 50);
			me->add("neili", -100);
			me->improve_skill("canyue-sword", (me->query_skill("canyue-sword",1)+me->query("int")));
			message_vision("$N正在专心研读残月剑法。\n", me);
			return 1;
		}
	    else
		{
			cost=me->query("jing");
			write("你现在过于疲倦，无法专心下来研读残月剑法。\n");
		}
	}
	call_out("destroy", 1);
	return notify_fail("你对着剑谱看来看去，无法从中领悟出更高深的剑法。\n");
}

int destroy() 
{ 
    tell_room(environment(this_object()),  
               "一阵风吹来，剑谱因为年代太久风化成灰烬了!\n"); 
    destruct(this_object()); 
    return 1;
}
