// Code of JHSH
// jinglisuck.c

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int exert(object me, object target)
{
        int sp, dp, jl;

        if( !target ) target = offensive_target(me);

        if( !objectp(target) || target == me)
                return notify_fail("��Ҫ��ȡ˭�ľ�����\n");

        if (environment(me)->query("no_fight"))
                return notify_fail("���ﲻ��ս�����㲻����ʹ�û��������˵ľ�����\n");

        if ( me->query_temp("sucked") )
                return notify_fail("��ո���ȡ��������\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("������ֲ��ܹ���ȡ���˵ľ�����\n");

        if( !me->is_fighting() || !target->is_fighting() || !living(target) )
                return notify_fail("�������ս���в�����ȡ�Է��ľ�����\n");

        if( (int)me->query_skill("huagong-dafa",1) < 90 )
                return notify_fail("��Ļ����󷨹���������������ȡ�Է���������\n");

        if( (int)me->query("neili") < 300 )
                return notify_fail("�����������������ʹ�û����󷨡�\n");

        if( (int)me->query("jingli") < 100 )
                return notify_fail("��ľ�������������ʹ�û����󷨡�\n");

        if( (int)me->query("jingli") >= (int)me->query("max_jingli") * 5/2 )
                return notify_fail("����ȡ�ľ�������ȫ���޷�����ȡ������\n");

        if( (int)target->query("max_jingli") <= 0 )
                return notify_fail( target->name() +
                        "û���κξ�����\n");

        if( (int)target->query("jingli") < (int)target->query("max_jingli") / 10 )
                return notify_fail( target->name() + "�Ѿ�������ɢ�����Ѿ��޷�����������ȡ�κξ����ˣ�\n");

	
        message_vision(HIR "$N��$n΢΢һЦ��ͻȻ���Ʊ�צ������$n������\n\n" NOR, me, target );

        if( !target->is_killing(me) ) target->kill_ob(me);

        sp = me->query_skill("force") + me->query_skill("dodge") + me->query("kar")*50;
        dp = target->query_skill("force") + target->query_skill("dodge") + target->query("kar")*50;
        sp *= me->query("combat_exp")/1000;
        dp *= target->query("combat_exp")/1000;

        me->set_temp("sucked", 1);              

        if( random(sp+dp) > dp )
        {
                tell_object(target, HIR "�����ڻ���Ѩ��" + me->name() + "ͻȻ��ס���������ã�ֻ���������ˮ���Ի���Ѩ���ڶ�����\n" NOR);
                tell_object(me, HIG "�����" + target->name() + "�ľ���������ԴԴ���������˽�����\n" NOR);

		jl = (1+random(3)) * (int)me->query_skill("huagong-dafa", 1)/2;
		if ((int)target->query("jingli") > jl)
		{		
	                target->add("jingli", -1 * jl );
	                me->add("jingli", jl);
		}else{
	                me->add("jingli", jl/2);
	                target->add("jingli", -jl/2 );
	                }
                if( target->query("combat_exp") >= me->query("combat_exp")/2 ) {
                        me->add("potential", 1);
                        me->add("combat_exp", 1);
                        if (me->query("potential") > me->query_potential_limit())
                        me->set("potential", me->query_potential_limit());
                }

                me->start_busy(1+random(3));
                target->start_busy(1+random(3));
                me->add("neili", -(int)me->query_skill("huagong-dafa", 1)/6);
                me->add("jingli", -5);

                call_out("del_sucked", 2, me);
        }
        else
        {       
                message_vision(HIY "����$p������$P����ͼ��û��$P��ס����\n" NOR, me, target);
                me->add("jingli", -20);
                me->start_busy(2+random(2));
                call_out("del_sucked", 5, me);
        }

        return 1;
}

void del_sucked(object me)
{
        if ( me->query_temp("sucked"))
        me->delete_temp("sucked");
}

