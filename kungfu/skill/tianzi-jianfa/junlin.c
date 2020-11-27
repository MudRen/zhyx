
#include <ansi.h>

inherit F_SSERVER;

#define JUNLIN "��" HIY "��������" NOR "��"
 
int perform(object me, object target)
{
        string msg;
        int count;
        int lvl;
        int i, ap, dp;
        object weapon;
        
        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/tianzi-jianfa/junlin"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");
      
                
        if (! target || ! me->is_fighting(target))
                return notify_fail(JUNLIN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" JUNLIN "��\n");

        if (me->query_skill_mapped("sword") != "tianzi-jianfa") 
                return notify_fail("��û�м������ӽ���������ʩչ" JUNLIN "��\n");
        
        if ((int)me->query("neili") < 800)
                return notify_fail("��������������޷�ʩչ" JUNLIN "��\n");

        if (me->query("max_neili") < 5000)
                return notify_fail("���������Ϊ��������ʹ��" JUNLIN "��\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���򲻹�������ʩչ" JUNLIN "��\n");

        if ((lvl = (int)me->query_skill("tianzi-jianfa", 1)) < 240)
                return notify_fail("������ӽ����������������޷�ʹ��" JUNLIN "��\n");             
                         
        
        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "ֻ��$N" HIY "���б���" 
              HIY"�ƺ�����һ����������$nֱ��ȥ��\n���Ծ�������֮������\n" NOR;

        message_sort(msg, me, target);
        me->add("neili", -300);
        ap = me->query_skill("tianzi-jianfa, 1");
        dp = target->query_skill("dodge", 1);
       
        if (ap / 3 + random(ap) > dp)
                  count = ap / 8;
  
        else count = 0;

        me->add_temp("apply/attack", count);

        for (i = 0; i < 15; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, i * 2);
        }
        me->add_temp("apply/attack", -count);
        me->start_busy(1 + random(5));
        return 1;
}


