// cangli.c �����

#include <ansi.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg,str;
        object target;
        int skill, ap, dp, neili_wound;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qishang-quan",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("���������ֻ����ս����ʹ�á�\n");

        if( (int)me->query("neili") < 800 )
                return notify_fail("��������������ߣ�\n");

        if( (int)me->query_skill("cuff") < 220 )
                return notify_fail("���ȭ���������ң��޷���������ȭ�ĸ����ܾ���\n");

        if( (int)me->query_skill("qishang-quan", 1) < 220)
                return notify_fail("������ȭ����Ϊ���������ܹ��������! \n");

        if( (int)me->query_skill("force", 1) < 220)
                return notify_fail(HIM "��Ļ����ڹ���Ϊ���㣬�������ʹ�ò����! \n" NOR);

        if( me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("��û�м�������ȭ���޷����ò������\n");
        if (me->query_skill_prepared("cuff") != "qishang-quan")  
                return notify_fail("��û��׼��ʹ������ȭ���޷�ʩչ�����������\n");  
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ�ô��У�\n");


        msg = HIY "$N��������ʹ������ȭ�ܾ��еġ�" HIR "�����" HIY "����˫ȭ������������$n��ȥ��\n"NOR;
        message_vision(msg, me, target);

        ap = me->query("combat_exp") + skill * 500;
        dp = target->query("combat_exp") / 2;
        if( dp < 1 )
                dp = 1;
        if( random(ap) > dp || !living(target))
        {
                if(userp(me))
                        me->add("neili",-200);

                msg = HIG "$n��$Nȭ��ɨ�У�ֻ��ȫ������ʧȴ��Ԧ�����⼱к��\n"NOR;
                neili_wound = skill + random(skill * 2);
                neili_wound += me->query("jiali");
                if(neili_wound > target->query("neili"))
                        neili_wound = target->query("neili");
                if(target->query("neili")<0)
                        neili_wound = 0;
                target->add("neili", -neili_wound);
                target->receive_wound("qi", neili_wound, me);
                target->start_busy(2);
                me->start_busy(2 + random(2));
		str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n";
        }
        else
        {
                msg = HIG "ֻ��$n���Ų�æ������һ���������$N�ı�ɱһ����\n"NOR;
                if(userp(me))
                        me->add("neili",-100);
                me->start_busy(3);
        }
        message_vision(msg, me, target);

        return 1;
}

