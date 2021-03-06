// 离剑式 by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
	object weapon;
        string msg,name;
        int ap, dp;
        int damage;
		object equipment;
 
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("离剑式只能对战斗中的对手使用。\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("无剑如何运用离剑式？\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("你现在的真气不够，无法使用离剑式！\n");

	if ((int)me->query_skill("lonely-sword", 1) < 300)
		return notify_fail("你的独孤九剑还不到家，无法使用离剑式！\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("你没有激发独孤九剑，无法使用离剑式！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "冷哼一声，忽的使出独孤九剑"HIM"“离剑式”"HIC"，手中剑光星星点点洒向$n"HIC"。\n" NOR;

        damage = me->query_skill("lonely-sword",1) * 10;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
		                           HIR "$n" HIR "竭力抵抗，身上护具件件被剑锋划破而跌落在地，身上血流不止！\n" NOR);
		if (objectp(equipment = target->query_temp("armor/hands")) && random(3)==1)
		{
		  name = equipment->name();      
		  equipment->move(environment(me));
		  message_combatd(HIW "$n" HIW "身上的" + name + HIW "被划破跌落在地。\n" NOR, me, target);
		}
		if (objectp(equipment = target->query_temp("armor/cloth")) && random(3)==1)
		{
		  name = equipment->name();      
		  equipment->move(environment(me));
		  message_combatd(HIW "$n" HIW "身上的" + name + HIW "被划破跌落在地。\n" NOR, me, target);
		}
		if (objectp(equipment = target->query_temp("armor/armor")) && random(3)==1)
		{
		  name = equipment->name();      
		  equipment->move(environment(me));
		  message_combatd(HIW "$n" HIW "身上的" + name + HIW "被划破跌落在地。\n" NOR, me, target);
		}
		
		me->start_busy(2);
		me->add("neili", -300);
	
	message_combatd(msg, me, target);

	return 1;
}
