// �ƽ�ʽ by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
	object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("�ƽ�ʽֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("�޽���������ƽ�ʽ��\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("�����ڵ������������޷�ʹ���ƽ�ʽ��\n");

	if ((int)me->query_skill("lonely-sword", 1) < 200)
		return notify_fail("��Ķ��¾Ž��������ң��޷�ʹ���ƽ�ʽ��\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("��û�м������¾Ž����޷�ʹ���ƽ�ʽ��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "����$n"HIC"������������һЦ������ʹ�����¾Ž�"HIM"���ƽ�ʽ��"HIC"��һ�������ޱȵش���$n"HIC"��\n" NOR;

        damage = me->query_int() * me->query_skill("lonely-sword",1)/6;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60+random(15),
		                           HIR "$n" HIR "��������ȫȻ�޷��赲$N" HIR "�⾫���һ�У�������⣬��Ѫ������\n" NOR);
		me->start_busy(1);
		me->add("neili", -400);
	
	message_combatd(msg, me, target);

	return 1;
}
