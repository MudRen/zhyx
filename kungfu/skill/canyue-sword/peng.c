//lian.c ��������
// looo/2001/6/24
#include <ansi.h>

#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)

{
        object weapon;
        string msg;

        int i, count,skill;
        skill = (int)(me->query_skill("sword"));       
        i = 4 + (int)me->query_skill("canyue-sword",1)/50;
        if (i > 12)
        	i=12;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))

                return notify_fail("���������¡�ֻ����ս���жԶ���ʹ�á�\n");        

        if (!objectp(weapon = me->query_temp("weapon")) )
                return notify_fail("�����ʹ����������ʹ�á��������¡���\n");

        if ((string)weapon->query("skill_type") != "sword")
                return notify_fail("��û���ý����޷�ʹ�á��������¡���\n");

        if(me->query_skill_mapped("sword") != "canyue-sword") 
                return notify_fail("��û���ò��½������޷�ʹ�á��������¡���\n");

        if( (int)me->query_skill("canyue-sword", 1) < 250 )
                return notify_fail("��Ĳ��½�����������죬ʹ�������������¡�������\n");

        if( (int)me->query_skill("force") < 300 )
                return notify_fail("����ڹ��ȼ���������ʹ�������������¡�������\n");

        if( (int)me->query("max_neili") < 3000 )
                return notify_fail("���������Ϊ��Ҫ��һ����ߣ�����ʹ�����������¡����С�\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("����������̫��������ʹ�á��������¡���\n");


        msg = HIM "\n$N" HIM "��ȻһЦ������"+ weapon->name() + HIM "���һ�����������£���Χ����ǹ������˸��ٲȻһ�����������¡���������\n"
              HIM "��Ȼ����ͼ��ã���ǧ�ǹ⻤��һ�����ʻ������¹���" HIM "$n" HIM "���ϵ����ȥ��\n" NOR;

        message_combatd(msg, me, target);
        
        count=skill/5;
        
        me->add_temp("apply/damage", count/2);
        me->add_temp("apply/attack", count);
        me->set_temp("canyue-sword/max_pfm", 1);

        while (i--)
        {
                if (! me->is_fighting(target))
                        break;
                if (! target->is_busy() && random(2)==1)
                        target->start_busy(1);                
                COMBAT_D->do_attack(me, target, weapon, 0);
                me->add("neili", -30);
        }

        me->start_busy(3+random(4));      
        
        me->add_temp("apply/damage", -count/2);
        me->add_temp("apply/attack", -count);
        me->delete_temp("canyue-sword/max_pfm");

        return 1;
}

