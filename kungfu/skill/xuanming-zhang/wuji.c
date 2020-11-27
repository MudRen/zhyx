#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ڤ�޼�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������ֲ���ʹ����ڤ�޼���\n");         

        if ((int)me->query_skill("xuanming-shengong", 1) < 150)
                return notify_fail("�����ڤ�񹦻�򲻹���ʹ������ڤ�޼���\n");

        if ((int)me->query_skill("xuanming-zhang", 1) < 150)
                return notify_fail("�����ڤ���Ʋ�������������ʹ����ڤ�޼���\n");

        if ((int)me->query("max_neili") < 2000)
                return notify_fail("���������Ϊ���㣬�޷�ʹ����ڤ�޼���\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("��������������޷�ʹ����ڤ�޼���\n");

        msg = MAG "$N������ڤ�񹦣�ȫ���ֳ�һ����������Ȼ��˫�Ʒ��ڣ�ʩչ��������ڤ\n�޼���Я���������������֮�����ƾ��ѹ���$n��\n"NOR;  

        lvl = me->query_skill("xuanming-zhang", 1);
        ap = me->query_skill("strike") + me->query("str") * 10;
        dp = target->query_skill("dodge") + target->query("dex") * 10;
        me->start_busy(4);
        if (ap / 2 + random(ap) > dp || !living(target))
        { 
                damage = ap + random(ap / 2);
                me->add("neili", -400);
                target->affect_by("xuanming_poison",
                               ([ "level" : me->query("jiali") + random(me->query("jiali")),
                                  "id"    : me->query("id"),
                                  "duration" : lvl / 50 + random(lvl / 20) ]));
                                  msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
               MAG "$nֻ����ǰ��Ӱ�ζ���ͻȻ���ؿ�һ����֪���Ʋ��ֻ���ؿڴ�һ��\n�������𣬾�������������\n" NOR);
        } else
        {
                msg += HIY "$n����$N������ӿ����æ����Ծ����\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
