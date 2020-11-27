#include <ansi.h>
#include <combat.h>

#define JUESHA "��" HIW "������ɲ�ơ�" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int i, ap, dp, pp, count;
        object weapon;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("������ɲ�ơ�ֻ����ս���жԶ���ʹ�á�\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("������ɲ�ơ�ֻ�ܿ���ʹ�á�\n");
                
        if (me->query("max_neili") < 2200)
                return notify_fail("���������Ϊ���������޷�ʩչ������ɲ�ơ���\n");

        if ((int)me->query("neili") < 1200)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("tie-zhang", 1) < 250)
                return notify_fail("������ƻ�򲻹����޷�ʹ�á�����ɲ�ơ���\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ�������޷�ʹ�á�����ɲ�ơ���\n");

        if (me->query_skill_mapped("strike") != "tie-zhang")
                return notify_fail("��û�м��������Ʒ�������ʩչ������ɲ�ơ���\n");

        if (me->query_skill_prepared("strike") != "tie-zhang")
                return notify_fail("������û��׼��ʹ�������Ʒ�������ʩչ������ɲ�ơ���\n");

        if (me->query_skill_prepared("cuff") == "tiexian-quan"
            || me->query_skill_prepared("unarmed") == "tiexian-quan" )
                return notify_fail("ʩչ������ɲ�ơ�ʱ�����Ʒ����˺�����ȭ������\n");

        if ((string)me->query_skill_mapped("force") != "tianlei-shengong")
                return notify_fail("����뼤�������񹦲���ʩչ��������ɲ�ơ���\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

                msg = HIC "$N" HIC "һ��ŭ�ȣ����ڼ�������������ת��˫�۶�Ȼ�������ߡ�ֻ���ƿ�֮�����죬\n"
                HIC "ͻȻ$N" HIC "˫��ӭ��һ�ӣ��ó���ǧ��Ӱ����������Ƶľ������У�����\n" 
                HIC"\n           " HIC"��������������\n"
                HIC"           " HIC"������ɲ�Ʃ�\n"
                HIC"           " HIC"��������������\n" NOR;

        ap = me->query_skill("strike");
        dp = target->query_skill("parry");
        pp = me->query_skill("tianlei-shengong",1) + me->query_skill("tiezhang-xinfa",1);
        ap += pp / 3;

        if (ap * 2 / 3 + random(ap) > dp)
        { 
                damage = ap + random(ap);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200,
                                           HIR "$n" HIR "���Ʋ�͸������ʵ��$N" HIR
                                           "˫������$p" HIR "ǰ�أ������꿦�ꡱ��"
                                           "�����������߹ǡ�\n" NOR);
	        message_combatd(msg, me, target);
        } else
        {
                msg += CYN "$n" CYN "��$N" CYN "�������ƷǷ�������"
                       "�����мܣ�����������Ծ������\n" NOR;
	        message_combatd(msg, me, target);
        }
     
            msg = HIW "������$N" HIW "˫��һ����ת�����񹦣�һ�ɻ���������ھ���ӿ���ȣ�������ɽ\n"
                     HIW"����֮����$n" HIW "ϯ�������\n" NOR;
	        message_combatd(msg, me, target);

        count = ap / 6;
        me->add_temp("apply/attack", count);
	 me->add_temp("apply/unarmed_damage", count / 2);
              
       
        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
        	COMBAT_D->do_attack(me, target, 0, i*2);
        }

        me->add("neili", -800);
        me->start_busy(4 + random(3));
        me->add_temp("apply/attack", -count);
		me->add_temp("apply/unarmed_damage", -count / 2);
        return 1;
}


