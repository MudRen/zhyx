// Code of ShenZhou
//01-01-01 wsky

//�ٲ����У���־ƽ��ƽ�̣�����������ͬʱ���Ⱥ�ɨ������
//����ȫ�����еġ������������С�

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
        int addon, ap, dp, damage, count, limit, limit2;
        string str;
        object weapon, weapon1;

        weapon = me->query_temp("weapon");
        weapon1 = me->query_temp("secondary_weapon");

        if (!weapon || weapon->query("skill_type") != "sword")
                return notify_fail("�������޽������ʹ��ȫ�潣����������������\n");

        if(!target ) target = offensive_target(me);

        if(!target || !target->is_character() || !me->is_fighting(target))
                return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

/*
        if (!me->query("quanzhen/lianhuan"))
                return notify_fail("�����ڻ�����ʹ��������������\n");
*/

        if (me->query_skill("sword",1)<150)
                return notify_fail("��Ļ�������������ʵ��\n");

        if (me->query_skill("quanzhen-jian",1)<180)
                return notify_fail("���ȫ�潣����Ϊ������\n");

        if( me->query_skill_mapped("sword") != "quanzhen-jian" )
                return notify_fail("�����õĲ���ȫ�潣����\n");

        if( me->query("neili") <= 350 )
                return notify_fail("�����������ʹ�á�����������\n");

        if( me->query("jingli") <= 250 )
                return notify_fail("��ľ�������ʹ�á�����������\n");

        if( me->query_skill_mapped("strike") != "haotian-zhang" &&
            me->query_skill_mapped("strike") != "chongyang-shenzhang")
                return notify_fail("�����õĲ���ȫ����Ʒ�������ʩչ������������\n");

         if( me->query_skill_prepared("strike") != "haotian-zhang" &&
             me->query_skill_prepared("strike") != "chongyang-shenzhang")
                return notify_fail("�������Ĳ���ȫ����Ʒ�������ʩչ������������\n");

        me->add_temp("quanzhen/lh_count",1);

        if (me->query_temp("quanzhen/lh_count") > 30)
                me->set_temp("quanzhen/lh_count", 1);

        me->add("neili", -350);
        me->add("jingli",-250);
        me->start_busy(3);

        count=me->query_temp("quanzhen/lh_count");
        limit=180;
        if (count<=10) tell_object(me, HIG"\n\n�㾫���ӣ��������棬���и���������\n\n"NOR);
        if (count>10 && count<=20) {
                tell_object(me, HIG"\n\n�㷴��ʹ�á����������������Ѿ�û����ǰ����������Ȼ���ͱ��ˡ�\n\n"NOR);
                limit=120;
        }
        if (count>20) {
                tell_object(me, HIG"\n\n��ʹ��̫��Ρ�����������������ɢ�������Ѿ�ʧȥ��ԭ�е�������\n\n"NOR);
                limit=60;
        }

        addon = me->query_skill("sword")/4;
        if (addon > limit) addon = limit;

        me->add_temp("apply/attack",addon);
        me->add_temp("apply/damage",addon/2);

        message_vision(HIR"������У�$N��ƽ�̣�����������ͬʱ���Ⱥ�ɨ����������ȫ�����еġ������������С�\n"NOR,me,target);

        COMBAT_D->do_attack(me, target, weapon, 1);

        weapon->unequip();
        if (objectp(weapon1))     weapon1->unequip();

        COMBAT_D->do_attack(me, target, 0, 1);

        weapon->wield();
        if (objectp(weapon1))     weapon1->wield();

        ap=me->query("combat_exp")/1000+me->query_skill("sword",1)+me->query_skill("unarmed",1);
        dp=target->query("combat_exp")/1000+target->query_skill("parry",1);

        if(me->query_skill("unarmed",1)>50) message_vision(HIY,me,target);
        message_vision("\n$N��һ�䣬৵�һ�ȣ�������$n��ɨ������ֻ���õ��ϳ������\n"NOR,me,target);

        if(random(ap)>dp/2 || !living(target))
        {
                damage=me->query_skill("quanzhen-jian",1)*(random(6)+3);

                message_vision(HIR"\nֻ��$n�����������Ѿ���$Nһ��ɨ�У��ҽ����У�����������\n"NOR, me, target);

                if (damage<500) damage=500;

                if (limit==100) damage=200;     

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", random(damage), me);                                

                str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                message_vision("($N"+str+")\n", target);

                target->start_busy(3);
        } else {
                message_vision(HIY"\n$n�������������ͣ����һԾ�����ɵض��˿�ȥ��\n"NOR,me,target);
                if(limit==100)
                {
                        message_vision(HIR"\n$N�������ͣ����Ʋ�ס������Ӵ��һ����ˤ��һ����\n"NOR,me,target);
                        me->add("eff_qi", -random(400));
                        str = COMBAT_D->status_msg((int)me->query("qi") * 100 /(int)me->query("max_qi"));
                        message_vision("($N"+str+")\n", me);
                }
                me->start_busy(2);
        }

        me->add_temp("apply/attack",-addon);
        me->add_temp("apply/damage",-addon/2);
        return 1;
}

