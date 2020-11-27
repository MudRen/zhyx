// hun.c �����߾�

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

        skill = me->query_skill("qijue-cuff", 1);

        if (! me->is_fighting(target))
                return notify_fail("�����߾�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill_mapped("cuff") != "qijue-cuff") 
                return notify_fail("��û�����߾�ȭ���޷�ʹ�á������߾������У�\n");

        if (me->query_skill_prepared("cuff") != "qijue-cuff")
                return notify_fail("��û��׼��ʹ���߾�ȭ���޷�ʩչ�������߾������С�\n");

        if (skill < 100)
                return notify_fail("����߾�ȭ�ȼ�������������������\n");

        if (objectp(weapon = me->query_temp("weapon")) ||
            objectp(weapon = me->query_temp("handing")) )
                return notify_fail("��������˫�ֲ���ʹ��ȭ�����С�\n");

        if (me->query("neili") < 500)
                return notify_fail("�������������\n");
        
        ap = me->query_skill("cuff") + me->query_skill("force");
        ap += me->query("jiali");
        ap += me->query("jianu");

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIY "\n$N" HIY "�������ߣ�ͻȻ���һ����$n" HIY "һ��֮�ʣ�$N" HIY "˫ȭ�Ӷ���\n"
              HIY "����$n" HIY "ȫ����������������ȭ��ȭͷ��������$n��\n" NOR;
        message_combatd(msg, me, target);

        n = (int)me->query("tianmo_jieti/times");
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        msg = HIW "һ��ȭ���ȥ��$n" HIW "������������������$N" HIW "�����ڼ�������˫ȭ��ӭ�������\n\n" NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIY "ֻ���á����ꡱһ����$n" HIY "һ���ʹ���۵�һ���³�һ��" HIR "��Ѫ" HIY "�����ʵʵ�ر�����һȭ��\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
		str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIW "$n" HIW "�����ڹ���ȫ����������ӭ��$N" HIW "��ȭ·�������顱���죬��$N" HIW "����һ������൱��\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(me->query("id")) ) target->kill_ob(me);
	me->add("neili",-damage/3);
        return 1;
}


