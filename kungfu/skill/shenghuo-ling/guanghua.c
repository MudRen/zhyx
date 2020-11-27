#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, skill;
        string msg;

        if (! target) target = offensive_target(me);
        skill = me->query_skill("shenghuo-ling",1);
        if (!objectp(weapon = me->query_temp("weapon")))
           return notify_fail("��ʹ�õı������ԣ�����ʹ��ʥ����֮�⻪�\n");

        if( !(me->is_fighting() ))
            return notify_fail("�⻪��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( skill < 140)
            return notify_fail("���ʥ����ȼ�����, ����ʹ�ù⻪�\n");

	if( me->query_skill_mapped("force") != "shenghuo-xuanming")
	    return notify_fail("��ʹ�õ��ڹ�����ʥ����ڤ���޷�ʹ��ʥ�����\n");

        if( me->query("max_neili") < 1200 )
            return notify_fail("���������Ϊ���㣬�޷����ù⻪�\n");

        if( me->query("neili") < 800 )
            return notify_fail("��������������޷�ʹ�ù⻪�\n");
                        
        msg = HIY "$N����һ������ʹ��ʥ���֮�⻪�����" +weapon->name()+ NOR + HIY"������ɣ��ó���������â����$n����������\n" NOR;

        if (random(me->query_skill("force")) > target->query_skill("force") / 2 || !living(target))
        {
            damage = (int)me->query_skill("force");
            damage += random(damage/2);
	    damage += me->query("jiali");
            me->add("neili", -damage/2);
            msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
            HIR "$nֻ���Է���������ǵذ�Ϯ����������ӿ����ȫ�޷��赲����ʱֻ��ȫ������ʹ����Ѫ�ɽ�������\n" NOR);

            me->start_busy(2);
        } else
        {
            msg += CYN "����$n��׼$N���������͵���ǰһԾ��������$N�Ĺ�����Χ��\n"NOR;
            me->add("neili", -200);
            me->start_busy(4);
        }
        message_combatd(msg, me, target);
        return 1;
}


