// shang.c ���־�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("�����ذ���ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "whip")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("force") < 300)
                return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

        if (me->query_skill("jiuyin-shengong", 1) < 300)
                return notify_fail("��ľ�������Ϊ������Ŀǰ����ʹ�����ذ���\n");

        if (me->query("neili") < 400)
                return notify_fail("��������������޷�ʹ�����ذ���\n");

        if (me->query_skill_mapped("whip") != "jiuyin-shengong")
                return notify_fail("��û�м��������񹦣�����ʹ�����ذ���\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "��Ȼ��Ц�����е�" + weapon->name() +
              HIY "һ����ʱ������������һ���������Ŵ�������$n" + HIY "��\n" NOR;

                ap = me->query_skill("whip", 1) * 3 + me->query("dex") * 20 + 
                     me->query_skill("martial-cognize", 1); 
                dp = target->query_skill("parry") + target->query("dex") * 20 + 
                     target->query_skill("martial-cognize", 1); 

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 1)*2;
                me->add("neili", -300);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 120,
                                           HIR "ֻ��$p" HIR "һ���ҽУ�" + weapon->name() +
                                           HIR "��Ȼ����$p" + HIR "�����ϣ������Ѿ�"
                                           "�Դ�����Ѫ�ɽ����ߣ��Ҳ����ԣ�\n" NOR);
        } else
        {
                me->add("neili", -100);
                me->start_busy(3);
                msg += CYN "����$p" CYN "����������������ס��"
                       CYN "$P" CYN "�����Ī���һ����\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

