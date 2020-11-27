// �ؽ�ʽ by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
	object weapon;
        string msg,name;
        int ap, dp;
        int damage;
		object equipment;
 
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("�ؽ�ʽֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("�޽�������ýؽ�ʽ��\n");
		
	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("�����ڵ������������޷�ʹ�ýؽ�ʽ��\n");

	if ((int)me->query_skill("lonely-sword", 1) < 200)
		return notify_fail("��Ķ��¾Ž��������ң��޷�ʹ�ýؽ�ʽ��\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("��û�м������¾Ž����޷�ʹ�ýؽ�ʽ��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
		damage = me->query_skill("lonely-sword",1) * 10;
		
        msg = HIC "����$N" HIC "����һ�գ�����ʹ�����¾Ž�"HIM"���ؽ�ʽ��"HIC"��һ���ȳ��������Ծ̲��������Ȼ����$n"HIC"��\n" NOR;       
		
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
		                           HIR "$n" HIR "��ǰһ����˲������������\n" NOR);
		if (random(5)>1){
			msg += HIR "$n" HIR "�н����������������˼�����һʱ���޷����֣�\n" NOR;		 
			target->start_busy(3 + random(7));
		}
		
		me->start_busy(2);
		me->add("neili", -300);
	
	message_combatd(msg, me, target);

	return 1;
}
