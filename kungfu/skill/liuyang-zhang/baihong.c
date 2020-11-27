
// baihong.c ���׺�������updated by Kasumi
#include <ansi.h>
inherit F_CLEAN_UP;
inherit F_SSERVER;

void remove_effect(object me, int amount);

int perform(object me)
{       
        int skill;
        string msg;

        if ((int)me->query_skill("liuyang-zhang", 1) < 300)
                return notify_fail("�����ɽ�����Ʋ�����죬����ʹ�á��׺���������\n");

        if ((int)me->query("neili") < 400 )
                return notify_fail("��������������޷�ʹ�á��׺���������\n");

        if ((int)me->query_temp("lingjiu/baihong"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("liuyang-zhang", 1)/2;

        msg = HIW "\n$N�����ĳ�������һ��������֮�����²��������Ź���������ң���ϳ��Ʒ���\n"
                  "��"+ HIW +"���׺����������˿�$N������ֱ���⣬�����˵ã�\n" NOR;
        message_combatd(msg, me);

        me->add_temp("apply/strike", skill);     
        me->set_temp("lingjiu/baihong", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill :), skill);

        me->add("neili", -100);
        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("lingjiu/baihong"))
        {
                me->add_temp("apply/strike", -amount);
                me->delete_temp("lingjiu/baihong");
                message_combatd(WHT "\n$N����һ�ӣ�������ǰ�ػ��˸��������������²�����������\n"NOR, me);
        }
}
