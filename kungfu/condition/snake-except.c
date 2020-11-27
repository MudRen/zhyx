 // snake-except.c
 // by Plzw 2004-2-4  
       
#include <ansi.h>  
       
inherit F_CLEAN_UP;  
       
int dispel(object me, object ob, int duration)  
{  
        int n;  
        string force;
  
        if (me != ob)  
        {  
                if (me->query_skill_mapped("finger") != "sun-finger") 
                { 
                        tell_object(ob, "�㷢��" + me->name() + "������ԴԴӿ������"  
                                    "���ﻹ�Ǳ��䣬���ް�����\n"); 
                        tell_object(me, "����ͼ����" + ob->name() + "�������������߾綾��"  
                                    "ȴ��Ȼ�������߾綾ԴԴ���ϵش��������ɴ󾪣���"  
                                    "æס�֡�\n"); 
                        return -1; 
                } 
                
                if (me->query("max_neili") < 2000)
                {
                	tell_object(me, "���������������޷�����" + ob->name() + "�������������߾綾��\n");
                	return -1;
                }
  
        } else 
        { 
                tell_object(me, "����õ�����䣬�޷�����������\n"); 
                return -1;  
        }  
       
        n = ob->query_condition("snake-except") - 
            (int)me->query_skill("sun-finger", 1); 
            
        force = me->query_skill_mapped("force");
 
        if (n < 1)  
        {
            ob->clear_condition("snake-except");  
            message_vision(HIY "$NĬ��" + to_chinese(force) + "��ʩչ��һ��ָ����"
				"˲ʱ�����$n������ҪѨ....\n\n" HIC "$N����һ������ͷ������ð������\n" + 
				"$n���ۡ���һ���³���Ѫ����ɫ��ʱ������ˡ�\n" NOR, me, ob);  
         	me->add("max_neili", - (1000 + random(1000)));
        }        
        else  
        {
	        ob->apply_condition("snake-except", n);  
   	        message_vision(HIY "$NĬĬ������һ��ָ��������$n�������ڵ����߾綾��\n"NOR, me, ob);  
   	}
   	    
        return 1;  
}  
    
int update_condition(object me, int duration)  
{  
        int limit;  
   
        if (! living(me) && (me->query("eff_qi") < 20 || me->query("eff_jing") < 10))  
        {   
        	    me->set_temp("die_reason", "���߾綾��������");
                me->die();  
                return 0;  
        } else  
        {  
                me->receive_wound("qi", 150 + random(50));  
                me->receive_wound("jing", 100 + random(20));  
                tell_object(me, HIG"��ֻ����һ�ɻ���һ����ľ�����е����߾綾�����ˣ�\n" NOR); 
                message("vision", HIG + me->name() + HIG "��Ȼ���ڵ��ϣ���ɫ���ϣ�ֱ����¡�\n" NOR,  
                       environment(me), ({ me })); 
        }  
  
        return 1;  
}
