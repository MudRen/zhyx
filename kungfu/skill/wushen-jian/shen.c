#include <ansi.h>
#include <combat.h>

#define SHEN "��" HIM "����Ԫ��" NOR "��"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        int damage,count,i;
        string msg, wn, wp,wp2,str;
        object weapon,weapon2;
        int ap, dp;
        me = this_player();

        if (userp(me) && ! me->query("can_perform/wushen-jian/shen"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHEN "ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" SHEN "��\n");

        if ((int)me->query_skill("wushen-jian", 1) < 300)
                return notify_fail("���ɽ���񽣲�����죬����ʩչ" SHEN "��\n");

        if (me->query_skill_mapped("sword") != "wushen-jian")
                return notify_fail("��û�м�����ɽ���񽣣�����ʩչ" SHEN "��\n");

        if ((int)me->query_skill("force", 1) < 220)
                return notify_fail("����ڹ���򲻹�������ʩչ" SHEN "��\n");

        if ((int)me->query_skill("dodge", 1) < 200)
                return notify_fail("����Ṧ��򲻹�������ʩչ" SHEN "��\n");  

        if ((int)me->query("max_neili") < 5500)
                return notify_fail("���������Ϊ���㣬����ʩչ" SHEN "��\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("�����ڵ���������������ʩչ" SHEN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn = weapon->name();        

        
        msg = HIM "\n$N" HIM "΢΢һЦ���ھ����ǣ�����" + wn + HIM "�����ǧ��"
                  "��" HIR "ף��" HIM "������" HIY "�ϸ�" HIM "������" NOR WHT "ʯ��" HIM "������" HIG "ܽ��" HIM "������"
                  HIW "����" HIM "�����׽�������ʹ��������ʯ����Ϯ��$n" HIM "ȫ��......\n" NOR;
        message_sort(msg, me, target);
        
        switch(random(2))
        {
           case 1:
           	
        //ף��
        msg = HIY "\n$N" HIY "ŭ��һ����������ע�뽣�������ʱ���ͨ�죬һʽ��" HIR "�򽣷���" HIY "��ʹ����"
                  "��ʱ��Х������������" + wn + HIY "����ǧ������У�����$n" HIY "����" NOR; 
        message_sort(msg, me, target);
        
        ap = me->query_skill("sword") + me->query_skill("force");
        dp = target->query_skill("dodge",1) + target->query_skill("force");
        
        if (ap * 3 / 4 + random(ap) > random(dp))
        {
                damage = ap + random(ap/2);          
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                          (: final, me, target, damage :));         
         } else
         {
         	msg = CYN "$n" CYN "�۽�" +wn + CYN"������ǿ���򶨣�"
                      "������������$N" CYN "��������������¡�\n" NOR;       		
         }
         message_combatd(msg, me, target);   
         break;
                  
         default:         
         
        msg = HIY "\n$N" HIY "��Хһ�����ڿն���" + wn + HIY"�ڿ������һ����"
              HIY "������̼佣����ɢ������������������������Ӱ������$n"
              HIY "ȫ��" NOR;
        message_sort(msg, me, target);

        ap = me->query_skill("wushen-jian", 1);
        dp = target->query_skill("dodge", 1);

        if (random(ap)+ ap/2 > dp / 2)
        {
         	damage = me->query_skill("sword");
         	damage += random(damage);

         	msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           HIR "$n" HIR "ֻ����������Ϯ�������Լ���Χ"
                                           "ס������ԥ�䣬$n" HIR "�ѱ�" + wn + HIR 
                                           "�̵�Ƥ��������\n" NOR);         	
        } else
        {
         	msg = CYN "Ȼ��$n" CYN "�������е�����������һ��"
                      "��Ȼ���$N" CYN "��һ����\n" NOR;       		
        }
        message_combatd(msg, me, target);
      }
         
         //�ϸ�
         msg = HIG "\nֻ��$N" HIG "һ�������������У�" HIG "������ջ����̣�" 
               HIG "ȷ��һ�С�" HIC "�ϸǻ���" HIG"��,����" NOR + wn + HIG "ֱָ$n" HIG "��" NOR;
         message_sort(msg, me, target);
         
         ap = me->query_skill("wushen-jian",1);
         dp = target->query_skill("dodge",1);
         if (ap * 3 / 4 + random(ap) > dp)
         {
         	damage = ap * 2 + random(ap);
          target->receive_damage("qi", damage,me);
          target->receive_wound("qi", damage*3/5, me);
	        str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	       	msg = "($n"+str+")\n";        	
        } else
        {
         	msg = CYN "Ȼ��$n" CYN "�ۼ�" + wn + CYN "��������$n"
                      CYN "��Ѹ���ޱȣ��������һ�ݣ�$N" CYN "����"
                      "���ա�\n" NOR;
        }
        message_combatd(msg, me, target);
        
        //ʯ��
        msg = HIW "\n�����ţ�$N" HIW "��������һ����һʽ��" HIG"��Ӣ�׷�" HIW"������"
                  + weapon->name() + HIW "��Ϊ���콣�⣬���ǵ������$n" HIW "��\n" NOR;
        message_sort(msg, me, target);
        me->set_temp("perform_wushenjian/lian", 1);
        count=me->query_skill("sword") / 6;
        me->add_temp("apply/attack", count);        
        for (i = 0; i < 6; i++)
	      {
		        if (! me->is_fighting(target))
			           break;
			      if (! target->is_busy() && random(2) == 1)
                       target->start_busy(1);
	        COMBAT_D->do_attack(me, target, weapon, 0);
	      }
        me->add_temp("apply/attack", -count);        
        me->delete_temp("perform_wushenjian/lian");
        
        //����
        
        if (objectp(weapon2 = target->query_temp("weapon")))
        {
             wp2 = weapon2->name();
	           msg = MAG "$N" MAG "����΢΢һ����ͻȻʩչ��������������������" +
                      wn + MAG "����һ����â������$n" MAG "���ֵ�" + wp2 + MAG "��\n" NOR;                		

	             if (random(me->query_skill("sword")) > target->query_skill("parry") / 2)
              	{
                	msg += HIR "$n" HIR "ֻ����ǰ��â���ǣ���ʱ����һ�ᣬ"
                              + wp2 + HIR "�����ַɳ���\n" NOR;
                	target->start_busy(3);
                  weapon2->move(environment(target));
        	      } else
		            {
        	      	msg += CYN "����$n" CYN "����$N" CYN "�����е����У���"
                             "�����磬����Ӧ�ԡ�\n" NOR;
        	      }
        	    message_sort(msg, me, target); 
	       }else
	       {
		          msg = MAG "$N" MAG "����΢΢һ����ͻȻʩչ����" HIW "��������"
                    NOR MAG "��������" + wn + MAG "�����Ŀ������$n" MAG "������"
                      "����֮�С�" NOR;    
              ap = me->query_skill("sword");
              dp = target->query_skill("parry");    		
         
	             if (random(ap) > dp / 2)
               	{                	
                	msg += HIR "\n$n" HIR "���Ų�������ʱ������ţ���������$N"
                               HIR "�Ľ��⵱�С�\n" NOR;
                  target->start_busy(random(ap)/50 + 1);
              	
              	} else
		            {
        	     	msg += CYN "\n����$n" CYN "����$N" CYN "�����е����У���"
                               "�����磬����Ӧ�ԡ�\n" NOR;
        	      } 
        	      message_combatd(msg, me, target);       	      
	        }        
        
        me->start_busy(3+random(4));
        me->add("neili", -600);
       return 1;
        
}


string final(object me, object target, int damage)
{
        int lvl, n;

        lvl = me->query_skill("wushen-jian", 1);
        n = 1 + random(lvl / 20);

        target->affect_by("zhurong_jian",
                ([ "level"    : lvl + random(lvl),
                   "id"       : me->query("id"),
                   "duration" : lvl / 50 + random(lvl / 20) ]));

        return  HIR "ֻ��$N" HIR "��һ�м���硢�����$n"HIR"���о��ɲ���������ʯ�䣬�ѱ�\n"
                HIR "$N"HIR"�������������˴��������죬��Ѫ������������\n" NOR;
}

