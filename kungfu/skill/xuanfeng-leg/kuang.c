// kuangfeng.c  ������

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, ob;
        string msg;
        int i;
        int extra;
i = me->query_skill("bibo-shengong", 1) * 3 / 10;
        if( !target ) target = offensive_target(me);
        if( !me->is_fighting() )
                return notify_fail("����������ֻ����ս���жԶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("������������ʼʱ�������ű�����\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ�ˮƽ������\n");

        if ((int)me->query_skill("luoying-shenzhang", 1) < 100 ||
            me->query_skill("xuanfeng-leg",1) < 100)
                return notify_fail("������ƹ��򻹲����ң��޷�ʹ�ÿ�������\n");

        if (me->query_skill_prepared("unarmed") != "xuanfeng-leg")
                return notify_fail("��û��׼�������ȷ����޷�ʩչ��������\n");

        msg = HIY "$N" HIY "ʹ���һ���������������������Ʈ��"
              "�������������ɣ�\n" NOR;
         message_vision(msg, me);
         me->add_temp("apply/attack", i);
        {
                msg = YEL  "\n$N" YEL"���������ƣ�����һ�Ÿ����߳���\n"NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                msg = HIM  "��Ӱ�У�" HIM "$N" HIM "����������ƴ����û���$n��\n"NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                msg = YEL "\n$N" YEL "��" YEL "$n" YEL "�Ż��󿪣�����������˫����������" YEL "$n��\n"NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                msg = HIM  "$N" HIM "ԽսԽ�£���Χ����һ�����磬ʹ��" HIM "$n" CYN "�����巽��\n"NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                msg = YEL "\n$N" YEL "���ǹ�է�֣������Դ���Ȼ֮ɫ����" YEL "$n��\n"NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                msg = HIM "$N" HIM "��Хһ��������෢����Ȼת��" HIM "$n" HIM"��󣬷�������һ�ƣ�\n"NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        }
        me->add("neili", -100);
        me->start_busy(1 + random(2));
        me->add_temp("apply/attack", -i);
        return 1;
}
