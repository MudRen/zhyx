#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define ZONG "��" HIM "���ݺ�" NOR "��"

int perform(object me, object target)
{
        string msg,parry_str;
        int ap, dp,i,delta,lvl;
        int damage, skill;

        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/liumai-shenjian/zong"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZONG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill_prepared("finger") != "liumai-shenjian")
                return notify_fail("��û��׼��ʹ�������񽣣��޷�ʩչ" ZONG "��\n");

        skill = me->query_skill("liumai-shenjian", 1);

        if (skill < 500)
                return notify_fail("�����������Ϊ���ޣ��޷�ʹ��" ZONG "��\n");

        if (me->query_skill("force") < 500)
                return notify_fail("����ڹ���򲻹�������ʩչ" ZONG "��\n");

        if (me->query("max_neili") < 8500)
                return notify_fail("���������Ϊ����,�޷�ʩչ" ZONG "��\n");

        if (me->query("neili") < 1500)
                return notify_fail("������������������޷�ʩչ" ZONG "��\n");

        if (me->query_temp("weapon"))
                return notify_fail("������ǿ��ֲ���ʩչ" ZONG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");


        msg = HIM "$N" HIM "һ����Х��ʮָ�׵����پ�����������ӿ����ͷ������"
              "�˷������಻������ʱ�����籼�������޾������������Ȼ����$n" HIM 
              "��\n" NOR;

        ap = me->query_skill("finger") + me->query_skill("force");
        dp = target->query_skill("parry") + target->query_skill("force");
        
        damage = ap*3/2 + (int)me->query_skill("jingluo-xue", 1)+(int)me->query_skill("yiyang-zhi", 1) + (int)me->query_skill("canhe-zhi", 1);
        damage = damage + random(damage);
        
        parry_str=target->query_skill_mapped("parry");

		lvl = (int) me->query_skill("kurong-changong", 1);
        
        if (lvl * 2 / 3 +random(lvl) > target->query_skill("force", 1))
		{
			target->map_skill("parry", 0);
		}

		if (lvl > 900)
		{delta = 500;}
		else if (lvl > 600)
		{delta = 300;}
		else if (lvl > 300)
		{delta = 200;}
		else delta = 0;

        
        if (ap + random(ap) > dp)
        {               	 
                me->add("neili", -400);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 150,
                                           HIR "ֻ��$n" HIR "һ���ҽУ����������"
                                           "͸��������˿ڴ���Ѫ��ʱ��ӿ��ʹ���ѵ���\n" NOR);
        } else
        {
                me->add("neili", -200);
               
                msg += CYN "$n" CYN "��$N" CYN "������ӿ����������"
                       "�мܣ���æ����Ծ����\n" NOR;
        }
        message_combatd(msg, me, target);
        
        if ((int)target->query("qi")> 0&& me->is_fighting(target))
        {        
              msg = HIW "������"HIW"$N" HIW "̯��˫�֣���ָ��������ʱ��������ȣ���"
              "�����ڣ���������������Ѩ��һ�����$n" HIW "��\n" NOR;

              msg += HIR "$n" HIR "ֻ�н����ݺᣬ΢һ��񣬲����������⡣\n" NOR;                  

                message_combatd(msg, me, target);

                me->add("neili", -600);               
                target->add_temp("apply/dodge", -delta);
                for (i = 0; i < 6; i++)
                {
               			 if (! me->is_fighting(target))
                        break;

                		if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);                

                	COMBAT_D->do_attack(me, target, 0, i * 3);
                }                
                target->add_temp("apply/dodge", delta);
       }
       me->start_busy(3+random (5));
       target->map_skill("parry", parry_str);
       

        return 1;
}

