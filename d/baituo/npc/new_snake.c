// Code of ShenZhou
// new_snake.c 
// maco

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("小蛇", ({ "snake" }) );
	set("long", "由欧阳世家白驼山庄培养出来的新生小蛇，到底会是什麽蛇，经过code才知道。\n");
	set("race", "蛇类");
	set("unit", "条");
	set("age", 1);
	set("attitude", "peaceful");

	set("auto_follow",0);
	set("wildness", 90);

	set("str", 20);
	set("cor", 20);
	set("dex", 20);

	set("combat_exp", 100000);

	set_temp("apply/attack", 40);
	set_temp("apply/damage", 40);
	set_temp("apply/armor", 60);

	set_skill("dodge", 10);
	set_skill("parry", 10);
	set_skill("force", 10);

	setup();
}

void init()
{
	::init();
	add_action("convert","bian");
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
       int poison;
       poison = me->query("snake_poison");

	if(me->query("name") == "怪蛇" )
	{
		victim->apply_condition("bt_poison", 10 + me->query("snake_poison")/5 +
			victim->query_condition("bt_poison"));
	       return HIR "只听$n痛呼了一声，给怪蛇狠狠的咬了一口！\n" NOR;
	}

	if( poison > 0 && !victim->query("snake_poison")) 
             victim->affect_by("snake_poison",
                              ([ "level" : poison/5 + random(poison/5),
                                 "id"    : me->query("id"),
                                 "duration" :  poison/20 ]));
       return HIR "只听$n痛呼了一声，给毒蛇狠狠的咬了一口！\n" NOR;
}

int convert(string arg)
{
	object me = this_player();
	object ob;

	if (arg!="snake" && arg!="she") return 0;
	if (me->query("family/family_name") != "欧阳世家") 
		return notify_fail("你不能化蛇为杖。\n");

	return notify_fail(this_object()->name()+"出生不久，身子太小，还不能化为蛇杖。\n");
}
