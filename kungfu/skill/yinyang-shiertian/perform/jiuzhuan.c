#include <ansi.h>
#include <combat.h>

#define TIAN "��" HIW "��תǬ��" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage,count,i,attack_time;
        string msg, wn, wp,wp2,str;
        object weapon,weapon2;
        int ap, dp;
        me = this_player();

        
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(TIAN "ֻ����ս���жԶ���ʹ�á�\n");
       
        if ((int)me->query_skill("yinyang-shiertian", 1) < 400)
                return notify_fail("���������תʮ�������򲻹�������ʩչ" TIAN "��\n");

	weapon = me->query_temp("weapon");

        if (! objectp(weapon))
        {
		if (me->query_skill_mapped("unarmed") != "yinyang-shiertian"
			|| me->query_skill_prepared("unarmed") != "yinyang-shiertian")
				return notify_fail("��û��׼��������תʮ�����죬�޷�ʹ��" TIAN "��\n");
        }
        else
	{
		if (objectp(weapon) && (string)weapon->query("skill_type") != "sword"
				&& (string)weapon->query("skill_type") != "blade")
                              return notify_fail("��ʹ�õ��������ԣ��޷�ʩչ" TIAN "��\n");
	}

        if (objectp(weapon) && me->query_skill_mapped("sword") != "yinyang-shiertian"
                 && (string)weapon->query("skill_type") == "sword")
                              return notify_fail("�㻹û�м���������תʮ�����죬�޷�ʩչ" TIAN "��\n");
             
	else if (objectp(weapon) && (string)weapon->query("skill_type") == "blade"
                      && me->query_skill_mapped("blade") != "yinyang-shiertian")
                              return notify_fail("�㻹û�м���������תʮ�����죬�޷�ʩչ" TIAN "��\n");    

        if ((int)me->query("max_neili") < 8500)
                return notify_fail("���������Ϊ���㣬����ʩչ" TIAN "��\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("�����ڵ���������������ʩչ" TIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");        
       
        message_sort(HIM "\n$N" HIM "����Ĭ�����޳����������ʮ�����쾳�磬"
                     "���ռ��ƺ�ҲŤ����������$n" HIM "��ʧɫ���·���������磡\n" NOR, me, target);

         message_sort(HIW "$N" HIW "˫��һ��һ�ɻ���������ھ���ӿ���ȣ�" 
                     "������ɽ����֮����$n" HIW "ϯ�������\n" NOR, me, target);
        ap = me->query_skill("yinyang-shiertian", 1);

        dp = target->query_skill("dodge", 1);
        
	if (ap + random(ap) > dp)
                count = ap / 3;
	else
                count = ap / 10;

        me->add_temp("apply/attack", count);
	me->add_temp("apply/damage", count / 2);
	me->add_temp("apply/unarmed_damage", count / 2);
        me->add("neili", -250);

        attack_time = 1+(int)(me->query_skill("yinyang-shiertian", 1)/50);
        if (attack_time > 9) attack_time =9;

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);
                if (! objectp(weapon))
                   COMBAT_D->do_attack(me, target, 0, i * 2);
                else COMBAT_D->do_attack(me, target, weapon, i * 2);
        }
        me->add_temp("apply/attack", -count);
	me->add_temp("apply/damage", -count / 2);
	me->add_temp("apply/unarmed_damage", -count / 2);
        me->start_busy(2+random(4));
        me->add("neili", -1000);
       return 1;
}
        

        

