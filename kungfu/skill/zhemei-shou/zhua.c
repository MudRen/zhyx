#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

#define HUA "��" HIR "������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg, parry_str;
        int ap, dp, p;
        int lv, cost_neili;

        if (userp(me) && ! me->query("can_perform/zhemei-shou/hua"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail(HUA "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(HUA "ֻ�ܿ���ʩչ��\n");
                
        if (me->query("int") < 34)
                return notify_fail("���������Բ��㣬�޷�ʩչ���ɵ��ռ����С�\n");
                
        if ((int)me->query_skill("beiming-shengong", 1) < 250)
                return notify_fail("��ı�ڤ�񹦻�򲻹�������ʩչ" HUA "��\n");

        if (lv = (int)me->query_skill("zhemei-shou", 1) < 250)
                return notify_fail("����ң��÷�ֵȼ�����������ʩչ" HUA "��\n");

        if (me->query("max_neili") < 4500)
                return notify_fail("���������Ϊ���㣬����ʩչ" HUA "��\n");

        if (me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("��û�м�����ڤ�񹦣�����ʩչ" HUA "��\n");

        if (me->query_skill_mapped("hand") != "zhemei-shou")
                return notify_fail("��û�м�����ң��÷�֣�����ʩչ" HUA "��\n");

        if (me->query_skill_prepared("hand") != "zhemei-shou")
                return notify_fail("��û��׼����ң��÷�֣�����ʩչ" HUA "��\n");

        if (me->query("neili") < 500)
                return notify_fail("�������������㣬����ʩչ" HUA "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY"                       ��   *   ��       ��        ��!!!!!!!!!!\n\n"HIM "$N" HIM "��������һ����������ڤ����������,���ֻӳ�����Ե��ʱϼ�����������"
              "��ɫ�����$n" HIM "ϯ�������\n\n" NOR;

        ap = me->query_skill("zhemei-shou", 1) + me->query_skill("dodge", 1)+me->query_skill("beiming-shengong", 1);
        dp = target->query_skill("dodge", 1) + target->query_skill("parry", 1)+target->query_skill("martial-cognize", 1);

        if (target->is_bad() || ! userp(target))
                ap += ap / 10;

        if (ap * 2 / 3 + random(ap) + random(20) > dp)
        {
                damage = 0;
                lv = me->query_skill("zhemei-shou", 1);
                if (lv >= 220)cost_neili = -250;
                if (lv >= 260)cost_neili = -220;
                if (lv >= 300)cost_neili = -190;
                if (lv >= 360)cost_neili = -160;
                
                if ( me->query("max_neili") > target->query("max_neili") * 2
                     && me->query("neili") > 500 )
                {
                        msg += HIM "ֻ��$n" HIM "һ����Х��$N" HIM "����ɫ��"
                               "���Ѿ���ע��$p" HIM "���ڣ���ʱ��$p" HIM "��"
                               "Ϊһ̲Ѫˮ��\n" NOR "( $n" RED "���˹��أ���"
                               "��������в�����ʱ�����ܶ�����" NOR ")\n";
                        damage = -1;
                        me->add("neili", cost_neili);
                       // me->start_busy(3);
                } else
                {
                        damage = ap;
                        damage += me->query_temp("apply/unarmed_damage");
                        damage += random(damage);

                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage / 2, me);
                        target->receive_damage("jing", damage / 4, me);
                        target->receive_wound("jing", damage / 8, me);
                        p = (int)target->query("qi") * 100 / (int)target->query("max_qi");

                        msg += HIM "$n" HIM "ֻ��΢΢һ㶣�$N" HIM "����ɫ�ƾ��������"
                               "�룬$p" HIM "���������ú�¯һ�㣬��Ż������Ѫ��\n\n" NOR;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                        
                                     
                        
                      //  me->add("neili", cost_neili);
                      //  me->start_busy(3);
                }
        } else
        {
                msg += CYN "$p" CYN "��״��ʧɫ����ȫ���Ʋ�͸$P"
                       CYN "���а��أ���������Ծ����������������\n" NOR;
              
        }
       
       msg +=HIY"$N�����޶���ڤ��,���Ϻ�������!ͻȻ��ָ����,�������У�ɨ��$n\n\n"NOR;
       
       
        if (ap * 3 / 5 + random(ap) > dp)          
        {          
                    damage = ap + me->query_skill("beiming-shengong",1) * 2;
                    
	                me->add("neili", -150);
                    msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                   HIG "ֻ�������ꡱһ����$N" HIG "���ƻ���$n" HIG "���ϵ�ҪѨ�ϣ�$n"
                                   HIG "һ���ҽУ�Ѫ���岽��\n"  NOR);    
        
      } else
      	
      	  {
                msg += CYN "$p" CYN "��״���Ų�æ��������$N$P"
                       CYN "���а��أ���������Ծ����������������\n" NOR;
               
        }
        
         if (ap * 2 / 3 + random(ap) > dp)          
              {          
                    damage = ap + me->query_skill("beiming-shengong",1);
                    
	                 me->add("neili", -100);
                  msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                   HIG "������,$N˫�����һ����ֻ�������ꡱһ����" HIG "$n" HIG "��������һ��Ѫ��"
                                   HIG "��״�ֲ���\n"  NOR);    
        
      } else
      	
      	  {
                msg += CYN "$p" CYN "��״���Ų�æ��������$N$P"
                       CYN "���а��أ���������Ծ����������������\n" NOR;
              
        }
        
        
         if (ap * 3 / 4 + random(ap) > dp)          
              {          
                    damage = ap;
                    
	                   me->add("neili", -100);
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                   HIG "$N�ٺ�һ����Ц��˫�������ǰ����������÷������̬��˫�ֻ���ǣ����һ�ɹ�����������$n\n"
                                   HIG "$n������ѹ�ȣ��۵�һ�����³�һ����Ѫ��\n"  NOR);    
        
      } else
      	
      	  {
                msg += CYN "$p" CYN "��״���Ų�æ��������$N$P"
                       CYN "���а��أ���������Ծ����������������\n" NOR;
               
                
        }
       
        
        if (me->query("reborn"))
        	{
                   if (ap * 4 / 5 + random(ap) > dp)
        	
        	   {
                        parry_str = target->query_skill_mapped("parry");

                            damage = ap + me->query_skill("beiming-shengong",1) * 4;
                        if (me->query_skill("zhemei-shou", 1) > 799)
                        {
                            damage = damage * 2 + random(damage);
                            target->map_skill("parry", 0);
                        }
                    
	                   me->add("neili", -200);
        		    msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 110,
        		                          HIY "\n$N��ת��֮�ˣ�ʹ����÷��ת������÷����Ū��\n\n"
        		                          HIY "$N��������:÷������Ӱ����Ū��Ϊһ,����ڤ����������,��������Ӱ,��Բ��������絶\n\n"
        		                          HIM "$n�����ֿ�,�����ֳ�����Ѫ��,�������,�����޼������\n" NOR);
                            target->map_skill("parry", parry_str);

             } else
      	
      	           {
                msg += CYN "$p" CYN "��״���Ų�æ��������$N$P"
                       CYN "���а��أ���������Ծ����������������\n" NOR;
                me->add("neili", -100);
              
                    }
          }
           me->start_busy(3+random(4));
        message_combatd(msg, me, target);

        if (damage < 0)
        {      //  target->die(me);
            target->set("eff_qi", -1);
            target->set("eff_jing", -1);
        }
        return 1;
}
