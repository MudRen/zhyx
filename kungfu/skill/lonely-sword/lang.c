// �˽�ʽ by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
	object weapon;
        string msg,msg1;
        int ap, dp, i;
        int damage;
 
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�þ��С�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("�޽���������˽�ʽ��\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("�����ڵ������������޷�ʹ���˽�ʽ��\n");

	if ((int)me->query_skill("lonely-sword", 1) < 500)
		return notify_fail("��Ķ��¾Ž��������ң��޷�ʹ���˽�ʽ��\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("��û�м������¾Ž����޷�ʹ���˽�ʽ��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "���˵��������ǰһ�������Ƕ��¾Ž�"HIM"���˽�ʽ��"HIC"����ʱ�������������㺣�˼���$n"HIC"��\n" NOR;
        message_sort(msg, me, target);
		for (i = 0; i < 6; i++)
		{
		   msg1=HIY"              ��"+chinese_number(i+1)+HIY"�ˣ�\n"NOR;
		  
		   damage = me->query_skill("lonely-sword",1)*3/2;
		   damage = damage + random(damage/2);
		   if (me->query("character") == "������"){
				damage = damage * 1.25;
		   }
		   msg1 += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
		                           HIR "$n" HIR "��ȫ�޷�������Ϊ$N" HIR "�Ľ������ˣ����ۡ����³�һ����Ѫ��\n" NOR);	
		   message_combatd(msg1, me, target);
		}
		if (me->query("character") == "������"){
				me->start_busy(3);
		   }else{
				me->start_busy(3+random(4));
		}
		me->add("neili", -600);	

	return 1;
}
