//luan ��˫���� 3��+6��
#include <ansi.h>
#include <combat.h>

#define LUAN "��" HIM "��˫����" NOR "��"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        int damage,count,i;
        string msg;
        int ap, dp;

        me = this_player();

        if (userp(me) && ! me->query("can_perform/yeqiu-quan/luan"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LUAN "ֻ����ս���жԶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������ֲ���ʹ��"	LUAN "��\n");

        if ((int)me->query_skill("yeqiu-quan", 1) < 500)
                return notify_fail("���Ұ��ȭ��������죬����ʹ��" LUAN "��\n");

        if (me->query_skill_prepared("unarmed") != "yeqiu-quan"
           && me->query_skill_prepared("finger") != "yeqiu-quan"
           && me->query_skill_prepared("hand") != "yeqiu-quan"
           && me->query_skill_prepared("cuff") != "yeqiu-quan")
                return notify_fail("��û��׼��Ұ��ȭ���޷�ʹ��" LUAN "��\n");
                                
        if ((int)me->query("neili", 1) < 1000)
                return notify_fail("����������̫��������ʹ��" LUAN "��\n");

/*        if (userp(target))
                return notify_fail(HIW "�㲻�ܶ����ʹ�����У�\n" NOR); */

        if ((int)me->query_skill("force", 1) < 500)
                return notify_fail("����ڹ���򲻹�������ʩչ" LUAN "��\n");

        if ((int)me->query("max_neili") < 10000)
                return notify_fail("���������Ϊ���㣬����ʩչ" LUAN "��\n");

        if ((int)me->query("neili") < 2000)
                return notify_fail("�����ڵ���������������ʩչ" LUAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");


        msg = HIW "\n$N" HIW "��һ�������һ����"HIM"��ɱ����˫���裡"HIW"��\n"
	      HIW "˫�ֲ��ϱ任��"HIM"��ʯͷ��"HIG"��������"HIW"��"HIB"������"HIW"������ʽ������$n"HIW"��\n" NOR;

	//ʯͷ
        ap = me->query_skill("yeqiu-quan", 1) + me->query_str()*5;
        dp = target->query_skill("force", 1) + target->query_str()*5;
	msg += HIW "\n$N" HIW "ʹ��һ��"HIM"��ʯͷ��"HIW"��˫ȭ���ճ���$n"HIW"�����ۻ�ȥ��\n" NOR;
	if (ap * 2 / 3 + random(ap) > dp)
	{
        	me->add("neili", -300);
		damage = ap+random(ap/4);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                   HIR "$nһ���ҽУ����������������������������è�ۣ�\n" NOR);
	} else
	{
        	me->add("neili", -100);
                msg += CYN "$p" CYN "���Ų�æ��ʹ��һ�������š���$N"CYN"���˸��ա�\n" NOR;
	}

	//����
        ap = me->query_skill("yeqiu-quan", 1) + me->query_dex()*5;
        dp = target->query_skill("dodge", 1) + target->query_dex()*5;
	msg += HIW "\n������$N" HIW "����һ��"HIG"��������"HIW"������������˫��ʳָ����ָ�������������$n"HIW"�ؿڣ�\n" NOR;
	if (ap * 2 / 3 + random(ap) > dp)
	{
        	me->add("neili", -300);
		damage = ap+random(ap/4);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                   HIR "$n���ܲ�������ʱ���������У���ǰ�����ĸ��ں����Ŀ�����\n" NOR);
	} else
	{
        	me->add("neili", -100);
                msg += CYN "$p" CYN "��æʹ��¿������ڵ���������ʮ�˸����Ŷ㿪$N"CYN"�ľ�����\n" NOR;
	}

	//��
        ap = me->query_skill("yeqiu-quan", 1) + me->query_con()*5;
        dp = target->query_skill("parry", 1) + target->query_con()*5;
	msg += HIW "\n$N" HIW "�����ٳ�һ��"HIB"������"HIW"�����ƴ󿪣�˫�ֽ���������$n"HIW"�����ţ�\n" NOR;
	if (ap * 2 / 3 + random(ap) > dp)
	{
        	me->add("neili", -300);
		damage = ap+random(ap/4);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                   HIR "$n���޿ɱܣ���$N"HIR"��ñ������ס�\n" NOR);
	} else
	{
        	me->add("neili", -100);
                msg += CYN "$p" CYN "�Ͻ�ʹ��һ�С���ͷ�ڹꡱ����ͷһ�����ձܿ���$N"CYN"�Ĺ�����\n" NOR;
	}
 	//����

        me->add("neili", -300);
        message_combatd(msg, me, target);

	msg = HIM "\n$N" HIM "ʹ�������Ժ󣬾�ȻԽսԽ�£�����$n"HIM"����һ����׷�ʹ�\n" NOR;
        ap = me->query_skill("yeqiu-quan", 1) + me->query_int()*5;
        dp = target->query_skill("literate", 1) + target->query_int()*5;

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 5;
                msg += RED "$n" RED "���$P" RED "�Ĺ��ƣ���ȫ�޷��ֵ���Ψ���˺�\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "����Ӧս���߾����ܻ���$P" HIC "����ʽ��\n" NOR;
                count = 0;
        }
        message_vision(msg, me, target);
	me->add_temp("apply/attack", count);
	me->add_temp("apply/unarmed_damage", count / 2);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
	me->add_temp("apply/attack", -count);
	me->add_temp("apply/unarmed_damage", -count / 2);
        me->start_busy(3 + random(6));
        return 1;
}