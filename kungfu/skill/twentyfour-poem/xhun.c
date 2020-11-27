// xhun.c �ۻ�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        object weapon;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("twentyfour-poem", 1);

        if (! me->is_fighting(target))
                return notify_fail("�ۻ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill_mapped("cuff") != "twentyfour-poem") 
                return notify_fail("��û����ʫ����ʮ��Ʒ���޷�ʹ�á��ۻ롹���У�\n");

        if (me->query_skill_prepared("cuff") != "twentyfour-poem")
                return notify_fail("��û��׼��ʹ��ʫ����ʮ��Ʒ���޷�ʩչ���ۻ롹���С�\n");

        if (skill < 100)
                return notify_fail("���ʫ����ʮ��Ʒ�ȼ�������������������\n");

        if (objectp(weapon = me->query_temp("weapon")) ||
            objectp(weapon = me->query_temp("handing")) )
                return notify_fail("��������˫�ֲ���ʹ���Ʒ����С�\n");

        if (me->query("neili") < 500)
                return notify_fail("�������������\n");
        
        ap = me->query_skill("cuff") + me->query_skill("force");
        ap += me->query("jiali");
        ap += me->query("jianu");

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIC "\n$N" HIC "���κ�ת��˫ȭƮ��������������תȫ���������ԣ������е���\n"
              HIW "�������裬�����ڳ䡣������룬����Ϊ�ۡ��߱�������̫�ա�\n" 
              HIW "�Ļ����ƣ����ȳ��硣�������⣬���价�С���֮��ǿ����֮���\n" 
              HIC "���������У�" HIG "ʫ����ʮ��Ʒ" HIC "��ǿʽ" HIY "���ۻ롹" HIC "������գ���Х������\n\n" NOR; 

        message_combatd(msg, me, target);

        n = (int)me->query("tianmo_jieti/times");
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        msg = HIW "\n$N" HIW "��ȭ��һ��������$n" HIW "������ȴ����̶������������\n" NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIW "$n" HIW "�����������ҽ�һ�����Ѿ������ػ��С�\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
		str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIC "$n" HIC "���Ʋ���͵����һԾ����ܿ�����\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(me->query("id")) ) target->kill_ob(me);
	me->add("neili",-damage/3);
        return 1;
}


