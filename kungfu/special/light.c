// lighting.c �޼�����
// Created by Vin 8/5/2002

#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;
inherit F_SSERVER;

string name() { return HIW "�޼��W�" NOR; }

#define LIGHTING "��" HIW "�޼��W�" NOR "��"

int perform(object me, object target)
{
        string msg;
        int ap, dp, damage;

        if (! me->is_fighting())
                return notify_fail(LIGHTING "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        target = me->select_opponent();

        if (! target || ! target->is_character()
           || target->query("not_living"))
                return notify_fail("������˭ʩչ" LIGHTING  "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = me->query_skill("martial-cognize", 1) +
             me->query_skill("jingyi-shengong", 1);

        dp = target->query_skill("martial-cognize", 1) +
             target->query_skill("jingyi-shengong", 1);

        damage = ap + random(ap);
        
        msg = WHT "$N" WHT "ʩչ���g��" HIW "�޼��W�" NOR +
              WHT "���������b�����ȵ�ķ�������ɡ�̩�ﰢ�ա����ء�\n" NOR;

        me->start_busy(1);

        if (ap * 3 / 2 + random(ap) > dp)
        {
                damage = ap * 10 + random(ap * 10);
                target->receive_wound("qi", damage, me);
                target->receive_wound("jing", damage / 2, me);

                msg += HIW "���rֻҊ�����W늏���������M������$n"
                       HIW "���ϣ�ֱ����$n" HIW "�߸[������Ѫ���ĞR��\n" NOR;
        } else
        {
                msg += HIW "���rֻҊ�����W늏���������M������$n"
                       HIW "���ϣ�����ɢ�^��$n" HIW "�s��һ�c����Ҳ�]�С�\n" NOR;
        }
        message_combatd(msg, me, target);
        me->want_kill(target);

        if (! target->is_killing(me))
                target->kill_ob(me);
        return 1;
}

