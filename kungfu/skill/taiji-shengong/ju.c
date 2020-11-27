// Created by Kasumi

#include <ansi.h>
#define JU "「" HIY"聚魄"HIW"还虚" NOR "」"

int exert(object me, object target)
{
	string msg;
	int level = me->query_skill("taiji-shengong", 1);

	if (level < 400) return notify_fail("你的太极神功修为还不够施展" JU "。\n");

		if( (int)me->query("neili") < 600 ) 
		return notify_fail("你的内力不足无法施展" JU "。\n");

	if( (int)me->query("jingli") == (int)me->query("max_jingli") ) 
		return notify_fail("你的精力充沛，不必施展" JU "。\n");
	
	msg = HIY "只见" + me->name()+"席地而坐，五心向天，益气升阳，益阴潜阳，升降反正，天地二气交泰于身，\n"
		  HIY "脸上红光时隐时现，不一会儿便神采弈弈地站了起来。\n"NOR;
	message_vision(msg, me);

	me->add("jingli", 300);
	me->add("neili", -600);
    
	if ((int)me->query("jingli") > (int)me->query("max_jingli"))
		me->set("jingli",(int)me->query("max_jingli"));

	if (me->is_fighting())
		me->start_busy(3);
	else me->start_busy(2);
	
	return 1;
}
