//updated by kasumi
#include <ansi.h>
#include <combat.h>

#define XIAN "��" HIY "�������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int level,ap,dp,count,i;

        if (userp(me) && ! me->query("can_perform/poyang-jian/xian"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" XIAN "��\n");      

        level = me->query_skill("poyang-jian", 1);

        if (level < 160)
		return notify_fail("��������⽣������죬����ʩչ" XIAN "��\n");

        if (me->query_skill_mapped("sword") != "poyang-jian")
                return notify_fail("��û�м���������⽣������ʩչ" XIAN "��\n");

	if ((int)me->query_skill("force") < 240)
		return notify_fail("����ڹ�����㣬����ʩչ" XIAN "��\n");

        if (me->query("neili") < 250)
                return notify_fail("�����ڵ���������������ʩչ" XIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");


	msg = HIG "\n$N" HIG "��Хһ����ʹ��������⽣���С�" HIY "�����"
              "��" HIG "��������" + weapon->name() + HIG "��â���ǣ�����"
              "ѣĿ��������⽵����ɲ�Ǽ�ֻ�����Ϊ֮ʧ�ԣ���â�Ѹ�"
              "��$n��\n" NOR;
        

		  ap = me->query_skill("sword");
    	dp = target->query_skill("dodge");
		
      if (ap * 3 / 5 + random(ap) > dp)
	    {
		   msg += HIY "$n" HIY "��$P" HIY "������ӿ�������������"
                           "���Ƶ��������ˣ��Ǳ����ѡ�\n" NOR;
		   count = me->query_skill("poyang-jian", 1) / 3;
      } else
      {
      msg += HIC "$n" HIC "��$N" HIC "�⼸������Ѹ���ޱȣ���"
                 "��������ֻ��С��Ӧ����\n" NOR;
		   count = 0;
      }

         me->add_temp("apply/attack", count);
         message_sort(msg, me, target);
		
		 for (i = 0; i < 6; i++)
         {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);               
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
         me->add("neili", -200);
		 me->add_temp("apply/attack", -count);
		 me->start_busy(1 + random(4));
	return 1;
}