// bizhen-qingzhang  �������� ����
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/bizhen-qingzhang/pengpai"))
                return notify_fail("�㻹����ʹ����һ�У�\n");

        if (me->query_temp("weapon"))
                return notify_fail("�������ֲ���ʩչ�����ȡ���һ�У�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("�����ȡ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (me->query_skill("bizhen-qingzhang", 1) < 180)
                return notify_fail("��ı������ƻ�������죬���������������ˣ�\n");

        if (me->query_skill_mapped("strike") != "bizhen-qingzhang")
                return notify_fail("��û�м����������ƣ��޷�ʹ�á����ȡ���һ�У�");

        if (me->query_skill_prepared("strike") != "bizhen-qingzhang")
                return notify_fail("��û��׼���������ƣ�����ʩչ�����ȡ���\n");

        if (me->query_skill("force") < 300)
                return notify_fail("���ڹ�����Ϊ�������޷����������ˣ�\n");

        if (me->query("max_neili") < 3000)
                return notify_fail("���������Ϊ�������޷����������ˣ�\n");

        if (me->query("neili") < 500)
                return notify_fail("��������������޷����������ˣ�\n");
 
       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "һ����ߣ�˫�ƻ����һ����Ȧ��"
              "���ƶ�������ʱһ����ӿ���ȵľ����粨��һ����$n"
              HIW "ӿ����\n" NOR;
 
        ap = me->query_skill("strike") + me->query_skill("martial-cognize",1);
        dp = target->query_skill("parry") + target->query_skill("martial-cognize",1); 
	damage = ap * 2 / 3 + random(ap);

        me->add("neili", -300);

        if (ap * 2 / 3 + random(ap) < dp)
        {
                msg += HIY "ֻ��$n" HIY "���Ų�æ������һ���������$N" HIY "��һ����\n"NOR;
        } else
        {
                me->add("neili", -300);
                damage = ap / 2 + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70 + random(5),
                                           HIR "ֻ��$n" HIR "�޷��ε�����ӿ���ȵ����������һ�����Ѫ������ֱ�߷ɳ���\n" NOR);
		if (me->query("reborn"))
        	{
        		if (ap * 3 / 5 + random(ap) > dp) 
	        	{
			me->add("neili", -300);
			damage =ap / 2 + random(ap * 2 / 3);
			msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60 + random(5),
						HIW "$N"+HIW"��״������𣬸����ٳ�һ�ƣ���ӿ���ȵ�������$n������У�\n"
						HIR "$n����ȫ�޷��мܣ���Ѫ�����ź����Ĵ��ɽ���\n" NOR);
				if (me->query("breakup"))
				{
					if (ap / 2 + random(ap) > dp)
					{
					me->add("neili", -400);
					damage =ap / 2 + random(ap);
					msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(5),
						HIW "������"+HIW"$N"+HIW"����һ�����ڣ�Ծ��$n�Ϸ��ٳ�һ�ƣ���ӿ���ȵ�������$n������棡\n"
						HIR "$n��$Nһ�����У���Ѫ����ҽ�һ��ײ����档\n" NOR);
					}
				}
			}
			me->start_busy(2 + random(5));	
        	}
        }
        message_combatd(msg, me, target);
        return 1;
}

