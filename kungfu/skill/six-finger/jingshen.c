// jingshen.c ��������
// looo/2001/6/28
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, ob;
        string msg;
        int skill, skill2;

        int i;
        i = me->query_skill("six-finger", 1) - 50;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill_mapped("finger") != "six-finger")
                return notify_fail("��û�м��������񽣣��޷�ʩչ���������񡹡�\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("��û��׼��ʹ�������񽣣��޷�ʩչ���������񡹡�\n");

        skill = me->query_skill("six-finger", 1);
        skill2 = me->query_skill("sun-finger", 1);
        if (skill < 200)
                return notify_fail("�����������Ϊ���ޣ��޷�ʹ�á��������񡹣�\n");

        if (skill2 < 200)
                return notify_fail("���һ��ָ��Ϊ���ޣ��޷�ʹ�á��������񡹣�\n");

        if (me->query_skill("force") < 400)
                return notify_fail("����ڹ���򲻹�������ʩչ���������񡹣�\n");

        if (me->query("max_neili") < 5000)
                return notify_fail("���������Ϊû�дﵽ�Ǹ����磬�޷���ת�����γɡ��������񡹣�\n");

        if (me->query_temp("weapon"))
                return notify_fail("������ǿ��ֲ���ʩչ���������񡹣�\n");

        if (me->query("neili") < 500)
                return notify_fail("������������������޷�ʩչ���������񡹣�\n");

        msg = HIY "$N" HIY "ʮָ������������������򰴣���������������������"
              HIY "$N" HIY "ָ����ӿ�����������ķ�����\n"
              HIR "���������������ص���ֱ���$nüë���䣬������ͨ����Ҳ����ǰ����֣�\n" NOR;
             message_vision(msg, me,target);

        me->add_temp("apply/attack", i);
        me->add_temp("apply/damage", 250);
        {
        msg =  HIC "-------------------------�ٳ彣 \n"NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);


        msg =  HIW "-------------------------���� \n"NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);


        msg =  HIY "------------------------ �г彣 \n"NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);


        msg =  HIG "-------------------------�س彣 \n"NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);


        msg =  HIM "-------------------------������ \n"NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);


        msg =  HIR "-------------------------���̽� \n"NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        }
        me->add_temp("apply/attack", -i);
        me->add_temp("apply/damage", -250);
        me->add("neili",-800);
        me->start_busy(4);
        return 1;
}
