// qianshan.c ����ǧɽ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define QIANSHAN "��" HIC "����ǧɽ" NOR "��"

int perform(object me, object target)
{
	string msg;
        int ap, dp;
        int i, count;
        object weapon;

        /*if (userp(me) && ! me->query("can_perform/china-aojue/qianshan"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");*/

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail(QIANSHAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon")) )
                return notify_fail("������Ҫ�ֱ���ʩչ��\n");

	if ((int)me->query_skill("china-aojue", 1) < 250)
		return notify_fail("����л�����������񣬲���ʹ��" QIANSHAN "��\n");	

       if (me->query_skill_mapped("sword") != "china-aojue") 
                return notify_fail("��û�м����л�����Ϊ����������ʩչ" QIANSHAN "��\n");

	if ( me->query("neili") < 700 )
		return notify_fail("�����������������ʹ��" QIANSHAN "��\n");

        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = me->query_skill("china-aojue", 1);
        dp = target->query_skill("dodge", 1);


        msg = HIC "$N" HIC"����"+ weapon->name() +HIC"��עǿ���������䣬�����������ţ���Խǧ��ɽ�壬\n"
                  "����֮�ͣ����˸�������л������ڶ�ʽ:"+HIG"����ǧɽ��\n" NOR;   
        message_combatd(msg, me, target);         
        count = ap;
        me->add_temp("apply/attack", count);	
        me->add_temp("apply/damage", count);
        for (i = 0; i < 16; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);
                        
               COMBAT_D->do_attack(me, target, weapon, 0);
        }
        me->add("neili", -40);
        me->start_busy(2 + random(5));     

        me->add_temp("apply/attack", -count);
        me->add_temp("apply/damage", -count);
	 

	return 1;
}
