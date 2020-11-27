// sunxin.c ���ľ�

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

private void remove_effect(object me, int amount);

int perform(object me)
{
        string msg;
        object target;
        int skill, ap, dp, attack_decrease;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qishang-quan",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("�����ľ���ֻ����ս����ʹ�á�\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("��������������ߣ�\n");

        if( (int)me->query_skill("cuff") < 60 )
                return notify_fail("���ȭ���������ң��޷���������ȭ�ĸ����ܾ���\n");

        if( (int)me->query_skill("qishang-quan", 1) < 60)
                return notify_fail("������ȭ����Ϊ���������ܹ�������ľ�! \n");

       if( (int)me->query_skill("force", 1) < 60)
                  return notify_fail(HIM "��Ļ����ڹ���Ϊ���㣬�������ʹ�����ľ�! \n" NOR);

        if( me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("��û�м�������ȭ���޷��������ľ���\n");
        if (me->query_skill_prepared("cuff") != "qishang-quan")  
                return notify_fail("��û��׼��ʹ������ȭ���޷�ʩչ�����ľ�����\n");  
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ�ô��У�\n");


        msg = HIY "$N��������ʹ������ȭ�ܾ��еġ�" HIR "���ľ�" HIY "����˫ȭ������������$n��ȥ��\n"NOR;
        message_vision(msg, me, target);

        ap = me->query("combat_exp") + skill * 500;
        dp = target->query("combat_exp") / 2;
        if( dp < 1 )
                dp = 1;
        if( random(ap) > dp || !living(target))
        {
                if(userp(me))
                        me->add("neili",-100);
                msg = HIG "$N����ȭ������ף�$n����$N��ɽ��ʯ��һȭ����ʱ������𣬲���������У�\n"NOR;
                attack_decrease = (int)target->query("apply/attack") / 10;
                target->add_temp("apply/attack", -attack_decrease);
                target->start_busy(2);
                me->start_busy(2 + random(2));
                call_out("remove_effect", skill/40, target, attack_decrease);
        }
        else
        {
                msg = HIG "ֻ��$n���Ų�æ������һ���������$N�ı�ɱһ����\n"NOR;
                if(userp(me))
                        me->add("neili",-100);
                me->start_busy(3);
        }
        message_vision(msg, me, target);

        return 1;
}

private void remove_effect(object me, int amount)
{
        if (!me)
                return;
        me->add_temp("apply/attack", amount);
        tell_object(me, "��о��������˳�������е�����ȭ���ľ����������ˡ�\n");
}
