// updated by kasumi 2007/3/30
#include <ansi.h>
#include <combat.h>

#define FJDH "��" HIG "��������" NOR "��"
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;

        int ap, dp, p, damage, i, count;
        string wp, msg,str;
      

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(FJDH "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" FJDH "��\n");

        if ((int)me->query_skill("force") < 400)
                return notify_fail("����ڹ���򲻹�������ʩչ" FJDH "��\n");

        wp = weapon->name();

        if ((int)me->query_skill("xuantie-jian", 1) < 250)
                return notify_fail("�����������������죬����ʩչ" FJDH "��\n");

        if ((string)weapon->query("material") != "xuantie" && ! environment(me)->query("biwutai") )                                                            
                return notify_fail("ֻ�����������ɵı�������ʹ��" FJDH "��\n");         

        if ((int)me->query("neili") < 600)
                return notify_fail("�����ڵ��������㣬����ʩչ" FJDH "��\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian")
                return notify_fail("��û�м�����������������ʩչ" FJDH "��\n");                  
       
        
        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "ͻȻ��Ŀ���񣬽�������һָ��ת˲���Ѿ��ڿն���"
              "����" + wp + HIW "\n˳��һ�ӣ������ù��������糱ˮ��ӿ��"
              "����ʩ��������������" HIG "��������" HIW "����\n"NOR;


        ap = me->query_skill("sword") + me->query_str() * 5;
        dp = target->query_skill("dodge") + target->query_dex() * 5;
		
		damage = me->query_skill("sword") + me->query_skill("surge-force",1) + me->query_str()*2;
		damage = damage*2 + random(damage*2);
        
       
	    msg += YEL "\n$N��Ȼ��һ������ȫ��������ӿ���ȶ���ѹ��$n��\n"NOR;
        msg += HIB "$n��ǰ�Ѿ���һƬãã���ˣ����еľ����Ѿ�Ť����\n"NOR;


        if (ap * 2/3 + random(ap) > dp)
        {
		     msg +=  HIR "���$n" HIR "ֻ����ȫ���ѱ�������������Ҳ�޷�Ӧ���������ޱߵĽ������ˣ�������Ѫ���������\n" NOR;
		     target->receive_wound("qi", damage, me);
			 str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));			
			 msg += "($n"+str+")\n";
             me->add("neili", -400);               
             count = ap /10;
		}
		else
		{  
		       msg += CYN "$nʹ��������������ֵ���$N���������ˣ���ɫ�������졣\n"NOR;
			   count = ap /14;
	    }
		message_combatd(msg, me, target);

        msg = HIY"\n$N����" + wp + HIY"һ�������ɹ�â����$n��\n"NOR;
        msg += HIC "��ʱ�ƺ����ֲ��أ����䲨��״�Ľ������˻�ǰ�ˣ�һ�˸߹�һ�ˣ����಻����\n"NOR;
        msg += HIR "����������������������������������������������\n"NOR;
        message_combatd(msg, me, target);
          
        me->add_temp("apply/attack", count);
        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2) == 1 && !target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(3 + random(4));
        msg = HIC "$Nʹ��"NOR"" FJDH HIC"����Χ��һ���ָֻ���ƽ����\n"NOR;
        message_combatd(msg, me, target);
        me->add_temp("apply/attack", -count);
                         
        return 1;

}



