// youming.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int di);

int exert(object me, object target)
{
        int skill;
        int di;
        object weapon;

        if (target != me)
                return notify_fail("��ֻ������ڤׯ�����Լ���ս������\n");

		if ((int)me->query_skill("linji-zhuang", 1) < 180)
                return notify_fail("����ټ�ʮ��ׯ��򲻹�������ʩչ��ڤׯ��\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("�������������\n");

        if ((int)me->query_temp("youming"))
                return notify_fail("���Ѿ�������ڤׯ�ˡ�\n");
		if (!me->query_temp("weapon"))
                return notify_fail("�����װ����������������ڤׯ��\n");

        skill = me->query_skill("force");

        me->add("neili", -100);
        me->receive_damage("qi", 0);

        if (me->query("reborn")) di = skill / 2; else di = skill / 4;
        
        if (objectp(weapon = me->query_temp("weapon")))
        {
                if (di <= 100)
					message_combatd(MAG "$N" MAG "Ĭ���������ͼ���" +
                                        weapon->name() + MAG "����͸��һ�ɹ�â����˸������\n" NOR, me);                      
                if (di <= 200 && di>100 )
                        message_combatd(MAG "$N" MAG "Ǳ��������ֻ��" +
                                             weapon->name() + MAG "����һ���⻪���������ˣ��������¡�\n" NOR, me);
                 if (di >= 200)             
                message_combatd(MAG "$N" MAG "��ɫһ����������ڤׯ����ʱ��" +
                                    weapon->name() + MAG "�⻪���䣬�����ޱ�ɱ�⡣\n" NOR, me);
        }        
        me->add_temp("apply/damage", di);
        me->set_temp("youming", 1);
        me->start_call_out((: call_other,__FILE__, "remove_effect", me, di :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int di)
{
        if (me->query_temp("youming"))
        {              
                me->add_temp("apply/damage", -di);
                me->delete_temp("youming");
                tell_object(me, "�����ڤׯ������ϣ��������ջص��\n");
        }
}
