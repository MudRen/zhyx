// �ý�ʽ by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
	    object weapon;
        string msg, wp;
        int ap, dp;
        int damage;
		object weapon2;
 
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("�ý�ʽֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("�޽���������ý�ʽ��\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("�����ڵ������������޷�ʹ���ý�ʽ��\n");

	if ((int)me->query_skill("lonely-sword", 1) < 600)
		return notify_fail("��Ķ��¾Ž��������ң��޷�ʹ���ý�ʽ��\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("��û�м������¾Ž����޷�ʹ���ý�ʽ��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "���г�������һ����ʹ�����¾Ž�"HIM"���ý�ʽ��"HIC",������ҫ������$n"HIC"��\n" NOR;

        damage = me->query_skill("lonely-sword",1) * 8;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
		                           HIR "$n" HIR "һ㶲�֪������ܣ�Ƭ��֮����Ȼ���У���Ѫ�������������������ң�\n" NOR);
		
		message_combatd(msg, me, target);
		target->set("jingli",0);
		target->set_temp("no_perform", 1);
        call_out("liao_end", 3 + random(5), me, target);
		me->start_busy(2);
		me->add("neili", -300);
	

	return 1;
}

void liao_end(object me, object target)
{
        if (target && target->query_temp("no_perform"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "��������һ��"
                                        "������ɫ�ɰ�ת�죬��������"
                                        "���ˡ�\n" NOR, target);

                        tell_object(target, HIY "��е������ҵ�����"
                                            "����ƽ����������\n" NOR);
                }
                target->delete_temp("no_perform");
	}
	return;
}
