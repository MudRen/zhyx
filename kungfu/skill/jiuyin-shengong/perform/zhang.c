// zhang.c ����������
// created by kasumi

#include <ansi.h>

inherit F_SSERVER;

#define ZHANG "��" HIM "����������" NOR "��"

int perform(object me, object target)
{
	    string msg,name,parry_str;
	    object equipment;
        int ap, dp;
        int i, times, count;


	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail(ZHANG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon"))
                return notify_fail("����ֻ�ܿ���ʩչ��\n");

	if ((int)me->query_skill("jiuyin-shengong", 1) < 349)
		return notify_fail("��ľ����񹦲�����񣬲���ʹ��" ZHANG "��\n");	

        if (me->query_skill_prepared("unarmed") != "jiuyin-shengong"
           && me->query_skill_prepared("strike") != "jiuyin-shengong")
                return notify_fail("��û��׼��ʹ�þ����񹦣��޷�ʩչ" ZHANG "��\n");

	if ( me->query("neili") < 800 )
		return notify_fail("�����������������ʹ��" ZHANG "��\n");

        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "˫��һ���û���������Ӱ����������$n"
              HIY "��ȥ��\n" NOR;
              
  message_combatd(msg, me, target);
		parry_str=target->query_skill_mapped("parry");
        ap = me->query_skill("jiujin-shengong", 1);
        dp = target->query_skill("parry", 1);

        if (ap * 3/5 + random(ap) > dp)
                count = ap / 6; 
        else count = ap / 8;
		if (me->query("reborn")) {
			target->map_skill("parry", 0);
		}

        me->add_temp("apply/attack", count);		
        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
                                //������
				                if (objectp(equipment = target->query_temp("armor/hands")) && random(3)==1)
								{
                                    if (equipment->query("consistence") < 15 )
								    {
									  name = equipment->name();                                                        
                                      equipment->set("consistence", 0);									 
                                      equipment->move(environment(me));
							       	  message_combatd(HIC "ֻ�����䡱��һ�����죬$n" HIC "��"
                                       "�ŵ�" + name + HIC "��$N" HIC "������"
                                       "��Ӧ�����ѣ�����һ�����Ƭ��\n" NOR, me, target);                                      
								    }  
									else
                                    {
                                      name = equipment->name();                                      
								      equipment->add("consistence", -10);
									  message_combatd(HIW "ֻ�����顱��һ�����죬$n" HIW "��"
                                       "�ϵ�" + name + HIW "��$N" HIW "������"
                                       "�����ֳ�һ˿�Ѻۡ�\n" NOR, me, target);
								    }
									continue;
								}
								//�Ʒ���
								if (objectp(equipment = target->query_temp("armor/cloth")) && random(3)==1)
								{
                                    if (equipment->query("consistence") < 15 )
								    {
									  name = equipment->name();                                                        
                                      equipment->set("consistence", 0);									 
                                      equipment->move(environment(me));
							       	  message_combatd(HIC "ֻ�����䡱��һ�����죬$n" HIC "��"
                                       "�ŵ�" + name + HIC "��$N" HIC "������"
                                       "��Ӧ�����ѣ�����һ�����Ƭ��\n" NOR, me, target);                                      
								    }  
									else
                                    {
                                      name = equipment->name();                                      
								      equipment->add("consistence", -10);
									  message_combatd(HIW "ֻ�����顱��һ�����죬$n" HIW "��"
                                       "�ϵ�" + name + HIW "��$N" HIW "������"
                                       "�����ֳ�һ˿�Ѻۡ�\n" NOR, me, target);
								    }
									continue;
								}
								//�Ƽ�								
								if (objectp(equipment = target->query_temp("armor/armor")) && random(3)==1)
								{
                                    if (equipment->query("consistence") < 15 )
								    {
									  name = equipment->name();                                                        
                                      equipment->set("consistence", 0);									 
                                      equipment->move(environment(me));
							       	  message_combatd(HIC "ֻ�����䡱��һ�����죬$n" HIC "��"
                                       "�ŵ�" + name + HIC "��$N" HIC "������"
                                       "��Ӧ�����ѣ�����һ�����Ƭ��\n" NOR, me, target);                                      
								    }  
									else
                                    {
                                      name = equipment->name();                                      
								      equipment->add("consistence", -10);
									  message_combatd(HIW "ֻ�����顱��һ�����죬$n" HIW "��"
                                       "�ϵ�" + name + HIW "��$N" HIW "������"
                                       "�����ֳ�һ˿�Ѻۡ�\n" NOR, me, target);
								    }
									continue;
								}
        }
		if (me->query("reborn")) {
			target->map_skill("parry", parry_str);
		}
        me->start_busy(3 + random(5));
        me->add("neili", -700);

        me->add_temp("apply/attack", -count);
		
	

	return 1;
}
