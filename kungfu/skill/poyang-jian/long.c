//updated by kasumi
#include <ansi.h>
#include <combat.h>

#define LONG "��" HIC "��������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp,i;
        int damage,count;
        int neili, hit_point, time;

        if (userp(me) && ! me->query("can_perform/poyang-jian/long"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LONG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" LONG "��\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" LONG "��\n");

        if (me->query_skill("poyang-jian", 1) < 180)
                return notify_fail("���������⽣��Ϊ����������ʩչ" LONG "��\n");

        if ((int)me->query_skill("dodge") < 200)
                return notify_fail("����Ṧ��򲻹�������ʩչ" LONG "��\n"); 

        if ((int)me->query("max_neili") < 2500)
                return notify_fail("���������Ϊ���㣬����ʩչ" LONG "��\n");

        if (me->query("neili") < 350)
                return notify_fail("�����������������ʩչ" LONG "��\n");

        if (me->query_skill_mapped("sword") != "poyang-jian")
                return notify_fail("��û�м���������⽣������ʩչ" LONG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
        
        if (! me->query("real_perform/poyang-jian/long"))
        {
                msg = HIY "\nֻ��$N" HIY "����" + weapon->name() + HIY
                      "��ɨ������ʩ�����С�" HIC "��������" HIY "����"
                      "�����ݺᣬ����һ���������Ѷ���������$n" HIY "��\n" NOR;
                ap = me->query_skill("sword");
				dp = target->query_skill("parry");
                neili = 170;
                hit_point = 50+random(20);
                time = 1 + random(3);
        }

        else
        {
                msg = HIW "\n����$N" HIW "����" + weapon->name() + HIW 
                      "�԰���к��������������ֱ������һ������һ�㣬��"
                      "��������⽣�ľ��衸" HIY "��������" HIW "����һ"
                      "��������$N" HIW "ʹ�������ߣ�����������Ȼ������$n" 
                      HIW "��\n" NOR;
                ap = me->query_skill("sword")+ me->query_skill("force");
				dp = target->query_skill("dodge")+target->query_skill("force");
                neili = 150;
                hit_point = 80+random(20);
                time = 2 + random(3);
        }
        message_sort(msg, me, target);

        if (ap * 2/ 3 + random(ap) > dp)
        {
                damage = ap + random(ap/2);
                me->add("neili", -neili);               
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, hit_point,
                                           HIR "$n" HIR "�������������ͣ� �赲��"
                                           "���� ��ʱ��" + weapon->name() + HIR 
                                           "���ˣ��಻���ԡ�\n" NOR);
        } else
        {
                me->add("neili", -150);               
                msg = CYN "��ȴ��" CYN "$n" CYN "�͵İεض��𣬱ܿ���"
                      CYN "$N" CYN "�������͵�һ�С�\n" NOR;
        }
        message_vision(msg, me, target);


       if (me->query("real_perform/poyang-jian/long"))
	   {
		   msg = HIW "ֻ��$N"HIW"���Ʋ���������" + weapon->name() + HIW "�����̻���������������$n" HIW "��\n" NOR;
           message_combatd(msg, me, target);

		   count = me->query_skill("sword",1)*2/3;
           me->add_temp("apply/attack", count);
           me->add_temp("apply/damage", count);
		   for (i = 0; i < 5; i++)
      	   {
               	if (! me->is_fighting(target))
               	        break;
				 if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1); 
                COMBAT_D->do_attack(me, target, weapon, 0);
           }
		   me->add_temp("apply/attack", -count);
           me->add_temp("apply/damage", -count);
		   me->add("neili", -100);
	   }
	    me->start_busy(time);

        return 1;
}
