// huan.c ���鵶�����һ�����
// Modify by Haiyan

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, zhao;

        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/xuanxu-dao/huan")) 
                return notify_fail("�����ڻ�����ʹ�á��һ�������\n"); 

        if (! target || ! me->is_fighting(target))
                 return notify_fail("���һ�����ֻ����ս���жԶ���ʹ�á�\n"); 

        if (! objectp(weapon = me->query_temp("weapon")) || 
              (string)weapon->query("skill_type") != "blade") 
                 return notify_fail("��ʹ�õ��������ԡ�\n"); 

        if (me->query_skill("force") < 200) 
                 return notify_fail("����ڹ�����Ϊ����������ʹ���һ�����\n"); 

        if ((int)me->query_skill("xuanxu-dao", 1) < 135)
                  return notify_fail("������鵶����Ϊ������Ŀǰ����ʹ���һ�����\n"); 

        if (me->query("neili") < 250)
                return notify_fail("�����������������ʹ�á��һ�������\n");

        msg = HIW "$N" HIW "ʹ�����鵶���еľ����һ����������ɻ�������������ֻ�ʵ�$n" + HIW 
              "��ǰһƬӰ����\n" NOR; 

        ap = me->query_skill("blade", 1) / 2 + me->query_skill("xuanxu-dao", 1); 
        dp = target->query_skill("dodge") / 2 + target->query_skill("parry", 1); 

        if ( ap / 2 + random(ap) > dp )
        {

                msg += HIR "�����������������������죬$p" HIR "һ��" 
                      "�ҽУ�ȫ�������ͷ������һһ�ʶϣ���̲�����" 
                      "������ȥ��\n" NOR; 
                zhao = 5; 
                count = ap / 10; 
                me->add("neili", -180);
        } else
        {
                msg += CYN "����$p" CYN "�����񵲣�$P" CYN  
                       "ֻ���þ�������˥�ߣ����е��⽥���� \n" NOR; 
                zhao = 0; 
                count = 0;
                me->add("neili", -60);
        }
                
        message_combatd(msg, me, target);
        me->add_temp("apply/attack", count);
        for (i = 0; i < zhao; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->add_temp("apply/attack", -count);
        me->start_busy(1 + random(zhao));

        return 1;
}

