// leidong �׶�����
// by winder 98.12

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int perform(object me)
{
        int skill, count, count1;

        if ((int)me->query_temp("leidong"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

 	if (me->query_temp("weapon"))
		return notify_fail("ֻ�п��ֲ���ʹ���׶����졣\n");

       if ((int)me->query("neili") < 500)
                return notify_fail("�����ڵ�����������\n");

        if ((int)me->query_skill("zixia-shengong",1) < 100)
                return notify_fail("�����ϼ����Ϊ��������\n");

        if ( me->query_skill_mapped("force") != "zixia-shengong")
                return notify_fail("����ʹ�ڹ�������ȭ�ķ������ϣ�\n");  

        skill = me->query_skill("cuff");
        if (skill < 135)
                return notify_fail("�������ȭ��Ϊ��������\n");

        me->add("neili", -400);
        message_combatd(HIM "$N" HIM "��������һ���������϶�ʱ"
                        "������ʢ������Խ��Խ�أ�\n" NOR, me);

        count = skill / 20;

        if (me->is_fighting())
                me->start_busy(2);

        me->add_temp("apply/str", count);
        me->add_temp("apply/dex", count);
        me->set_temp("leidong", 1);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :), skill / 3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if ((int)me->query_temp("leidong"))
        {
                me->add_temp("apply/str", -amount);
                me->add_temp("apply/dex", -amount);
                me->delete_temp("leidong");
                tell_object(me, CYN "����׶�����������ϣ��������ջص��\n" NOR);
        }
}

