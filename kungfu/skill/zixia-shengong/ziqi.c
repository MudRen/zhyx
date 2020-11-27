// ziqi.c ��������
// looo/2001/6/21/update
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        object weapon;
        string msg;
        int d_count, count, qi, maxqi, skill;

        if( (int)me->query_temp("ziqi") )
                return notify_fail(HIG"���Ѿ����������������ˡ�\n");

        if( (int)me->query("neili") < 200 )
                return notify_fail("���������������\n");

        if( (int)me->query_skill("force") < 150)
                 return notify_fail("�����ϼ�񹦵���Ϊ����������ʹ����������! \n");
//�����б������ӱ�������
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��û�н�.��ô����������ѽ? \n");
        msg = MAG "$N" MAG "����һ����,����������ʢ!!���еı�������͸��һ���Ϲ�..\n" NOR;

        qi = me->query("qi");
        maxqi = me->query("max_qi");
        skill = (int)me->query_skill("zixia-shengong", 1);



        if(qi > (maxqi * 0.4))
        {
                message_combatd(msg, me);
                me->add_temp("apply/damage", skill / 3);
		me->add_temp("apply/sword",skill / 10);
                me->set_temp("ziqi", 1);
                me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill/5);

                me->add("neili", -150);
        }
        else{
                msg = HIR "$N" HIR "ƴ�����������������������������Լ�����̫�أ�û�ܳɹ�!\n" NOR;
           message_combatd(msg, me);
        }

        return 1;
}

void remove_effect(object me, int amount)
{
        if ( (int)me->query_temp("ziqi") )
        {
                me->add_temp("apply/damage", - amount / 3);
		me->add_temp("apply/sword", - amount / 10);
                me->delete_temp("ziqi");
                tell_object(me, HIY "������������������,����������ȥ.\n" NOR);
        }
}
