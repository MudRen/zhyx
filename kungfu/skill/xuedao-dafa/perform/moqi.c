// ��΢����������
//����Խ�ߣ�����Խ�ߡ�˵�����͵�ͬѧ��ӼӸ���
//2�ڸ���ⶥ
// buy gentl
//update 2012.11.29

#include <ansi.h>
#include <combat.h>

#define MOQI "��" HIR "ħ��Ѫɱ" NOR "��"

inherit F_SSERVER;


int perform(object me, object target)
{
        mapping prepare;
        string msg, wp;
        int skill, ski_value;        
        int damage;       
        int ap, dp, p, str, amount, jj;
        object weapon;


        skill = me->query_skill("xuedao-dafa", 1);

        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail(""MOQI" ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" MOQI "��\n");
  
        if( me->query_skill("xuedao-dafa", 1) < 400 )
                return notify_fail("���Ѫ���󷨹������㡣 \n");

        if( me->query_skill("force", 1) < 400 )
                return notify_fail("����ڹ������á� \n");
        
        if(me->query("neili") < 1000)
                return notify_fail("�������������\n");
        
        if (me->query_skill_mapped("force") != "xuedao-dafa") 
                return notify_fail("������û�м���Ѫ����Ϊ�ڹ�������ʩչ"MOQI"��\n"); 

        if (me->query_skill_mapped("blade") != "xuedao-dafa")
                return notify_fail("��û�м�������ΪѪ���󷨣�����ʩչ" MOQI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");


        msg = HIR "$N" HIR "��������һ�����ţ���ʱһ����Ѫ����" + weapon->name() + HIR"�ϣ�ֻ��һƬѪ��"HIR "��ס��Ӱ��$n" HIR "��ͷ���䡣\n" NOR;

        ap = me->query_skill("blade")+me->query_skill("force")+me->query_skill("dodge")+me->query_skill("parry");
        dp = target->query_skill("force") + target->query_skill("parry") + target->query_skill("dodge");     
        ski_value=0;
        ski_value=(int)me->query("shen") / -8000000;
        if (ski_value<=0) ski_value=1;
        if (ski_value>10) ski_value=10;
        damage = 600 + skill * ski_value / 4;
        amount = ski_value * 50;
        ap += amount;
        me->add_temp("apply/damage", amount);
       

       

       // ��һ��
	    msg += HBWHT "\n��ħ�����¡�\n" NOR ; 
       
        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "Ѫ���У�" HIR"$N����ӰͻȻ���֣�" + weapon->name() + HIR "����$n������Դ���������Ѫ�������أ� \n" NOR);
        } else
        {
                msg += CYN "����$n" CYN "������ã����Ų�æ�������$N"
                       CYN "�ı�ɱһ����\n"NOR;
        }

        // �ڶ���

	    msg += HBYEL "\n��ħ���¡��\n"NOR; 
       
        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "Ѫ���У�" + weapon->name() + HIR "��������Ѫ�ɽ���$n" HIR"ֻ����ǰһ��Ѫ�죬���������󺿣�\n" NOR);

        } else
        {
                msg += CYN "$n" CYN "ʹ��������������ڽ�$N"
                       CYN "��һ���㿪��˿������\n" NOR;
        }

        //// ������

	    msg += HBGRN "\n��ħ���컡� \n"NOR; 
       
        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                           HIR "Ѫ���У�" + weapon->name() + HIR "��������Ѫ�ɽ���$n" HIR"ֻ����ǰһ��Ѫ�죬���������󺿣�\n" NOR);

        } else
        {
                msg += CYN "����$n" CYN "������ã����Ų�æ�������$N"
                       CYN "�ı�ɱһ����\n"NOR;
        }

        //// ������

	    msg += HBCYN "\n��ħ��������\n"NOR; 
       
		 if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                          HIR "ֻ��������Ѫ������Ѫ��ĵ���ȴ�ַ·𻯳�һƬѪ��������ס" HIR"$n����Ӱ��\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "ʹ��������������ڽ�$N"
                       CYN "��һ���㿪��˿������\n" NOR;
        }
      
          


if ((int)target->query("qi")> 0&& me->is_fighting(target) && (int)me->query_skill("xuedao-dafa", 1) > 499 && !userp(target))    //�޸�1499Ϊ499����ȷ�ϡ�
        	 {
                    ap = me->query_skill("blade");
                    dp = target->query_skill("force"); 
					ap += amount;

        msg += HIY "\n������$N�Բм�����Ѫ��ת����ɱ����\n
            ����$N���Ϸ���һ��ǿ���ɱ������\n
    ��$N����ɱ���𽥵ؾۼ�,��" + weapon->name() + HIY "���γ���ħ����\n
            $Nٿ�ش��һ������ħ �� Ѫ ɱ����\n\n" NOR;
			
		target->receive_damage("qi", amount, me);	//�����˺����500

        
        if( ap * 2 / 3 + random(ap) > dp)  
        {
                msg += HIR  "$NͻȻ��ͷһ��������ֻ��$N�������һ��Ѫ����$n��ȥ����\n
����Ѫ����֮
            ����ɱ�� ��ħ Ѫ �� ɱ��\n\n
$n�⵽ǰ��δ�еĴ��,��$NҲ���˲��ᡣ\n" NOR;

                damage = 600 + skill * ski_value;
                damage += random(damage/2);
                
                target->start_busy(5 + random(ski_value));
                target->receive_damage("qi", damage, me);
				target->receive_wound("qi", damage/2, me);
                me->receive_wound("qi", me->query("qi")* 1 /100);
        }
        else if( random(3) > 2 )
        {
                msg += HIR BLINK"$N������ת����ɱ��������,�Ե��˺���Ӱ�졣\n" NOR;
                me->receive_wound("qi", me->query("qi")*1/100);
        }
        else
        {
                msg += HIR BLINK"$n�ܵ�ǿ���ɱ���˺����������á�\n" NOR;
                me->receive_wound("qi", me->query("qi")* 1 /100);
                target->receive_damage("qi", (int)me->query_skill("xuedao-dafa", 1), me);
                target->start_busy(3 + random(ski_value));
        }
           }   

	    message_combatd(msg, me, target);
	    me->add("neili", -ski_value * 500);
          me->add_temp("apply/damage", -amount);
          me->start_busy(3 + random(4));

        return 1;
}

