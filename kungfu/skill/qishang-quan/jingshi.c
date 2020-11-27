// jingshi.c ��ʧ��

#include <ansi.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg,str;
        object target;
        int skill, ap, dp, jing_wound, eff_jing_wound, neili_wound;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qishang-quan",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("����ʧ����ֻ����ս����ʹ�á�\n");

        if( (int)me->query("neili") < 900 )
                return notify_fail("��������������ߣ�\n");

        if( (int)me->query_skill("cuff") < 250 )
                return notify_fail("���ȭ���������ң��޷���������ȭ�ĸ����ܾ���\n");

        if( (int)me->query_skill("qishang-quan", 1) < 250)
                return notify_fail("������ȭ����Ϊ���������ܹ���ᾫʧ��! \n");

          if( (int)me->query_skill("force", 1) < 250)
                return notify_fail(HIM "��Ļ����ڹ���Ϊ���㣬�������ʹ�þ�ʧ��! \n" NOR);

        if( me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("��û�м�������ȭ���޷����þ�ʧ����\n");
        if (me->query_skill_prepared("cuff") != "qishang-quan")  
                return notify_fail("��û��׼��ʹ������ȭ���޷�ʩչ����ʧ������\n");  
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ�ô��У�\n");


        msg = HIY "$N��������ʹ������ȭ�ܾ��еġ�" HIR "��ʧ��" HIY "����˫ȭ������������$n��ȥ��\n"NOR;
        message_vision(msg, me, target);

        ap = me->query("combat_exp") + skill * 500;
        dp = target->query("combat_exp") / 2;
        if( dp < 1 )
                dp = 1;
        if( random(ap) > dp || !living(target))
        {
                if(userp(me))
                        me->add("neili",-300);

                msg = HIG "$N��ȭֻ�������������$n����$N����������һ˲����������$n���ڣ�\n$nֻ�����е�ƣ��������\n"NOR;
                neili_wound = skill + random(skill);
                neili_wound += me->query("jiali");
                if(neili_wound > target->query("neili"))
                        neili_wound = target->query("neili");

                jing_wound = random((int)skill);
                jing_wound += me->query("jiali");
                eff_jing_wound = random((int)skill / 3);
                eff_jing_wound += (int)me->query("jiali")/2;
                target->receive_damage("jing", jing_wound, me);
                target->receive_wound("jing", eff_jing_wound, me);
		str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n";
                me->start_busy(2);
                target->start_busy(1 + random(2));
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

