// �佣ʽ by kasumi

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
		return notify_fail("�佣ʽֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("�޽���������佣ʽ��\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("�����ڵ������������޷�ʹ���佣ʽ��\n");

	if ((int)me->query_skill("lonely-sword", 1) < 800)
		return notify_fail("��Ķ��¾Ž��������ң��޷�ʹ���佣ʽ��\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("��û�м������¾Ž����޷�ʹ���佣ʽ��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "Ю����Ȼ�۽�$n" HIC "������ʯ��ͻȻ����Ծ��һ�����£����Ƕ��¾Ž�"HIM"���佣ʽ��"HIC"��\n" NOR;

        damage = me->query_skill("lonely-sword",1) * 6;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60+random(30),
		                           HIR "$n" HIR "��æ���з�������ϧΪʱ����������ͷ�ϵġ��ٻ�Ѩ�������ζ��������������\n"
								   HIR"������Ѩ��������$n"HIR"����֮�࣬������ɢ��\n" NOR);
		
		message_combatd(msg, me, target);
		if (random(2)==1){
			target->set("neili",0);
		}else{
			target->add("neili",-target->query("neili")*2/3);
		}
		me->start_busy(2)+random(3);
		me->add("neili", -300);
	

	return 1;
}
