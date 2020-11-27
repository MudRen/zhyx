// �콣ʽ by kasumi

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
		return notify_fail("�콣ʽֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("�޽�������ô콣ʽ��\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("�����ڵ������������޷�ʹ�ô콣ʽ��\n");

	if ((int)me->query_skill("lonely-sword", 1) < 400)
		return notify_fail("��Ķ��¾Ž��������ң��޷�ʹ�ô콣ʽ��\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("��û�м������¾Ž����޷�ʹ�ô콣ʽ��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "���г����������������ʹ�����¾Ž�"HIM"���콣ʽ��"HIC"�����г����Է�����˼�ĽǶȹ���$n"HIC"��\n" NOR;

        damage = me->query_skill("lonely-sword",1) * 10;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
		                           HIR "$n" HIR "��æ�мܣ���֪$N"HIR"�ĳ�������˼��Ĵӷ�϶�����ж��룬��ʱ�̳�һ��Ѫ������\n" NOR);
		
		message_combatd(msg, me, target);
		if (objectp(weapon2 = target->query_temp("weapon")) && random(3)==1)
		{
			  wp = weapon2->name();                                                        
              weapon2->set("consistence", 0);									 
              weapon2->move(environment(me));
		      message_combatd(HIC "ֻ����ž����һ�����죬$n" HIC "��"
                                                "�е�" + wp + HIC "��$N" HIC "��������"
                                                "��Ӧ�����飬���ֵ����ڵ��ϡ�\n" NOR, me, target);                                      
		}  		
		me->start_busy(2);
		me->add("neili", -300);
	

	return 1;
}
