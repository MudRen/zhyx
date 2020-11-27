// freeze.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object met);

int exert(object me, object target)
{
	int ap;
        int dp;
        int damage;
	int skill;
        string msg;

        if (target == me || ! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

        if ((skill = me->query_skill("lengyue-shengong", 1)) < 150)
                return notify_fail("��������񹦻�򲻹����޷����ú�����\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("�����������!");

	if (me->query_temp("hu/freeze"))
		return notify_fail("���Ѿ����������º����ˣ�\n");

	if (!target || target == me)
	{
                message_vision(HIW "$N" HIW "Ĭ�������񹦣�һ�ɺ���������ɢ������"
                      HIW "�����ܵ�ʱѩ��ƮƮ��\n" NOR,me);
		me->set_temp("hu/freeze",1);
       	        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill);
		return 1;		
	}

        msg = HIW "$N" HIW "Ĭ�������񹦣�һ�ɺ���ӭ������$n"
              HIW "�����ܵ�ʱѩ��ƮƮ��\n" NOR;

	ap = me->query_skill("force");
        dp = me->query_skill("force");

        me->start_busy(2);

        if (ap / 2 + random(ap) > random(dp))
        {
                damage = ap / 2 + random(ap / 2);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", random(damage), me);
                if (target->query("neili") > damage)
                        target->add("neili", damage);
                else
                        target->set("neili", 0);

                msg += HIG "$n" HIG "��Ȼ����һ��͸�Ǻ��⣬��ʱ��"
                       "�����ѪҺ������Ҫ�����ˡ�\n" NOR;
                target->start_busy(1);
        } else
                msg += HIY "$n" HIY "�е�һ�������ĵ׷�����æ"
                       "�˶��ֿ����������¡�\n" NOR;

        message_combatd(msg, me, target);

	me->set_temp("hu/freeze",1);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill);

	return 1;
}

void remove_effect(object me)
{
	if (!me) return;
        if ((int)me->query_temp("hu/freeze"))
        {
                me->delete_temp("hu/freeze");
                tell_object(me, "������º���������ϣ��������ջص��\n");
        }
}
