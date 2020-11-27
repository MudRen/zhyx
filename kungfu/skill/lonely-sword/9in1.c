// ��ʽ��һ by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
	    object weapon;
        string msg, wp,name;
        int ap, dp;
        int damage;
		object weapon2;
		object equipment;
 
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("���¾Ž�֮��ʽ��һֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("�޽�������þ�ʽ��һ��\n");

	if ((int)me->query("neili") < 2000)
		return notify_fail("�����ڵ������������޷�ʹ�ô콣ʽ��\n");

	if ((int)me->query_skill("lonely-sword", 1) < 900)
		return notify_fail("��Ķ��¾Ž��������ң��޷�ʹ�ö��¾Ž�֮��ʽ��һ��\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("��û�м������¾Ž����޷�ʹ�þ�ʽ��һ��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "���һ�������У������������н��Ⱪ�ǣ����¾Ž���ʽ�������������\n" NOR;

        damage = me->query_skill("lonely-sword",1);
                damage  = damage + random (damage);

		msg += HIM"                      �ƽ�ʽ��\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
		                           HIR "$n" HIR "ֻ���Ľ�����ҫ��ѣ��ֻ����ʱ���̳�һ��Ѫ������\n" NOR);
		msg += HIG"                      �˽�ʽ��\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
		                           HIR "$n" HIR "ֻ���Ľ�����ҫ��ѣ��ֻ����ʱ���̳�һ��Ѫ������\n" NOR);
		msg += HIY"                      �ý�ʽ��\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
		                           HIR "$n" HIR "ֻ���Ľ�����ҫ��ѣ��ֻ����ʱ���̳�һ��Ѫ������\n" NOR);
		msg += HIR"                      �佣ʽ��\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
		                           HIR "$n" HIR "ֻ���Ľ�����ҫ��ѣ��ֻ����ʱ���̳�һ��Ѫ������\n" NOR);
		msg += HIC"                      �콣ʽ��\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
		                           HIR "$n" HIR "ֻ���Ľ�����ҫ��ѣ��ֻ����ʱ���̳�һ��Ѫ������\n" NOR);
		msg += HIW"                      �ؽ�ʽ��\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
		                           HIR "$n" HIR "ֻ���Ľ�����ҫ��ѣ��ֻ����ʱ���̳�һ��Ѫ������\n" NOR);
		msg += HIY"                      ����ʽ��\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 110,
		                           HIR "$n" HIR "ֻ���Ľ�����ҫ��ѣ��ֻ����ʱ���̳�һ��Ѫ������\n" NOR);
		msg += HIG"                      �뽣ʽ��\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 120,
		                           HIR "$n" HIR "ֻ���Ľ�����ҫ��ѣ��ֻ����ʱ���̳�һ��Ѫ������\n" NOR);
		msg += HIG"                      ��ʽ��һ��\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 130,
		                           HIR "$n" HIR "ֻ���Ľ�����ҫ��ѣ��ֻ����ʱ���̳�һ��Ѫ������\n" NOR);								   
		
		
		message_combatd(msg, me, target);

		if (objectp(weapon2 = target->query_temp("weapon")) && random(3)==1)
		{
			  wp = weapon2->name();                                                        
              weapon2->set("consistence", 0);									 
              weapon2->move(environment(me));
		      message_combatd(HIC "ֻ����ž����һ�����죬$n" HIC "��"
                                                "�е�" + wp + HIC "��$N" HIC "��������"
                                                "��Ӧ�����飬���ֵ����ڵ��ϡ�\n" NOR, me, target);                                      
		}  

		if (objectp(equipment = target->query_temp("armor/hands")) && random(3)==1)
		{
		  name = equipment->name();      
		  equipment->move(environment(me));
		  message_combatd(HIW "$n" HIW "���ϵ�" + name + HIW "�����Ƶ����ڵء�\n" NOR, me, target);
		}
		if (objectp(equipment = target->query_temp("armor/cloth")) && random(3)==1)
		{
		  name = equipment->name();      
		  equipment->move(environment(me));
		  message_combatd(HIW "$n" HIW "���ϵ�" + name + HIW "�����Ƶ����ڵء�\n" NOR, me, target);
		}
		if (objectp(equipment = target->query_temp("armor/armor")) && random(3)==1)
		{
		  name = equipment->name();      
		  equipment->move(environment(me));
		  message_combatd(HIW "$n" HIW "���ϵ�" + name + HIW "�����Ƶ����ڵء�\n" NOR, me, target);
		}
		
		if (! target->query_temp("lonely_dang") && me->query("character") == "������" && random(3)==1)
        {           
                target->add_temp("apply/force", -500);
                target->add_temp("apply/parry", -500);
                target->add_temp("apply/dodge", -500);
                target->set_temp("lonely_dang", 1);
        		msg = HIM "$nֻ���û��������ϣ�ȫ�����������һ˿˿Զ���Լ���ȥ������֮����\n" NOR;
				message_combatd(msg, me, target);
				call_out("dang_end", 5 + random(8), me, target);		
		}
		
		if (me->query("character") == "������" && random(4)==1){
				target->set("neili",0);
		}		
		me->start_busy(3+random(4));
		me->add("neili", -1500);
	

	return 1;
}

void dang_end(object me, object target)
{
        if (target && target->query_temp("lonely_dang"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "��������һ��������ɫ��"
                                        "��ת�죬�������ö��ˡ�\n" NOR, target);                       
                }                
                target->add_temp("apply/force", 500);
                target->add_temp("apply/parry", 500);
                target->add_temp("apply/dodge", 500);
                target->delete_temp("lonely_dang");
        }
        return;
}
