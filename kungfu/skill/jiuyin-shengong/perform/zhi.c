// zhi.c �����޼�ָ
// created by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define ZHI "��" HIY "�����޼�ָ" NOR "��"

int perform(object me, object target)
{
        string msg,wp;
        object weapon;
        int n,count;
        int skill, ap, dp, damage;


        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("jiuyin-shengong", 1);

        if (! me->is_fighting(target))
                return notify_fail(ZHI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon"))
                return notify_fail(ZHI "ֻ�ܿ���ʩչ��\n");

        if (skill < 299)
                return notify_fail("��ľ����񹦵ȼ��������޷�ʩչ" ZHI "��\n");

        if (me->query("neili") < 800)
                return notify_fail("��������������������ʩչ" ZHI "��\n");

        if (me->query_skill_prepared("finger") != "jiuyin-shengong"
           && me->query_skill_prepared("unarmed") != "jiuyin-shengong")
                return notify_fail("��û��׼��ʹ�þ����񹦣��޷�ʩչ" ZHI "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        me->add("neili", -400);

        ap = me->query_skill("jiuyin-shengong", 1) + me->query_skill("martial-cognize", 1);
        dp = target->query_skill("jiuyin-shengong",1) + target->query_skill("martial-cognize", 1);

        msg = HIY "$N" HIY "���ֳ�ָ�����������ƺ�������$n"
              HIY + "��ʽ�е�������\n" NOR;
        if (ap + random(ap) > dp)
        {
                n = 8;
                if (ap * 3 / 5 + random(ap*2) > dp)
                {
					    count = ap / 5 ;
						me->add_temp("apply/attack", count);
	         	me->add_temp("apply/unarmed_damage", count / 2);
                        
						msg += HIY "$n" HIY "����ָ�����ޱȣ�ȫȻ�޷��ֵ�������֮������������$N"
                               HIY "��������" + chinese_number(n) + "ָ��\n" NOR;
                        
						message_combatd(msg, me, target);
                        
                        while (n-- && me->is_fighting(target))
                        {
                                if (random(2) && ! target->is_busy())
                                	target->start_busy(1);
								if (me->query("reborn")) {
									damage = ap*2/3 + random(ap);
									msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 85 + random(15),
									HIR "ֻ������һ����$n" HIR "�����Ѿ�����һ��Ѫ��ģ���Ŀ�����\n" NOR);
									message_combatd(msg, me, target);
								}else{
									COMBAT_D->do_attack(me, target, 0, 0);	
								}								
								if (objectp(weapon = target->query_temp("weapon")) && random(2)==1)
								{
                                    if (weapon->query("consistence") < 15 )
								    {
									  wp = weapon->name();                                                        
                                      weapon->set("consistence", 0);									 
                                      weapon->move(environment(me));
							       	  message_combatd(HIC "ֻ�����ϡ���һ�����죬$n" HIC "��"
                                                "�е�" + wp + HIC "��$N" HIC "��������"
                                                "��Ӧ�����飬���ֵ����ڵ��ϡ�\n" NOR, me, target);                                      
								    }  
									else
                                    {
                                      wp = weapon->name();                                      
								      weapon->add("consistence", -10);
									  message_combatd(HIW "ֻ����������һ����$n" HIW "��"
                                                "�е�" + wp + HIW "��$N" HIW "��������"
                                                "�²������ѡ�\n" NOR, me, target);
								    }
								}
                        } 
						me->start_busy(2 + random(5));
						me->add_temp("apply/attack", - count);
		        me->add_temp("apply/unarmed_damage", - count / 2);
                } else
                {
                        msg += HIY "$n" HIY "�������룬��æ�ֵ���ȫȻ�޷�������\n" NOR;
			            if (! target->is_busy())
                        	target->start_busy(5);
                        	message_combatd(msg, me, target);
                }
        } else
        {
                msg += HIC "����$n" HIC "�����Ż�����¶���������\n" NOR;
                me->start_busy(3 + random(4));
                message_combatd(msg, me, target);
        }

        
        return 1;
}
