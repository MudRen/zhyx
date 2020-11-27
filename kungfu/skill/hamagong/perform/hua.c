// hua.c һ�����Ű� by kasumi 2015.2.24

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define HUA "��" HIW "һ�����Ű�" NOR "��"

int perform(object me, object target)
{
        string msg,str;
        int n,damage;

        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! me->query("reborn")){
                return notify_fail("��û�о�����ת���������޷������󡹦��ѧ��һ�����Ű١���\n");
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("��󡹦��һ�����Ű١�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(HUA "ֻ�ܿ���ʹ�á�\n");
                
        if ((int)me->query("neili") < 1000)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("hamagong", 1) < 500)
                return notify_fail("��ĸ�󡹦��򲻹����޷�ʩչ" HUA "��\n");

        if ((int)me->query_skill("force") < 600)
                return notify_fail("����ڹ���Ϊ�������޷�ʩչ" HUA "��\n");

        if (me->query_skill_prepared("unarmed") != "hamagong")
                return notify_fail("������û��׼��ʹ�ø�󡹦���޷�ʩչ" HUA "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
			  

        msg = HIY"$N"HIY"����󡱵Ĵ�������������󡹦������˫��һ��˫���뷢����ǰ�Ƴ�......\n"
              HIG"��һ��ʵ��$N"HIG"��������֮���ۣ�$n��Ȼ���ܵ�ɽ�麣Х��ľ���Ϯ����\n" NOR;   
        damage = me->query_skill("force",1)/3+me->query_skill("hamagong",1)/2;
        damage = damage + random (damage/2);

		msg += HIM"                      ͻ��\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 20,
		                           HIR "$n" HIR "��ʱ������Ѫ���������ۡ����³���һ����Ѫ��\n" NOR);
		msg += HIG"                      ͻ��\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
		                           HIR "$n" HIR "��ʱ������Ѫ���������ۡ����³���һ����Ѫ��\n" NOR);
		msg += HIY"                      ͻ��\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
		                           HIR "$n" HIR "��ʱ������Ѫ���������ۡ����³���һ����Ѫ��\n" NOR);
		msg += HIR"                      ͻ��\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
		                           HIR "$n" HIR "��ʱ������Ѫ���������ۡ����³���һ����Ѫ��\n" NOR);
		msg += HIC"                      �ƣ�\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
		                           HIR "$n" HIR "��ʱ������Ѫ���������ۡ����³���һ����Ѫ��\n" NOR);
		msg += HIW"                      �ƣ�\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
		                           HIR "$n" HIR "��ʱ������Ѫ���������ۡ����³���һ����Ѫ��\n" NOR);
		msg += HIY"                      �ƣ�\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
		                           HIR "$n" HIR "��ʱ������Ѫ���������ۡ����³���һ����Ѫ��\n" NOR);
		msg += HIG"                      �ƣ�\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90,
		                           HIR "$n" HIR "��ʱ������Ѫ���������ۡ����³���һ����Ѫ��\n" NOR);
		msg += HIW"                  һ�����Ű٣�\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
		                           HIR "$n" HIR "�������ͬ���ߵķ��ݰ���˳�ȥ��\n" NOR);
		
		
		message_combatd(msg, me, target);
        me->add("neili", -900);
        me->start_busy(3+random(4));
        return 1;
}
