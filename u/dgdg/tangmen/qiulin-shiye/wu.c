#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{   
        string msg;
        object env = environment(me); 
        mapping *obb = env->query("exits"); 

        if (userp(me) && ! me->query("can_perform/qiulin-shiye/wu")) 
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ�������衹��\n"); 
                    
        if (! target) target = offensive_target(me);
        
        if (! target || ! target->is_character() ||
            ! me->is_fighting(target))
                return notify_fail("��ֻ����ս����ʹ�á������衹��\n");
                
        if ((int)me->query_skill("qiulin-shiye", 1) <  90)
                return notify_fail("��Ŀǰ������ʹ�����������衹��\n");
                
        if ((int)me->query("neili") < 500)
                return notify_fail("�������������\n");
                
        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");
                
        me->add("neili", -200);
        msg = HIC"$NͻȻ����һ��������һչ�������Ʈ����ϣ�����Խ��ԽС��\n"NOR;
        me->start_busy(1);
    
        if (random(atoi(count_div(me->query("combat_exp"), 100))) >
            atoi(count_div(target->query("combat_exp"), 400))) 
        {
                if (! target->is_busy())
                target->start_busy(3 + random(3));
                me->receive_damage("qi", 200);
                me->receive_damage("jing",80);
                if (sizeof(obb) > 0) me->move(obb[0]);
                msg += RED"ֻ��$nֻ����Ŀ�ɿڴ�,һʱ��æ������������֪����Ǻá�\n"NOR;
        } else 
        {
                msg += HIC "����$pȴ�����϶��𣬴��һ�����������ߣ������������ǰ�棬$P����û�еóѡ�\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}


