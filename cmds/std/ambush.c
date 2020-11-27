// ambush.c  ��ϳ��������������ָ��
#include <ansi.h>
#define QUARRY_OBJ   "/clone/quarry/"             //�����·��
 
inherit F_CLEAN_UP;

int main(object me)
{
        object ob;      

        if ( me->query("changanjob/kind") != "hunt" )        
        return notify_fail("������û����ȡ��ɱҰ�޵����񣬲��������\n");         

        if ( me->query("changanjob/ok") )        
        return notify_fail("�������Ѿ���ɱ������������ˣ����ȥ�����ɣ�\n");       
        
        if ( environment(me)->query("no_fight") )
        return notify_fail("���ﲻ��ս���������������\n");     

        if ( me->is_busy() || me->query("doing") )
        return notify_fail("��������æ���أ�\n");  
 
        if ( me->is_fighting() )
        return notify_fail("������������أ���ô�������\n"); 

        if (me->query("qi") < 30 )
        return notify_fail("����������̫����������\n"); 

        if (me->query("jing") < 30 )
        return notify_fail("�����ھ���̫����������\n"); 
     
        message_vision(HIC"$N�ҵ�һ��Ƨ���Ľ��䣬�����������\n"NOR, me);        
        me->set_short_desc("������ڴ˵ء�");
        me->delete_temp("pending/ambush");  
              
        me->start_busy((:call_other, __FILE__, "ambush" :), 
                      (:call_other, __FILE__, "halt_ambush" :)); 
        return 1;
}

int ambush(object me)
{
      object env;
      
      env = environment(me);

      if (me->add_temp("pending/ambush", 1) > 10 )
      {
          tell_object(me, HIY "������˰��죬����û��Ұ�޳��֣�ֻ����ʱ������\n" NOR);
          message("vision", HIY + me->name() + HIY "�����˾��񣬿�����ʱ���ټ�������ˡ�\n" 
                   NOR, env, ({ me }));
          me->set_short_desc(0);
          me->delete_temp("pending/ambush"); 
          return 0;
       } 

        if (me->query("qi") < 20 ||
            me->query("jing") < 20)
        {
                tell_object(me, HIY "��ʵ��̫ƣ���ˣ������ټ��������ֻ������Ϣһ�¡�\n" NOR);
                message("vision", HIC + me->name() + HIC "һ�����ݣ���ʼ������Ϣ��\n" NOR,
                        env, ({ me }));
                me->set_short_desc(0);
                me->delete_temp("pending/ambush"); 
                return 0;
        }
        me->receive_damage("qi", 5);
        me->receive_damage("jing", 5);


       if ( me->query("changanjob/kind") == "hunt" &&
            me->query("changanjob/place") == env->short() &&
            me->query_temp("pending/ambush") > 5 &&
            random(3) == 1 )
       {
          call_other(__FILE__, "set_beast", me);       
          me->set_short_desc(0);
          me->delete_temp("pending/ambush"); 
          return 0;
        }
       return 1;
}

int halt_ambush(object me)
{            
	 message_vision(HIG"$N��չ��һ���ֽţ����ټ�������ˡ�\n"NOR, me);        
        me->set_short_desc(0);  
        me->delete_temp("pending/ambush");     
        return 1;
}

void set_beast(object me)
{         
          string *list;
          object beast;
          int exp;
          exp = me->query("combat_exp");
          if (exp < 400000) exp = 400000;

          list = get_dir(QUARRY_OBJ);
          beast = new(QUARRY_OBJ + list[random(sizeof(list))]); 
          if ( ! beast || beast == 0) call_other(__FILE__, "set_beast", me); 
          else
          { 
             if ( exp / 10000 - beast->query("power") <= 30
                  || exp / 10000 - beast->query("power") >= 50 )
                 call_other(__FILE__, "set_beast", me);  
             else
             {
          	   beast->set("owner", me->query("id") );
          	   beast->set("no_auto_kill", 1);
          	   beast->move(environment(me));              
         	   message_vision(HIR"ͻȻ��֪��������ڳ���һֻ"NOR "$N" NOR 
                               HIR"��\n$n�ڵ�һ����������ȥ��\n" NOR, beast, me);
                 me->kill_ob(beast);
                 beast->kill_ob(me);
              }
          }
}

int help(object me)
{
        write(@HELP
���ָ�������������ȴ�Ұ�޳��ֽ������
HELP );
        return 1;
}

