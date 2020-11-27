#include <ansi.h> 
 
int check_fight(object me); 
int remove_effect(object me); 
 
int perform(object me) 
{ 
        object weapon; 
 
        if( !me->is_fighting() || !living(me)) 
                return notify_fail("��������ֻ����ս���е�ʹ�á�\n"); 
 
      if (! objectp(weapon = me->query_temp("weapon")) || 
          (string)weapon->query("skill_type") != "blade")  
                return notify_fail("�����Ұѵ���˵�ɣ�\n"); 
 
        if(me->query_temp("honglian"))         
                return notify_fail("������ʹ�á������𡹡�\n");   
 
        if(me->query_temp("mz_lx"))         
                return notify_fail("������ʹ�á�������ħ�䡹��\n");   
 
        if((int)me->query_skill("jiechen-dao", 1) < 180 ) 
                return notify_fail("��Ľ䳾��������죬��������ᡸ������֮���ϡ�\n"); 
 
        if (me->query_skill_mapped("blade") != "jiechen-dao") 
                return notify_fail("�����ʹ�ý䳾����ʩչ�������𡹡�\n");    
 
        if( (int)me->query("max_neili", 1) < 3500 ) 
                return notify_fail("���������Ϊ̫����ʹ�����������𡹡�\n");                
 
        if( (int)me->query("neili", 1) < 800 ) 
                return notify_fail("����������������ʹ�����������𡹡�\n"); 
                 
        if(userp(me) && (int)me->query_skill("buddhism", 1) < 180 ) 
                return notify_fail("��������ķ������򲻹����޷�ʹ�á������𡹡�\n"); 
 
        if(userp(me) && me->query_skill_mapped("force") != "hunyuan-yiqi") 
                return notify_fail("����ڹ����ԣ���������ʹ���������𡹡�\n");        
                                                                                      
        if(!me->query("jiali")) 
                return notify_fail("��������ȫ������Ϊ�����㲻���������޷����ӳ����������ġ�\n"); 
 
        message_vision(RED "\n$N����䳾��֮�������𡹾����������������ʺ�ɫ����ӿ����\n" 
                           "����ǰ����֮�����㼴ͣס����������Ʈ���޶����������ڰ�գ�\n" 
                           "������������翣�����׽����ȴ��ɱ�������Σ�ʵ������������\n"    NOR, me); 
        me->start_busy(1); 
        me->set_temp("honglian", 1); 
        me->add("neili", -300); 
        me->add_temp("apply/parry", me->query_skill("jiechen-dao", 1)/2); 
        me->add_temp("apply/arrmor", me->query_skill("jiechen-dao", 1)/2); 
        check_fight(me); 
        return 1; 
} 
         
int check_fight(object me) 
{ 
        object *enemy, target; 
        int sz;         
 
        if (!me) return 0; 
 
        if(me->is_ghost() || !living(me) || environment(me)->query("no_fight") || me->query_temp("weapon")){ 
           me->add_temp("apply/parry", -me->query_skill("jiechen-dao", 1)/2); 
           me->add_temp("apply/arrmor",-me->query_skill("jiechen-dao", 1)/2); 
           me->delete_temp("honglian"); 
           return 0; 
           }         
         
        me->add("neili", -5); 
        enemy = me->query_enemy(); 
 
        if( !enemy || !arrayp(enemy) ) remove_effect(me); 
        sz = sizeof(enemy); 
        if( sz > 4 ) sz = 4; 
        if( sz > 0 ) target = enemy[random(sz)]; 
        else remove_effect(me); 
        if(!me->query_temp("honglian")) return 1; 
 
        else if(!me->is_fighting()) 
        { 
                if(!me->query_temp("stopped")) 
                { 
                    me->set_temp("stopped", 1); 
                    call_out("check_fight", 2, me); 
                } 
                else remove_effect(me); 
        } 
        else if (userp(me)) 
        { 
                  message_vision(HIY"$Nһ��������ͻȻ���У���Ȼ����ȫ��ͬ����������\n"NOR,me); 
                  me->start_busy(1); 
                  me->add_temp("apply/parry", -me->query_skill("jiechen-dao", 1)/2); 
                  me->add_temp("apply/arrmor", -me->query_skill("jiechen-dao", 1)/2); 
                  me->delete_temp("honglian"); 
                  return 1; 
        }    
       else if( me->query("neili") <= 10 || !target ) remove_effect(me); 
       else call_out("check_fight", 1, me); 
       return 1; 
}        
 
int remove_effect(object me) 
{ 
   string msg; 
   message_vision(HIY "\n$N����һ�к�����ʹ�꣬˫�ֺ�ʮ���ڵ��أ�ʾ�ȱ�Ϊ����\n\n"NOR, me); 
   me->add_temp("apply/parry", -me->query_skill("jiechen-dao", 1)/2); 
   me->add_temp("apply/armor", -me->query_skill("jiechen-dao", 1)/2); 
   me->delete_temp("honglian"); 
   me->delete_temp("stopped"); 
   remove_call_out("check_fight");  
   return 0; 
} 

