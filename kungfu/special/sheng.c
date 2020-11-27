// sheng.c

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "Խ������" NOR; }

int perform(object me, string skill)
{
        int n, q;

        if ((int)me->query("neili") < 50)
                return notify_fail("�������������\n");
                
        if ((int)me->query("eff_qi") < (int)me->query("max_qi") / 2)
                return notify_fail("���Ѿ����˹��أ�ֻ��һ��������������Σ�գ�\n");
                
        q = (int)me->query("eff_qi") - (int)me->query("qi");
        
        if (q < 10 && ((int)me->query("eff_jing") - (int)me->query("jing") < 10))
                return notify_fail("��������Ϣ�;������档\n");
                
        n = 100 * q / me->query_skill("force");
        n = 30 * n / me->query_con();
        
        if (n < 20)
                n = 20;
                
        if ((int)me->query("neili") < n) 
        {
                q = q * (int)me->query("neili") / n;
                n = (int)me->query("neili");
        }
        
        me->add("neili", -n);
        me->receive_heal("jing", q);
        me->add("qi", q);
        
        message_vision("$N�������˼���������ɫ�������ö��ˡ�\n", me);
        
        if (me->is_fighting()) 
                me->start_busy(1);
        
        me->improve_skill("force", random(me->query_skill("force", 1)), 0);
        me->improve_skill("parry", random(me->query_skill("parry", 1)), 0);
        me->improve_skill("dodge", random(me->query_skill("dodge", 1)), 0);
        
        return 1;
}

