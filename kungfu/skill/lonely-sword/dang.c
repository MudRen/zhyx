// ����ʽ by kasumi

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
		return notify_fail("����ʽֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("�޽�������õ���ʽ��\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("�����ڵ������������޷�ʹ�õ���ʽ��\n");

	if ((int)me->query_skill("lonely-sword", 1) < 700)
		return notify_fail("��Ķ��¾Ž��������ң��޷�ʹ�õ���ʽ��\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("��û�м������¾Ž����޷�ʹ�õ���ʽ��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "������ǰһ�ݣ���������������һ�㣬��������$n" HIC "�����Ƕ��¾Ž�"HIM"������ʽ��"HIC"��\n" NOR;

        damage = me->query_skill("lonely-sword",1) * 11;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85,
		                           HIR "$n" HIR "������$N"HIR"������·�����֮�������ش���\n" NOR);		
		
		if (! target->query_temp("lonely_dang"))
        {           
                target->add_temp("apply/force", -500);
                target->add_temp("apply/parry", -500);
                target->add_temp("apply/dodge", -500);
                target->set_temp("lonely_dang", 1);
        		msg += HIM "$nֻ���û��������ϣ�ȫ�����������һ˿˿Զ���Լ���ȥ������֮����\n" NOR;
		}
		message_combatd(msg, me, target);
		call_out("dang_end", 5 + random(8), me, target);
		me->start_busy(2);
		me->add("neili", -300);
	

	return 1;
}

void dang_end(object me, object target)
{
        if (target && target->query_temp("lonely_dang"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "��������һ��������ɫ��"
                                        "��ת�죬�������ö��ˡ�\n" NOR, target);                       
                }                
                target->add_temp("apply/force", 500);
                target->add_temp("apply/parry", 500);
                target->add_temp("apply/dodge", 500);
                target->delete_temp("lonely_dang");
        }
        return;
}