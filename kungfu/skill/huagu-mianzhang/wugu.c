// wugu.c �޹�
// smallbear 11/3/2002

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg,force;
        int ap, dp;
        int count;
        int i,j;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("���޹ǡ�ֻ����ս���жԶ���ʹ�á�\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���޹ǡ�ֻ�ܿ���ʹ�á�\n");
                
        if ((int)me->query("neili") < 500)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("huagu-mianzhang", 1) < 120)
                return notify_fail("��Ļ������ƻ�򲻹����޷�ʹ�á��޹ǡ����У�\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���Ϊ�������޷�ʹ�á��޹ǡ����У�\n");

        if (! me->query_skill_prepare() &&
            me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("������û��׼��ʹ�û������ƣ��޷�ʹ�á��޹ǡ����У�\n");
    if(!stringp(force = me->query_skill_mapped("force"))
                ||force!="busi-shenlong")
                return notify_fail("��û��ʹ�����������ķ����޷�ʹ�����У�\n");

        msg = HIW "ֻ����$N�ؽڿ������죬������Լ͸���ɺ�����˫�۱�������޹�һ�㣡\n"NOR;
        ap = me->query_skill("strike") + me->query("str") * 10;
        if (living(target))
                 dp = target->query_skill("parry") + target->query("dex") * 10;
        else     dp = 0;
        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 20;
                msg += HIW "$n��$P��ʽ���죬��֪����ô�мܣ�������$N��˫���ѵ���ǰ��\n"NOR;
        } 
        
        else
        {
                msg += HIW "$n���Ӿ���ɲ�Ǽ��ѿ���$N����ʽ�������мܡ�\n" NOR; 
                count = 0;
        }

        message_vision(msg, me, target);
        me->add_temp("apply/attack", count);

        me->add("neili", -200);
        j = random(6);
        if (j < 3) j = 3;
   for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1);
        me->add_temp("apply/attack", -count);

        return 1;
}


