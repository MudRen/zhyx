// sandie.c ��������
// looo/2001/6/28/
#include <ansi.h>

#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int damage;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character()
           || !me->is_fighting(target) || !living(target) )
                return notify_fail("������������ֻ����ս����ʹ�á�\n");

        if( objectp( me->query_temp("weapon")) )
                return notify_fail("ֻ�п��ֲ���ʩչ��������������\n");

        if( (int)me->query_skill("sun-finger", 1) < 180 ||
            (int)me->query_skill("finger", 1) < 180 ||
            (int)me->query_str() < 25)
                return notify_fail("���еĹ��򻹲�����죬����ʹ�á�������������\n");

        if (me->query_temp("weapon"))
                return notify_fail("�㲻ȡ�±��������ʹ��һ��ָ��\n");

        if(!me->query_skill("duanshi-xinfa", 1))
           if(me->query_skill("duanshi-xinfa", 1) <180)
                return notify_fail("�������ڵĶ����ķ���ʹ������������������\n");

        if ( me->query_skill_mapped("finger") != "sun-finger" )
                return notify_fail("�������޷�ʹ�á��������������й�����\n");

            if (me->query_skill_mapped("parry") != "sun-finger")
                return notify_fail("����ʹ�õ��мܲ��ԡ�\n");
        if( (int)me->query("neili") < 1800 )
                return notify_fail("���������Ϊ̫��������ʹ�á�������������\n");

        if( (int)me->query("neili") < 800 )
                return notify_fail("�������������\n");

        if (target->query_skill_mapped("force")=="hamagong")
        {
                msg = HIY "\n$N����$n��������ָ��һʽ���������������ֻ������������ָ��ֱϮ$n�ؿڣ�\n" NOR;
                if (random(me->query_skill("force",1)) > target->query_skill("force",1) /4 || !living(target))
                {
                        me->start_busy(1);
                        target->start_busy(1);
                        damage = (int)me->query_skill("sun-finger", 1);
                        damage += (int)me->query_skill("force", 1);
                        damage += damage/2 + random(damage/2);
                        target->receive_damage("qi", damage);
                        target->receive_wound("qi", damage/3);
                        me->add("neili", -300);
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                               HIR "$n" HIR "���·������ƺ������Լ��Ŀ��ǣ����Ƕ�ܲ����������ص��У�\n\n" NOR);
                if(me->query_skill("sun-finger", 1) > 190)
	                call_out("perform2", 0, me, target);
                }
                else {
                        me->start_busy(3);
                        if (target->is_busy()) target->start_busy(1);
                        me->add("neili", -200);
                        msg += HIW"$p���ⷴ�ֵ�Ѩ�ƺ����Ǹ�󡹦�Ŀ��ǣ�ʶ��������Σ��֮��һ�������ţ��������һ�������ѵĶ����һ�С�\n"NOR;
                }
        }
        else
        {
                msg = HIY "\n$N������ָ��һʽ������������������������������죬һ�ɴ���������ֱϮ$n�ؿڣ�\n" NOR;
                if (random(me->query_skill("parry")) > target->query_skill("parry") / 2 || !living(target))
                {
                        me->start_busy(1);
                        target->start_busy(1);
                        damage = (int)me->query_skill("sun-finger", 1);
                        damage += (int)me->query_skill("force", 1) ;
                        damage += random(damage/2);
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                               HIR "$n" HIR "һ���ƺߣ�ȫ��Ѫ����������������������\n" NOR);
                        if(me->query_skill("sun-finger", 1) > 190)
	                        call_out("perform2", 0, me, target);
                }
                else
                {
                        me->start_busy(3);
                        if (target->is_busy()) target->start_busy(1);
                        me->add("neili", -100);
                        msg += HIW"����$pһ�����Ʒ���ԶԶ�Ķ��˿�ȥ��\n"NOR;
                }
        }
        message_vision(msg, me, target);
        return 1;
}

int perform2(object me, object target)
{
	int i;
        string msg;

        if (!me || !target) return 0;
        if(!living(target))
        return notify_fail("�����Ѿ�������ս���ˡ�\n");

        if( (int)me->query("neili", 1) < 600 )
        return notify_fail("���Ҫ�ٳ��ڶ�ָ��ȴ�����Լ������������ˣ�\n");

        if (target->query_skill_mapped("force")=="hamagong")
		i = 4;
	else
		i = 2;

        msg = HIY "\n����$N̤ǰһ�������ڶ�ָ���յ���$n��ǰ������Ѩ������Ѩ�������֮�\n"NOR;

        if (random(me->query_skill("dodge")) > target->query_skill("dodge") / i)
	{
	        msg += HIR "���һָ���У�$nֻ����ȫ������ͨ���������������ܸ��ӣ�\n"NOR;
        	me->start_busy(2);
	        target->start_busy(me->query_skill("force",1)/30);
        	me->add("neili", -(me->query_skill("force",1)/2));
	        if((int)me->query_skill("sun-finger", 1) > 230)
        	call_out("perform3", 0, me, target);
        }
        else
        {
        	me->start_busy(4);
            if (target->is_busy()) target->start_busy(1);
	        me->add("neili", -150);
        	target->add("neili", -50);
	        msg += HIW"\n$p�ۿ����޿ɱܣ���Ҳһָ��ȥ������ָ��������$p˳�����˿�ȥ��\n" NOR;
        }
        message_vision(msg, me, target);
        return 1;
}

int perform3(object me, object target)
{
	int i;
        int skill;
        string msg;
        skill = (int)me->query_skill("sun-finger", 1);
        skill = skill/10;

        if(!living(target))
          return notify_fail("�����Ѿ�������ս���ˡ�\n");

        if( (int)me->query("neili", 1) < 400 )
                return notify_fail("���Ҫ�ٳ�����ָ��ȴ�����Լ������������ˣ�\n");

        if (target->query_skill_mapped("force")=="hamagong")
		i = 4;
	else
		i = 2;

        msg = HIY "\n������$Nһ��ָ�����ε�����Դ���������ͬʱ͸��$n���������Ϲ�Ѩ��
��ά�����Ѩ����������Ѩ����������Ѩ������������Ѩ��\n"NOR;

        if (random(me->query_skill("force")) > target->query_skill("force") / i)
	{
        	me->add("neili", -200);
	        msg += HIR "$nֻ�������澭��������ϢΪ֮һ����ȫ��������Ȼ�᲻�����ˣ�\n" NOR;
        	target->add_temp("apply/attack", -200);
	        target->add_temp("apply/dodge", -200);
        	target->add_temp("apply/parry", -200);
	        me->start_busy(3);
            if (target->is_busy()) target->start_busy(1+random(2));
        	target->add("neili", -700);
	        call_out("back", 4 + skill, target);
        }
        else
        {
 	       me->start_busy(target->query_skill("force",1)/30);
        	me->add("neili", -200);
	        target->start_busy(1);
        	msg += HIW"\n$p��Ϣδ������$Pָ��������������æ��Ծ�����ߣ��Ǳ��رܿ���\n" NOR;
        }
        message_vision(msg, me, target);
        return 1;
}

void back(object target)
{
    if (!target) return;
        target->add_temp("apply/attack", 200);
        target->add_temp("apply/dodge", 200);
        target->add_temp("apply/parry", 200);
}
