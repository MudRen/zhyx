// /kungfu/skill/dragon-strike/xianglong.c  perform ����һ��
// Rama 2001/11/11

#include <ansi.h>
#include <armor.h>
#include <combat.h>
inherit F_SSERVER;

void remove_effect(object me, object target, int lvl);
void msg_display(object me, object target, int lvl);

int perform(object me, object target)
{
        object armor;
        int lvl, my_exp;
        
        my_exp = me->query("combat_exp");

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("�㲻��ս���С�\n");

        if( me->query_temp("yield") )
                return notify_fail("�㲻���ƣ����ʹ������һ����\n");

        if ( objectp(me->query_temp("weapon")) )
                return notify_fail("�㲻�ǿ��֡�\n");

        if( me->query_temp("xianglong",1) ){
                return notify_fail("������ʹ�ý���һ����\n");   
        }

        if( (int)me->query("max_jingli", 1) < 500 )
                return notify_fail("��ľ�����Ϊ����������ʩչ����һ����\n");

        if( (int)me->query("max_neili", 1) < 6000 )
                return notify_fail("���������Ϊ����������ʩչ����һ����\n");

        if( me->query_skill("force") < 550 )
                return notify_fail("��Ļ����������δ�����޷�ʩչ����һ����\n");

        if( (lvl = me->query_skill("strike")) < 550 )
                return notify_fail("��Ľ���ʮ������Ϊ������\n");

        if ( me->query_skill_mapped("force") != "huntian-qigong")
                                         return notify_fail("�������ڹ����ԣ�\n");

        if( me->query("neili") <= lvl*2 )
                                         return notify_fail("�������������\n");

        if( me->query("jingli") <= 500 )
                                         return notify_fail("��ľ���������\n");

        me->set_temp("xianglong",1);
        message_vision(HIR "$N���۵��˫����������ת�˸�ԲȦ������������ȫ������\n\n" NOR, me,target);
        me->add("neili", -lvl/2); 
        me->add("jingli", -lvl/5);  
        lvl = (int)(lvl / 5);

        me->add_temp("apply/parry", lvl);
        me->start_busy(1+random(2));

        call_out("msg_display",1+(int)((me->query_skill("strike")-300)/50),me,target,lvl);

        return 1;
}

void msg_display(object me, object target, int lvl)
{
        string *circle, msg;

        if (!me) return;
        
        if (!target ||
            !target->is_character() ||
            !me->is_fighting(target) ||
            !living(me))
        {
                me->delete_temp("xianglong");
                me->add_temp("apply/parry",-lvl);
                return;
        }
       

        circle = ({
                "$NͻȻ���һ����˫���������$p�����ͻ���ȥ��\n",
                "$N������������һ�������ֺ���һ�ƣ�����$p��ȥ��\n"
        });

        msg = HIG"\n"+ circle[random(sizeof(circle))] +"\n" NOR;

        circle = ({
                "����δ����$p�Ѹ��ؿں������������֮�䣬$N��������ŭ������ӿ������",
                "ֻһ˲֮�䣬$p�����Ϣ���ͣ�$N��������ŭ����ӿ���Ʋ��ɵ���������һ�����εĸ�ǽ����$p��ǰ���塣"
        });

        msg += HIG"\n"+ circle[random(sizeof(circle))] +"\n" NOR;

        if( target
            &&  target->is_character()
            &&  me->is_fighting(target) ) {
                message_vision(msg, me, target);
                call_out("remove_effect",2,me,target,lvl);
        } else {
                me->delete_temp("xianglong");
                me->add_temp("apply/parry",-lvl);
        }
        return 0;
}

void remove_effect(object me, object target, int lvl)
{
        int jiali, jianu, ap, dp, pp,dmg,damage;
        object weapon;
        string *limbs, limb, result, str, type;

        if (!me) return;
        
        if (!target ||
            !target->is_character() ||
            !me->is_fighting(target) ||
            !living(me))
        {
                me->delete_temp("xianglong");
                me->add_temp("apply/parry",-lvl);
                return;
        }

        weapon=target->query_temp("weapon");
        jiali = me->query("jiali");
        jianu = me->query("jianu")*5;
        ap = me->query_skill("strike");
        ap += (jiali + jianu)/4;
        ap *= 2;
        if (living(target))
        {
            pp = target->query_skill("parry");
            dp = target->query_skill("dodge");
        }  else
        {
            pp = 0;
            dp = 0;
        }
        type = "����";
        
        if( target
        &&      target->is_character()
        &&      me->is_fighting(target) ) {
        
        if (wizardp(me))
                printf("ap = %d , pp = %d , dp = %d , me->query_temp(apply/parry) = %d , lvl = %d .\n",ap,pp,dp,me->query_temp("apply/parry"),lvl);

        if( ap/2 + random(ap) > dp + pp ) {
            message_vision(HIM"$N��˫���Ѹ��Ż��������һ���������ش���$p�ؿڣ����ſ������������߹Ƕ��˼�����\n"NOR, me, target);
            dmg = ap;
            dmg += jiali + jianu*5;
            dmg += random(dmg/2);

        if (wizardp(me))
                printf("damage = %d\n",dmg);

            target->receive_damage("qi", dmg,  me);
            target->receive_wound("qi", dmg/2+random(dmg/2), me);
            target->start_busy(1+random(2));
        
            me->add("neili", -dmg/3);
            me->add("jingli", -dmg/6);

            limbs = target->query("limbs");

            result = COMBAT_D->damage_msg(dmg, type);
            result = replace_string( result, "$l", limbs[random(sizeof(limbs))]);
            result = replace_string( result, "$p", target->name() );
            message_vision(result, me, target);

            str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
            message_vision("($N"+str+")\n", target);
        } else {
            if ( objectp(weapon) )
            {
                message_vision(HIC "$n��֮�£�$p����������Բ��ס��ǰ��ͬʱ���������Ʈ����ˣ��ܿ���$N��һ�ơ�\n" NOR, me, target, weapon);
            }
            else {
                message_vision(HIC "$n��֮�£�˫������������Բ��ס��ǰ��ͬʱ���������Ʈ����ˣ��ܿ���$N��һ�ơ�\n" NOR, me, target);
            }
        }
        }
        me->start_busy(2+random(2));
        me->delete_temp("xianglong");
        me->add_temp("apply/parry",-lvl);
        return 0;
}

