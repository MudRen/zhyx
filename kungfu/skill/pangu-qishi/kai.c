#include <ansi.h>
#include <combat.h>

#define KAI "��" HIY "����ٵ�" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (userp(me) && ! me->query("can_perform/pangu-qishi/kai"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(KAI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "hammer")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" KAI "��\n");

        if (me->query_skill("force") < 300)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" KAI "��\n");

        if (me->query_skill("pangu-qishi", 1) < 180)
                return notify_fail("����̹�������Ϊ����������ʩչ" KAI "��\n");

        if (me->query("neili") < 400)
                return notify_fail("�����������������ʩչ" KAI "��\n");

        if (me->query_skill_mapped("hammer") != "pangu-qishi")
                return notify_fail("��û�м����̹����ƣ�����ʩչ" KAI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = WHT "$N" WHT "һ���Ϻȣ�����" + weapon->name() +
              WHT "��ɽ��Ρ�ţ�Я�ſ���ٵ�֮����$n" WHT "�������£�\n" NOR;

        ap = me->query_skill("hammer") + me->query("str") * 10;
        dp = target->query_skill("force",1)*3/2 + target->query("con") * 10;
        
        if (target->query("family/family_name") == "��ɽ��")
             ap=ap*2;
        else if (target->query("family/family_name") == "��ɽ��")
        	   ap=ap*2;
        	else if (target->query("family/family_name") == "��ɽ��")       
        	   ap=ap*2;
        else ap=ap;

        if (ap * 2/3 + random(ap) > dp)
        {
                damage = ap * 2 + random(ap*2);
                me->add("neili", -200);
                
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           HIR "$n" HIR "��ܲ�������$N" HIR "��"
                                           "һ�������ؿڣ���ʱһ�����죬���ݰ����"
                                           "��ɳ�ȥ��\n" NOR);
        } else
        {
                me->add("neili", -100);                
                msg += HIC "����$n" HIC "�����ĵ���$N" HIC "������"
                       "�ľ��������а�������ʱ���������Ρ�\n"NOR;
        }
        message_combatd(msg, me, target);
        msg = WHT "������$N" WHT "һ�����ȣ���ת����" + weapon->name() + WHT "����$n��\n" NOR;
        if (ap * 2/3 + random(ap) > dp)
        {
                damage = ap * 2 + random(ap*2);
                me->add("neili", -200);
                me->start_busy(3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           HIR "$n" HIR "��ܲ�������$N" HIR "��"
                                           "һ������Ƥ���ɡ�\n" NOR);
        } else
        {
                me->add("neili", -100);                
                msg += HIC "����$n" HIC "�����ĵ���$N" HIC "������"
                       "�ľ��������а�������ʱ���������Ρ�\n"NOR;
        }
        me->start_busy(3);
        message_combatd(msg, me, target);

        return 1;
}
