// wang.c ��Ů�����ľ�
// looo/2001/6/23
#include <ansi.h>
#include <combat.h>
inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        string msg;

        int skill, i;
        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("ֻ����ս���в�����ᡸ���项��\n");


        if (me->query("gender") == "����")
                return notify_fail("Ů���ҵ��������������ף�\n");


        if (me->query("neili") < 200)
                return notify_fail("�������������\n");

        if (me->query_temp("wang"))
                return notify_fail("���Ѿ����롸"HIW"����"NOR"���ľ����ˡ�\n");

        if (me->query_skill("yunv-xinfa",1) < 200)

                return notify_fail("�����Ů�ķ����������졣\n");

        if (me->query_skill_mapped("sword") != "yunv-jian")
                return notify_fail("��û�м�����Ů����!\n");

	if (!me->query_temp("weapon") ||
	    me->query_temp("weapon")->query("skill_type") != "sword")
		return notify_fail("��ʹ�õı�������!\n");

        skill = me->query_skill("yunv-xinfa");
        i = skill / 50 + 1;             
        if (random(i) > 3)

        {
message_combatd(HIW "$N" HIW "��Ȼ���ף�������������ˮ����ȫ�����������������ϣ�\n"              
                        HIW "����ͻ�䣬һ������������࣬һ���ȴ������ƴ������Ѱ����\n"
                        HIW "һ��һʽ������֮�ʣ�������쳣׼ȷ��\n" NOR, me);
        tell_object(me, HIM "������Ե���������ԣ��㲻����������龳�硣\n");
        me->add_temp("apply/attack", skill / 3); 

        me->set_temp("wang", 1);
        me->add("neili", -100);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 3 :), skill);


         }
       else {
                msg = HIM "$N" HIM "�������飬һʱ֮�䲻�ܽ������龳�硣\n" NOR;
                me->start_busy(3);
            }
        message_combatd(msg, me, target);
        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("wang"))
        {
                me->add_temp("apply/attack", -amount);

                me->delete_temp("wang");
                tell_object(me, "һ����ʹ���ֹ����������ĵ����£�����֮�����.\n");
        }
}
