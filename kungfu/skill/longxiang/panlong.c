//   panlong.c ����ʽ
//   looo/2001/6/21
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int bs;
        int damage;

        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))

                return notify_fail(" ����ʽֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") ||
            me->query_temp("secondary_weapon"))
 return notify_fail("�������ֲ���ʹ������ʽ\n");

        if (me->query_skill("force") < 150)
                return notify_fail("����ڹ�����Ϊ����,����óȻʹ������ʽ��\n");

        if (me->query_skill("longxiang", 1) < 150)
                return notify_fail("������������������죬����óȻʹ������ʽ��\n");

        if (me->query("max_neili") < 1500)
                return notify_fail("�����������������óȻʹ������ʽ��\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("����������㣬�޷�ʩչ����ʽ��\n");
        if (me->query_skill_mapped("force") != "longxiang")
                return notify_fail("��û�м������������������óȻʹ������ʽ��\n");

        msg = HIC "$N" HIC "���Ծ�𣬾ޱ�һ����������������ľ���--����ʽ��\n"
              HIC "�����ɼ��������ڼ���������ƾ���ֱ��" HIC "$n" HIC "��ȥ \n"NOR;

        ap = me->query_skill("longxiang") + me->query("str") * 10;


 if (random(me->query_skill("force")) > target->query_skill("force")/3 || !living(target))
        {
                damage = ap + 500;
                bs = 3;
                me->add("neili", -450);
                me->start_busy(bs);


         msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 80,
                       HIR "���" HIR "$n" HIR "��" HIR "$N" HIR "���������㣬һ��֮�£���Ȼ���˵ֵ����ƾ�Ӳ����͸���������\n"NOR);
        } else

        {

                me->start_busy(4);
                msg += HIY "$n" HIY "����������������ϸ�룬һ�������������������������һ��\n"NOR;
        }
                message_combatd(msg, me, target);

                return 1;
}

