// haishi.c ������¥

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int delta;
        int i, count;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/sanfen-jianshu/haishi"))
                return notify_fail("�㲻��ʹ�á�������¥����һ������\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("��������¥��ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("sword", 1) < 350)
                return notify_fail("��Ľ�����Ϊ������Ŀǰ����ʹ�á�������¥����\n");

        if (me->query_skill("sanfen-jianshu", 1) < 350)
                return notify_fail("������ֽ�������Ϊ����������ʹ����һ������\n");

        if (me->query_skill("dodge") < 350)
                return notify_fail("����Ṧ��Ϊ�������޷�ʹ�á�������¥����\n");

        if ((int)me->query("dex") < 45)
                return notify_fail("�����̫��޷�ʩչ��������¥����\n");
 
        if (me->query("neili") < 1000)
                return notify_fail("�������������\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "���һ��������" + weapon->name() +
              HIW "����֮�ʣ�ͻȻȦת��ʹ�����ֽ����Ķ���֮��"
              "��������¥����һ��֮��\n�����̺����У���ʽ������"
              "������������ʵʵ���������⾶ֱ����$n"
              HIW "��\n\n" NOR;

        ap = me->query_skill("sword") + me->query_skill("force") + me->query_skill("dodge");
        dp = target->query_skill("dodge") + target->query_skill("parry");
        if (ap + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 70,
                                           HIR "$n" HIR "��ȫ�޷�������ʵ��ֻ��һ���ĵĴ�ʹ��һ���ҽУ��ѱ�$N"
                                           HIR "�����Ľ��д��С�\n" NOR);

                if (ap / 2 + random(ap) > dp)
                {
                        damage /= 2;
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                                   HIR "\n$N" HIR "��$n" HIR "�ش�֮�²�������������"
                                                   HIR "��Цһ��������" + weapon->name() +
                                                   HIR "�������ֹ���һ��������$p" HIR "�ؿڡ�\n" NOR);
                }

        } else
        {
                msg += HIC "$n" HIC "��״���μ��ˣ��ܿ���$N"
                       HIC "�����Ĺ�����\n" NOR;
        }

        message_combatd(msg, me, target);

        ap = me->query_skill("parry") + me->query_skill("force");
        dp = target->query_skill("force");

        msg = HBGRN "\n���$N" HBGRN "Ծ����У�һ�С�"HBGRN"���лþ�" HBGRN"��������" 
                  + weapon->name() + HBGRN "���裬�����������������Ĺ���$n" HBGRN "��\n" NOR;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "��ȫ�����˷�����"
                       "ãȻ֮�ж�����ײ������ȴ������������Ѫ���졣\n" NOR;
                count = ap / 8;
        } else
        {
                msg += HIC "$n" HIC "�ۿ�����Ϯ����ʩ���������"
                       "����$N" HIC "����������������\n" NOR;
                count = ap / 20;
        }
        message_sort(msg, me, target);
        me->set_temp("perform_sanfenjian/lian", 1);
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
        me->delete_temp("perform_sanfenjian/lian");
        me->add("neili", -300 - random(300));
        me->start_busy(1 + random(2));

        return 1;
}