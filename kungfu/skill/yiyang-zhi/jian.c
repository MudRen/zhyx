#include <ansi.h>
#include <combat.h>

#define JIAN "��" HIR "Ǭ��" HIY "����" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, i, damage,count,busytime;
        string msg;

        if (userp(me) && ! me->query("can_perform/yiyang-zhi/jian"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(JIAN "ֻ�ܿ���ʩչ��\n");       

        if ((int)me->query_skill("yiyang-zhi", 1) < 180)
                return notify_fail("��һ��ָ��������죬����ʩչ" JIAN "��\n");

        if ((int)me->query_skill("jingluo-xue", 1) < 180)
                return notify_fail("��Ծ���ѧ�˽ⲻ��������ʩչ" JIAN "��\n");

        if (me->query("max_neili") < 3000)
                return notify_fail("���������Ϊ���㣬����ʩչ" JIAN "��\n");       

        if (me->query_skill_mapped("finger") != "yiyang-zhi")
                return notify_fail("��û�м���һ��ָΪָ��������ʩչ" JIAN "��\n");       

        if (me->query("neili") < 400)
                return notify_fail("�����ڵ��������㣬����ʩչ" JIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");


		ap = me->query_skill("force") + me->query_skill("finger")+ me->query_skill("jingluo-xue", 1);
        dp = target->query_skill("force") + target->query_skill("dodge")+ target->query_skill("jingluo-xue", 1);
		busytime = 2;


        if (me->query_skill_mapped("force") == "xiantian-gong" && (int)me->query_skill("xiantian-gong", 1) > 279)
     	{   
	     	msg = HIY "��ʱֻ��$N" HIY "����" HIW "��������" HIY "����Ϊ" HIR
                      "�����ھ�" HIY "����ָ�⣬��һ��ָ���ַ�����$n" HIY "ȫ����"
                      "��ҪѨ��\n" NOR;  
            if (ap * 2 / 3 + random(ap) > dp)
            { 
                damage = ap + random(ap);
				me->add("neili", -200);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                           HIR "$n" HIR "ֻ��ȫ��һ�ȣ�$P" HIR "��"
                                           HIW "���칦" HIR "Ǭ��" HIY "����" HIR
                                           "����ʱ������룬�������ú�¯�����һ��"
                                           "��Ѫ��\n" NOR);
                message_combatd(msg, me, target);
				busytime = busytime + 1;
            } else
            {
				me->add("neili", -100);
                msg += CYN "$n" CYN "��$N" CYN "��ָ������ӿ������"
                       "�����мܣ�����������Ծ������\n" NOR;
                message_combatd(msg, me, target);
            }
		}

        msg = HIR "$N" HIR "��������������顣һָ��һָ�ؽ���������������������$n" HIR "�����"
              "���Ա����������֡�\n"NOR;
        message_combatd(msg, me, target);
		count = ap/12;

        me->add_temp("apply/attack", count);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->add_temp("apply/attack", -count);
        me->add("neili", -250);
        me->start_busy(busytime + random(3));
        return 1;
}
