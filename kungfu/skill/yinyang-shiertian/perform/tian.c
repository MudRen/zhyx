#include <ansi.h>
#include <combat.h>

#define TIAN "��" HIW "��תǬ��"HIY"ʮ����" NOR "��"

inherit F_SSERVER;



int perform(object me, object target)
{
        int damage,count,i,attack_time;
        string msg, wn, wp,wp2,str;
        object weapon,weapon2;
        int ap, dp;
        me = this_player();

        
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(TIAN "ֻ����ս���жԶ���ʹ�á�\n");
       
        if ((int)me->query_skill("yinyang-shiertian", 1) < 500)
                return notify_fail("���������תʮ�������򲻹�������ʩչ" TIAN "��\n");

	weapon = me->query_temp("weapon");

        if (! objectp(weapon))
        {     if (me->query_skill_mapped("unarmed") != "yinyang-shiertian"
                        || me->query_skill_prepared("unarmed") != "yinyang-shiertian")
                              return notify_fail("��û��׼��������תʮ�����죬�޷�ʹ��" TIAN "��\n");
        }
        else if (objectp(weapon) && (string)weapon->query("skill_type") != "sword"
                      && (string)weapon->query("skill_type") != "blade")
                              return notify_fail("��ʹ�õ��������ԣ��޷�ʩչ" TIAN "��\n");

             if (objectp(weapon) && me->query_skill_mapped("sword") != "yinyang-shiertian"
                 && (string)weapon->query("skill_type") == "sword")
                              return notify_fail("�㻹û�м���������תʮ�����죬�޷�ʩչ" TIAN "��\n");
             
             else if (objectp(weapon) && (string)weapon->query("skill_type") == "blade"
                      && me->query_skill_mapped("blade") != "yinyang-shiertian")
                              return notify_fail("�㻹û�м���������תʮ�����죬�޷�ʩչ" TIAN "��\n");    

        if ((int)me->query("max_neili") < 20000)
                return notify_fail("���������Ϊ���㣬����ʩչ" TIAN "��\n");

        if ((int)me->query("neili") < 2500)
                return notify_fail("�����ڵ���������������ʩչ" TIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");        
        
        message_sort(HIM "\n$N" HIM "����������תʮ�����죬�·��������������ʣ�"
                     HIM "�������Ͼ�ѧ\n" HIW "               ��"HIC" �� ת Ǭ ��"HIY" ʮ ��"HIR" ��" HIW " ��" HIM " ��\n\n" NOR, me, target);
                     
        ap = me->query_skill("yinyang-shiertian", 1) + me->query_skill("force", 1) + me->query_skill("martial-cognize", 1);
        dp = target->query_skill("dodge", 1) + target->query_skill("parry", 1) + target->query_skill("martial-cognize", 1); 
        attack_time = 1+(int)(me->query_skill("yinyang-shiertian", 1)/55);
        if (attack_time > 12) attack_time =12;
       
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                message_sort(HIW "$N" HIW "����������Ю����֮�����ӿ�����$n" 
                             HIW "����������\n" NOR, me, target);
		
                if (ap * 3 / 2 + random(ap) > dp)
                {
			damage = ap + random(ap);
			if (me->query_skill("yinyang-shiertian",1)>999 && random(5)>2)
			{
				target->receive_damage("qi", damage, me);
				target->receive_wound("qi", damage * 2 / 3, me);
				target->receive_damage("jing", damage, me);
				target->receive_wound("jing", damage * 2 / 3, me);
				msg = HIY "$n" HIY "�����мܣ�����" HIY "$N" HIY "���ھ����಻����" HIY "$n" HIY "�����ش���\n" NOR;
			}else
			{
				if (me->query_temp("weapon"))
				{
        	                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, (i + 1) * 20,
                	                                          HIR "$n" HIR "����������$N" HIR
                        	                                  "���ھ���������룬��ͷһ�����һ��"
                                	                          "����Ѫ��\n" NOR);
	                        } else
        	                {
                	                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, (i + 1) * 20,
                        	                                  HIR "$n" HIR "����������$N" HIR
                                	                          "���ھ���������룬��ͷһ�����һ��"
	                                       	                  "����Ѫ��\n" NOR);
        	                }
			}
                } else
                {
                       	msg = CYN "$n" CYN "����˫�ۣ������мܣ���"
                              "$N" CYN "���ھ�ж����\n" NOR;
                }
		me->add("neili", -200);
                message_sort(msg, me, target);

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);
        }
        me->start_busy(3+random(4));
        return 1;        
}

