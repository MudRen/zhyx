//created by kasumi.

#include <ansi.h>
#include <combat.h>

#define PO "��" HIW "�Ż���" HIR "��" HIW "��" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
        int ap, dp;

        //if (userp(me) && ! me->query("can_perform/liuyang-zhang/pori"))
             //   return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }
	if (! target || ! me->is_fighting(target))
                return notify_fail(PO "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(PO "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("bahuang-gong", 1) < 400)
                return notify_fail("��˻�����Ψ�Ҷ��𹦻�򲻹�������ʩչ" PO "��\n");

        if ((int)me->query_skill("liuyang-zhang", 1) < 400)
                return notify_fail("�����ɽ�����Ʋ�����죬����ʩչ" PO "��\n");

        if (me->query("max_neili") < 4500)
                return notify_fail("���������Ϊ���㣬����ʩչ" PO "��\n");

        if (me->query_skill_mapped("strike") != "liuyang-zhang")
                return notify_fail("��û�м�����ɽ�����ƣ�����ʩչ" PO "��\n");

        if (me->query_skill_prepared("strike") != "liuyang-zhang")
                return notify_fail("��û��׼����ɽ�����ƣ�����ʩչ" PO "��\n");

        if (me->query("neili") < 800)
                return notify_fail("�������������㣬����ʩչ" PO "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "$N" HIW "�����������������е�ˮ¶Ϊ�����������У��̶�����һ��,�������������㼤����$n��\n"NOR;

	      
        ap = me->query_skill("force") + me->query_skill("strike") + me->query_skill("dodge") + me->query_skill("parry");
        dp = target->query_skill("force")*2 + target->query_skill("parry") + target->query_skill("dodge");
        if (ap * 3 / 5 + random(ap) > dp)   
        	{
        		damage=ap+random(ap/2);
        		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
        	                                   HIR "$n" HIR "��æ�ֵ�������Ȼ������$N"
                                             HIR "��������������$n���ϣ�һ������Ѫ���˿ڴ�ӿ����\n" NOR);
            me->add("neili", -250);
          }
        else
        	{
        		msg += CYN "$n" CYN"�ۼ���Ƭ��������ǰ��ֻ���������գ��˾��������佫��Ƭ���˿���\n"NOR;
        		me->add("neili", -100);        		
        	}
        msg += HIG "\n������" HIG "$N" HIG "���˻�����Ψ�Ҷ������������ޣ�ȫ�������ŷ�������һ��"
              "��$n" HIG "ͷ����Ȼ���䡣\n" NOR;
        		     

        if (ap * 2 /3  + random(ap) > dp)
	      {
                damage = 0;
                if (me->query("max_neili") > target->query("max_neili") * 2)
                {
                        msg += HIR "��ʱֻ�����ۡ���һ����$N" HIR "һ�ƽ�$n"
                               HIR "ͷ���ĵ÷��飬�Խ��Ľ�������̱����ȥ��\n"
                               NOR "( $n" RED "���˹��أ��Ѿ�������в���"
                               "��ʱ�����ܶ�����" NOR ")\n";
                        damage = -1;
                } else
		            {
			            damage = (int)me->query_skill("bahuang-gong", 1) * 8;
                    	damage += random(damage / 2);

	                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80+random(20),
        	                                   HIR "$n" HIR "��æ�ֵ�������Ȼ������$N"
                                                   HIR "�ƾ����ˮ��ӿ�����ڣ������������"
                                                   "�߹ǡ�\n" NOR);
		             }
		             me->add("neili", -200);
		             me->start_busy(3+random(3));
	       } else
	       {
		        msg += CYN "$p" CYN "��$P" CYN "�ƾ����ȣ����Ƶֵ���"
                                           "ס����������������������������\n" NOR;
		        me->start_busy(3+random(3));
		        me->add("neili", -100);
	       }
	message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);

	return 1;
}
