// �뽣ʽ by kasumi

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
		return notify_fail("�뽣ʽֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("�޽���������뽣ʽ��\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("�����ڵ������������޷�ʹ���뽣ʽ��\n");

	if ((int)me->query_skill("lonely-sword", 1) < 300)
		return notify_fail("��Ķ��¾Ž��������ң��޷�ʹ���뽣ʽ��\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("��û�м������¾Ž����޷�ʹ���뽣ʽ��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "���һ��������ʹ�����¾Ž�"HIM"���뽣ʽ��"HIC"�����н������ǵ������$n"HIC"��\n" NOR;

        damage = me->query_skill("lonely-sword",1) * 10;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
		                           HIR "$n" HIR "�����ֿ������ϻ��߼��������滮�ƶ������ڵأ�����Ѫ����ֹ��\n" NOR);
		if (objectp(equipment = target->query_temp("armor/hands")) && random(3)==1)
		{
		  name = equipment->name();      
		  equipment->move(environment(me));
		  message_combatd(HIW "$n" HIW "���ϵ�" + name + HIW "�����Ƶ����ڵء�\n" NOR, me, target);
		}
		if (objectp(equipment = target->query_temp("armor/cloth")) && random(3)==1)
		{
		  name = equipment->name();      
		  equipment->move(environment(me));
		  message_combatd(HIW "$n" HIW "���ϵ�" + name + HIW "�����Ƶ����ڵء�\n" NOR, me, target);
		}
		if (objectp(equipment = target->query_temp("armor/armor")) && random(3)==1)
		{
		  name = equipment->name();      
		  equipment->move(environment(me));
		  message_combatd(HIW "$n" HIW "���ϵ�" + name + HIW "�����Ƶ����ڵء�\n" NOR, me, target);
		}
		
		me->start_busy(2);
		me->add("neili", -300);
	
	message_combatd(msg, me, target);

	return 1;
}
