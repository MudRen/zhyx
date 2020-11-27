// duo.c ������÷

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon, weapon2;
        int skill,lv1,lv2;
        int comb1,comb2;
        int dodge1,dodge2,neili1,neili2,str1,str2,force1,force2,hand1,parry2;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("zhemei-shou",1);

        if( !(me->is_fighting() ))
                return notify_fail("������÷ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (!living(target))
                return notify_fail("�Է��Ѿ������ˣ�ֱ��ȥ����ˣ������ʲô����\n");

        if (objectp(weapon2 = me->query_temp("weapon")))
                return notify_fail("�������֡�\n");

        if (!objectp(weapon = target->query_temp("weapon")))
                return notify_fail("�Է�û�б��У��㲻�õ��ġ�\n");

        if( skill < 100)
                return notify_fail("�����ɽ��÷�ֵȼ�����, ����ʹ�ÿ�����÷��\n");

        if ((int)me->query_skill("xiaowuxiang", 1)<100
                && (int)me->query_skill("lingjiu-xinfa", 1)<100
                && (int)me->query_skill("xiaoyao-xinfa", 1)<100
                && (int)me->query_skill("bahuang-gong", 1)<100
                && (int)me->query_skill("beiming-shengong", 1)<100)
                return notify_fail("��Ĺ����������޷�ʹ��������÷��\n");

        if ( me->query_skill_mapped("force") != "xiaowuxiang"
                && me->query_skill_mapped("force") != "bahuang-gong"
                && me->query_skill_mapped("force") != "lingjiu-xinfa"
                && me->query_skill_mapped("force") != "xiaoyao-xinfa"
                && me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("����ʹ�õ��ڹ��ķ�����ȷ���޷�ʹ�ÿ�����÷��\n");

        if( me->query("neili") < 300 )
                return notify_fail("��������������޷�ʹ�ÿ�����÷��\n");

        message_vision(CYN"\n$N�����Ϣ����׼$n��ʽ��һ��������ͻȻ���ֲ��룬ץ��$n���е�"+weapon->query("name")+CYN"��\n\n"NOR,me,target);

        
        force1 = me->query_skill("force",1);
        force2 = target->query_skill("force",1);
        parry2 = target->query_skill("parry",1);
        hand1 = me->query_skill("hand",1);
        dodge1 = me->query_skill("dodge",1);
        dodge2 = target->query_skill("dodge",1);
        str1 = me->query_str();
        str2 = target->query_str();
        lv1 = hand1*dodge1;
        lv2 = parry2*dodge2;

        if (lv1 < lv2)
        {
                message_vision("˭֪$n����������������һ�����е�ס��$N�Ĺ��ơ�\n",me,target);
                me->start_busy(1+random(3));
                me->add("neili",-50);
                COMBAT_D->do_attack(target,me,me->query_temp("weapon"));
                return 1;
        }

        if (lv1 > random(lv2*2))
        {
                message_vision(HIR"$nһ����������"+weapon->query("name")+HIR"�ѱ�$N����ץ����\n\n"NOR,me,target);
                comb1 = str1*force1;
                comb2 = str2*force2;
        
                if (comb1 > comb2 * 4/5 )
                {
                        message_vision(HIW"$nֻ��һ�ɾ�����"+weapon->query("name")+HIW"���˹���������һ�飬����"+weapon->query("name")+HIW"���ֶ�����\n"NOR,me,target);
                        weapon->move(me);
                        target->reset_action();
                        if (!target->is_busy())
                        target->start_busy(1);
                        me->add("neili",-50);
                        return 1;
                }
                message_vision(HIW"$N�߶��������������һ�������������ھ���"+weapon->query("name")+HIW"ԴԴ���룬$n��֮�¼����������лضᣡ\n\n"NOR,me,target);
                message_vision(HIG"$Nֻ��$n���е�"+weapon->query("name")+HIG"��ͬ��������һ�㣬ֻ�÷��֣�Ʈ���˿���\n"NOR,me,target);
                me->start_busy(1+random(2));
                me->add("neili",-150);
                return 1;

        }
        message_vision("����$n�Ŀ�����$N����ͼ�����̲�ȡ���ƣ�Ʈ��㿪$N�Ĺ�����\n",me,target);
        me->add("neili",-50);
        me->start_busy(1+random(2));
        return 1;
}

