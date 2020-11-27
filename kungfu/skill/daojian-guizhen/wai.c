#include <ansi.h>
#include <combat.h>

#define TIANWAI "��" HIR "����Х��������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string type1, type2, msg,name;
        object weapon1, weapon2;
		object equipment;
        int ap, dp, damage, str;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(TIANWAI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        weapon1 = me->query_temp("weapon");
        weapon2 = me->query_temp("handing");

        if (! objectp(weapon1) || ! objectp(weapon2))
                return notify_fail("��û��ͬʱװ������������ʩչ" TIANWAI "��\n");

        if (weapon2->query("consistence") <= 0)
                return notify_fail("���" + weapon2->name() + "�Ѿ�����"
                                   "�𻵣��޷�����ʹ���ˡ�\n");

        type1 = weapon1->query("skill_type");
        type2 = weapon2->query("skill_type");

        if ((type1 != "sword" && type1 != "blade")
           || (type2 != "sword" && type2 != "blade"))
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" TIANWAI "��\n");

        if ((type1 == "sword" && type2 != "blade")
           || (type1 == "blade" && type2 != "sword"))
                return notify_fail("��û��ͬʱװ������������ʩչ" TIANWAI "��\n");

        if (me->query_skill_mapped("sword") != "daojian-guizhen"
           || me->query_skill_mapped("blade") != "daojian-guizhen")
                return notify_fail("��û�м����������棬����ʩչ" TIANWAI "��\n");

        if (me->query_skill("daojian-guizhen", 1) < 800)
                return notify_fail("��ĵ�������ȼ�����������ʩչ" TIANWAI "��\n");

        if (me->query_skill("lengyue-shengong", 1) < 500)
                return notify_fail("��������񹦵ȼ�����������ʩչ" TIANWAI "��\n");

	if (! me->query("reborn"))        
		return notify_fail("����δת���������޷����˾��У�\n");    

        if (me->query_skill("force") < 1000)
                return notify_fail("��ı����ڹ���ûѧ�ã�����ʩչ" TIANWAI "��\n");

        if (me->query("neili") < 1500)
                return notify_fail("�����ڵ���������������ʩչ" TIANWAI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = me->query_skill("sword") +
             me->query_skill("blade") +
             me->query_skill("force");

        dp = target->query_skill("force") +
             target->query_skill("sword") +
             target->query_skill("blade");

        damage = ap + random(ap);

        msg = HIY "$N" HIY "��" + weapon1->name() + HIY "��" + weapon2->name() + HIY "��������ǰ����ת���������ھ��纣Х�㱬����\n"
              HIY"�������ƶ�����˰���ɫ���������������һ��һľ��ɢ��������������������ǿ���ɱ�������ꡢ���⣬\n"
              HIY"��˲��ȫ�����۳�һ���������еĵĹ����������赲�� \n"
              HIY "$n" HIY "��ǰ�Ķ���������ȫ����˲�䱻���飬�ƿ���������գ�Ҳ�ƺ���ն�������롣\n"
              HIY"��һ�ˡ�һ����һ����������ģ��ݺݵķ�����$n�� \n" NOR;

        if (ap / 2 + random(ap) > dp)
        {

                msg += HIR "$n" HIR "��$N" HIR "ɱ�����ǣ�������"
                       "�����⣬�мܶ�ʱɢ�ң�ȫȻ��������\n" NOR;
                ap += ap / 2;
                damage += damage;
        } else
        {
                msg += HIG "$n" HIG "��$N" HIG "ɱ�����ǣ�˿����"
                       "�Ҵ��⣬��æ��������Ŭ�����ܸ��š�\n" NOR;
        }

        msg += HIW "\nͻȻ��$N" HIW "����һչ������" + weapon1->name() +
               HIW "����һ����վ��һ���뻡��ֱ��$n" HIW "��ȥ��\n" NOR;

        if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           HIR "$n" HIR "�����ֵ���ȴ�����мܵ�ס"
                                           "����$N" HIR "һ�л���Ҫ������Ѫ�Ĵ���"
                                           "����\n" NOR);
				//�Ʒ���
				if (objectp(equipment = target->query_temp("armor/cloth")) && random(3)==1)
				{
					name = equipment->name();                                                        
					equipment->set("consistence", 0);									 
					equipment->move(environment(me));
					msg += MAG "ֻ�����䡱��һ�����죬$n" MAG "��"
										"�ŵ�" + name + MAG "��$N" MAG "���潣����"
										"��Ӧ�����ѣ�����һ�����Ƭ��\n" NOR;   
				}
				//�Ƽ�								
				if (objectp(equipment = target->query_temp("armor/armor")) && random(3)==1)
				{
					name = equipment->name();                                                        
					equipment->set("consistence", 0);									 
					equipment->move(environment(me));
					msg += MAG "ֻ�����䡱��һ�����죬$n" MAG "��"
										"�ŵ�" + name + MAG "��$N" MAG "���潣����"
										"��Ӧ�����ѣ�����һ�����Ƭ��\n" NOR;   
				}
        } else
        {
                msg += CYN "$n" CYN "��֪��һ�е���������æ����"
                       "������С�Ĳ��У�˿������\n" NOR;
        }

        msg += HIW "\n����$N" HIW "�ֽ�����" + weapon2->name() +
               HIW "��$n" HIW "ƽƽ�ݳ�����ʽ���Ƽ򵥣�ȴ�̲���"
               "�����ɱ�š�\n" NOR;

        if (ap * 3 / 4 + random(ap) > dp)
        {
                // ת������
                weapon1->move(me, 1);
                weapon2->wield();

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 110,
                                           HIR "$n" HIR "ֻ���ۻ����ң�ȫȻ�޷���"
                                           "���Ȼ���$N" HIR "һ�����У����һ����"
                                           "Ѫ��\n" NOR);
                // ת�ƻس�ʼ״̬
                weapon2->move(me, 1);
                weapon1->wield();
                me->set_temp("handing", weapon2);
			//������
			if (objectp(equipment = target->query_temp("armor/hands")) && random(3)==1)
			{
					name = equipment->name();                                                        
					equipment->set("consistence", 0);									 
					equipment->move(environment(me));
					msg += MAG "ֻ�����䡱��һ�����죬$n" MAG "��"
										"�ŵ�" + name + MAG "��$N" MAG "���潣����"
										"��Ӧ�����ѣ�����һ�����Ƭ��\n" NOR;  
			}
			//�Ʊ���
			if (objectp(equipment = target->query_temp("weapon")) && random(3)==1)
			{
					name = equipment->name();                                                        
					equipment->set("consistence", 0);									 
					equipment->move(environment(me));
					msg += MAG "ֻ�����䡱��һ�����죬$n" MAG "��"
										"�ֵ�" + name + MAG "��$N" MAG "���潣����"
										"��Ӧ�����ѣ�����һ�����Ƭ��\n" NOR;  
			}
        } else
        {
                msg += CYN "$n" CYN "��֪��һ�е���������æ����"
                       "������С�Ĳ��У�˿������\n" NOR;
        }


     if ((int)target->query("qi")> 0&& me->is_fighting(target) && (int)me->query_skill("daojian-guizhen", 1) > 799 && !userp(target))
             {                              
                           if (ap + random(ap) > dp)
                           {       
                            target->receive_damage("qi", damage*2, me);
                            target->receive_wound("qi", damage, me);
	        	      str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                           msg += HIC"��Ȼ�䣬"HIC"$N"HIC"����"+ weapon1->name() + HIC "��" + weapon2->name() + HIC"���������ĳ�Х�������������⻪������ʣ�\n"
                                 HIC"��������ͻ�䣬�����⻪����߻���������" HIC"$n�����ǵ�����ǿ���У�  \n	 "             
                                 HIR"\n     ��" HIG"��" HIY"��" HIB"��" HIM"��" HIC"��" HIW"��" HIR"��" HIG"��" HIY"��" HIB"��" HIM"��" HIC"��" HIW"��\n"
                                               HIY"     " HIR"��"  HIY"  " HIY " �� "  HIC " �� "  HIR" Х "  HIW" �� "  HIB" �� " HIY"  " HIC"��"
                                                 HIR"\n     ��" HIG"��" HIY"��" HIB"��" HIM"��" HIC"��" HIW"��" HIR"��" HIG"��" HIY"��" HIB"��" HIM"��" HIC"��" HIW"��\n\n" 
                                  HIC"$n"HIC "��Ų���㣬�߾�ȫ����Ҳû�취�㿪��һ����һ���������˸����ţ�\n" NOR;
                           msg += "($n"+str+")\n";   
                                       if (random(3) == 1
                                           && target->query("neili"))
                                          {
                                           msg += HIY "\n$n" HIY "�ĵ���ǡ�ñ�$N" HIY "�������У�ȫ��������"
                                           "ɢ������ƺӾ��̣�������ʱ��к������\n\n" NOR;
	              	                             target->set("neili", 0);
                                             }
                             }
                         else
                          {
                                   msg += CYN "�Ҷ�$n" CYN "��ͨ�����������Դ���$N" CYN "�޴����֡�\n" NOR;
                         }  
                }
        me->start_busy(3 + random(3));
        me->add("neili", -1800);
        message_combatd(msg, me, target);
        return 1;
}
