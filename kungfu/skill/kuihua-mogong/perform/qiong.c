// qiong �����޾�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define QIONG "��" HIR "�����޾�" NOR "��"
 
int perform(object me, object target)
{
	string msg;
        int ap, dp, ap1, dp1,attack_time,i,damage;
        object weapon;

        if (userp(me) && ! me->query("can_perform/kuihua-mogong/qiong"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
	        return notify_fail(QIONG "ֻ����ս���жԶ���ʹ�á�\n");

	if (me->query_skill("kuihua-mogong", 1) < 250)
		return notify_fail("��Ŀ���ħ����������죬����ʹ��" QIONG "��\n");

        if ((int)me->query("max_neili") < 3800)
                return notify_fail("���������Ϊ���㣬����ʩչ" QIONG "��\n");

	if (me->query("neili") < 200)
		return notify_fail("��������������޷�ʩչ" QIONG "\n");

        if (weapon = me->query_temp("weapon"))
        {
                if (weapon->query("skill_type") != "sword" &&
                    weapon->query("skill_type") != "pin" &&
					weapon->query("skill_type") != "xsword")
                        return notify_fail("�������õĲ��ǽ�����ôʩ"
                                           "չ" QIONG "��\n");
        } else
        {
                if (me->query_skill_prepared("unarmed") != "kuihua-mogong")
                        return notify_fail("�㲢û��׼��ʹ�ÿ�"
                                           "��ħ�������ʩչ" QIONG "��\n");
        }
        if (weapon && me->query_skill_mapped("sword") != "kuihua-mogong")
                return notify_fail("��û��׼��ʹ�ÿ���ħ��������ʩչ" QIONG "��\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "kuihua-mogong")
                return notify_fail("��û��׼��ʹ�ÿ���ħ��������ʩչ" QIONG "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

       

        ap = me->query_skill("dodge");
        dp = target->query_skill("dodge");
		
		if (( random(ap/4) > dp) && me->query("reborn"))
        {	
				msg = HIR "\n$N" HIR "��Хһ������Ȼ������ǰ��һ�о�ֱϮ$n" HIR "Ҫ�����ٶ�֮�죬��"
				"�˼���δ��������δ�š�\n" NOR;
                msg += HIR "��һ���ٶ�֮����ȫ������$n" HIR "�����󣬱�$N"
                       HIR "��һ�����û����˵���Ҫ����$n" HIR "��̲�����Ƶ�̱����ȥ��\n" NOR;
                message_combatd(msg, me, target);
                me->add("neili", -400);
                target->unconcious();  
                return 1;
		}else{
				ap1 = me->query_skill("dodge") + me->query_skill("parry");
                dp1 = target->query_skill("dodge") + target->query_skill("parry");
				attack_time = (int) me->query_skill("kuihua-mogong", 1) / 100;
				if (attack_time>15){
					attack_time=15;
				}
				if (!me->query("reborn")){
					attack_time=1;
				}
				msg ="";
				for (i = 0; i < attack_time; i++){
					if (ap1 * 3 / 4 + random(ap1) > dp1)
					{
					 msg += HIR "\n$N" HIR "��Хһ������Ȼ������ǰ��һ�о�ֱϮ$n" HIR "Ҫ�����ٶ�֮�죬��"
					"�˼���δ��������δ�š�\n" NOR;
                     damage = ap * 2 + random(ap);
                     msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 85 + random(15),
                                                HIR "��һ���ٶ�֮����ȫ������$n" HIR "������$n" HIR
                                                "���һ������Ȼ���С�\n" NOR);
                     me->add("neili", -150);
                     me->start_busy(1 + random(2));
					}
					else
					{
					 msg += HIR "\n$N" HIR "��Хһ������Ȼ������ǰ��һ�о�ֱϮ$n" HIR "Ҫ�����ٶ�֮�죬��"
					"�˼���δ��������δ�š�\n" NOR;
                     msg += HIC "$n" HIC "֪�����в��ƣ���æ���ܣ�û��һ����\n" NOR;
                     me->add("neili", -80);
                     me->start_busy(1 + random(2));
					}
				}
                message_combatd(msg, me, target);
                return 1;
		}

	return 1;
}
