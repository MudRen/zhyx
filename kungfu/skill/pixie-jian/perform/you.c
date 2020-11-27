// you.c ��ڤһ��
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp, bs;
        int damage;
        object weapon;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (me->query("gender") != "����" && !me->query("tianmo_jieti"))
                return notify_fail("����Ա��������ڹ���⣬�޷�ʹ�ô˾��У�\n");  

        if (userp(me) && ! me->query("can_perform/pixie-jian/you"))
                return notify_fail("�㻹����ʹ�á���ڤһ������\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ڤһ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��û��װ��������������һ�С�\n");

        if( me->query_skill_mapped("sword") != "pixie-jian") 
                return notify_fail("�㲢û��ʹ�ñ�а�������޷�ʹ�ô˾��У�\n"); 

        if (me->query_skill("pixie-jian", 1) < 400)
                return notify_fail("��ı�а������������죬����ʹ����ڤһ����\n");

        if (me->query("neili") < 300)
                return notify_fail("�����������������ʹ����ڤһ����\n");
 
        msg = HIR "$N" HIR "��������ǰȥ����ʱ��ƽ�$n" HIR
              "������" + weapon->name() + HIR "��Ȼ����$p��Ҫ����\n" NOR;
 
        ap = me->query_skill("pixie-jian", 1) * 3 / 2 + me->query("dex") * 20 +
             me->query_skill("martial-cognize", 1);
        dp = target->query_skill("parry") + target->query("dex") * 20 +
             target->query_skill("martial-cognize", 1);

        me->start_busy(2);
        me->add("neili", -40);

        if (ap * 2 / 3 + random(ap) < dp || !living(target))
        {
                msg += HIG "Ȼ��$n" HIG "�ֵ��÷�����$N" HIG
                       "�Ĺ���һһ���⡣\n" NOR;
        } else
        {
                target->start_busy(1);
                me->add("neili", -60);
                damage = ap / 4 + random(ap / 4) - random(80);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                           HIR "$n" HIR "��æ���ˣ�������ң��������$N"
                                           HIR "���У���Ѫ����һ�أ�\n" NOR);
        }

        message_combatd(msg, me, target);
        return 1;
}

