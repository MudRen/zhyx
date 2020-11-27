// qi.c ���ν���

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define QI "��" HIG "���ν���" NOR "��"

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg,str;
        int ap, dp;

        if (! target) target = offensive_target(me);


        if (userp(me) && ! me->query("can_perform/liumai-shenjian/qi"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(QI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("force") < 420)
                return notify_fail("����ڹ���򲻹���ʹ����" QI "��\n");

        if (me->query("max_neili") < 5000)
                return notify_fail("���������Ϊ��������ʹ�����Ϭ����" QI "��\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("��������������޷�ʹ��" QI "��\n");

        if (me->query_skill("liumai-shenjian", 1) < 200)
                return notify_fail("�����������Ϊ���ޣ��޷�ʹ��" QI "��\n");

        if (me->query_skill_prepared("finger") != "liumai-shenjian")
                return notify_fail("��û��׼�������񽣣��޷�ʹ��" QI "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "$N" HIG "��ָһ����һ���������׵����ν���ֱ��$n" HIG "��ǰ��ȥ��\n" NOR;  

        ap = me->query_skill("finger")+  (me->query_skill("jingluo-xue", 1) + me->query_skill("lamaism", 1)  + me->query_skill("buddhism", 1)) / 2 ;
        dp = target->query_skill("force") + (target->query_skill("jingluo-xue", 1) + target->query_skill("lamaism", 1)  + target->query_skill("buddhism", 1)) / 2;
        weapon = target->query_temp("weapon");
       
        if (ap * 3 / 5 + random(ap) > dp)
        { 
                damage = ap + (int)me->query_skill("yiyang-zhi", 1) + (int)me->query_skill("canhe-zhi", 1) + random(ap * 6);
                me->add("neili", -300);
                if (! objectp(weapon) || weapon->query("skill_type") == "pin")                     
				{
						msg +=  HIR "$n" HIR "ֻ������ǰһ���ʹ����Ѫ�Դ��ڼ����������ǰ��ʱһ�ڣ�\n" NOR;
				        target->receive_wound("qi",damage,me);
		                str =  COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		                msg += "($n"+str+")\n" ;	
				}
                else
                if (weapon->is_item_make() || weapon->query("damage") > 180 || weapon->query("skill_type") == "hammer")
				{
                        msg += HIR "$n" HIR "��" + weapon->name() + HIR "��ͼ�мܣ�"
                                     HIR "������ɽ������Ϭ����͸��" + weapon->name() +
                                     HIR "ֱ���$n" HIR "������Ѫ������������Ҫ��ת������\n" NOR;
				        target->receive_wound("qi",damage,me);
		                str =  COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		                msg += "($n"+str+")\n" ;	
		        }
                else
                {
                        msg +=  HIR "$n" HIR "��ת" + weapon->name() + HIR "��������"
                                             "ǰ��ֻ��ž��һ����" + weapon->name() +
                                      HIR "������أ��������죡\n$n" HIR "����"
                                            "���������ۡ�������һ����Ѫ����ɫ��ĲҰס�\n" NOR;
                        target->receive_wound("qi",damage,me);
		                str =  COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		                msg += "($n"+str+")\n" ;	
                        weapon->move(environment(me));
                        weapon->set("no_wield", weapon->name() + "�Ѿ�����ˣ�û��װ���ˡ�\n");
                        weapon->set_name("�����" + weapon->name());
                        weapon->set("value", 0);
                }
        } else
        {
                msg += CYN "����$p" CYN "�ڹ���Ϊ������Ὣ����������������Ρ�\n" NOR;
        }
        message_combatd(msg, me, target);

		me->start_busy(1+random(2));

        return 1;
}

