// patrol.c  ��ϳ�����Ѳ�������ָ��
#include <ansi.h>
 
inherit F_CLEAN_UP;

int main(object me)
{
        object ob;      

        if ( me->query("changanjob/kind") != "patrol" )        
        return notify_fail("������û����ȡѲ�ǵ�����\n");         

        if ( me->query("changanjob/ok") )        
        return notify_fail("�������Ѿ���ɱ���Ѳ�������ˣ����ȥ�����ɣ�\n");  
    
        if ( me->is_busy() || me->query("doing") )
        return notify_fail("��������æ���أ�\n");  
 
        if ( me->is_fighting() )
        return notify_fail("������������أ���ô��Ѳ�ǣ�\n"); 

        if (me->query("qi") < 30 )
        return notify_fail("����������̫�����Ѳ�ǣ�\n"); 

        if (me->query("jing") < 30 )
        return notify_fail("�����ھ���̫�����Ѳ�ǣ�\n"); 
     
        message_vision(HIC"$N����������������ϸ������û�п��ɵ��ˡ�\n"NOR, me);        
        me->set_short_desc("����Ѳ�ǡ�");
        me->delete_temp("pending/patrol");  
              
        me->start_busy((:call_other, __FILE__, "patrol" :), 
                      (:call_other, __FILE__, "halt_patrol" :)); 
        return 1;
}

int patrol(object me)
{
      object env, *ob;
      int i, flag, have; 
      
      env = environment(me);
      flag = 0;
      have = 0;

      for( i=0; i < 5; i++ )
        {
	   if ( me->query("changanjob/place/" + (i+1)) == env->short() )
          flag = i + 1;
        } 

      if (me->add_temp("pending/patrol", 1) > 8 )
      {      
         message_vision(HIY"$NѲ���˰��죬���ֲ��޿���֮�ˡ�\n"NOR, me);          
        if ( flag != 0 )        
       {   ob = all_inventory(me);
            for(i=0; i<sizeof(ob); i++) 
              {   
                  if (ob[i] == me->query("changanjob/gonghan"))
                     {                                       
                         have = 1;  
                         break;
                     }  
               }      
            if ( have == 0 )   
                message_vision(HIR"$N������ʼ��´˵��ΰ����ã�"
                           "ȴ��������û����¼����Ѳ�ǵĹ�����\n"NOR, me);          
            else
            {
                message_vision(HIG"$N����ڱ���Ѳ�ǵĹ����ϼ��´˵��ΰ����á�\n"NOR, me);
                for( i=0; i < 5; i++ )
                {
                   if ( me->query("changanjob/place/" + (i+1)) == env->short() )
                   {
	               me->set("changanjob/placeok/" + (i+1), 1);
                      me->query("changanjob/gonghan")->set("placeok/" + (i+1), 1);
                   }
                } 
     
            }
         }
          me->set_short_desc(0);
          me->delete_temp("pending/patrol"); 
          return 0;
       } 

        if (me->query("qi") < 20 ||
            me->query("jing") < 20)
        {
                tell_object(me, HIY "��ʵ��̫ƣ���ˣ�ֻ������Ϣ׼��һ����ټ���Ѳ�ǡ�\n" NOR);
                message("vision", HIC + me->name() + HIC "һ�����ݣ���ʱֹͣѲ��׼����Ϣ��\n"
                                  NOR, env, ({ me }));
                me->set_short_desc(0);
                me->delete_temp("pending/patrol"); 
                return 0;
        }
        me->receive_damage("qi", 5);
        me->receive_damage("jing", 5);

       if ( me->query("changanjob/kind") == "patrol" &&
            ! me->query("changanjob/catch") &&
            flag != 0 &&  
            ! me->query("changanjob/placeok/" + flag )  &&
            me->query_temp("pending/patrol") > 5 && 
            random(12) == 1 &&
            me->query("changanjob/catch_num") < 3 )
       {
          call_other(__FILE__, "set_liumang", me);       
          me->set_short_desc(0);
          me->delete_temp("pending/patrol"); 
          return 0;
        }
       return 1;
}

int halt_patrol(object me)
{            
	 message_vision(HIG"$N���˿������������ټ����ڴ˴�Ѳ���ˡ�\n"NOR, me);        
        me->set_short_desc(0);  
        me->delete_temp("pending/patrol");     
        return 1;
}

void set_liumang(object me)
{                   
          object lm;
          int exp, lv, qi, jing;
              
          lm = new("/u/sanben/changan_job/liumang");
          exp = me->query("combat_exp");
          lv = to_int(pow(to_float(exp*10), 1.0 / 3)) + 1;       
          qi = me->query("max_qi") * 3 / 2;
          jing = me->query("max_jing") * 3 /2;

          lm->set("max_qi", qi);
          lm->set("max_jing", jing);         
	   lm->set("eff_jing", jing);
	   lm->set("jing", jing);
          lm->set("eff_qi", qi);
	   lm->set("qi", qi);

          lm->set("combat_exp", exp * 3 / 2);
	   lm->set_skill("unarmed", lv + random(10));
	   lm->set_skill("dodge", lv + random(10));
	   lm->set_temp("apply/attack", lv * 3 / 4 + random(5));
	   lm->set_temp("apply/defense", lv * 3 / 4 + random(5));
          lm->set_temp("apply/dodge", lv * 3 / 4 + random(5));

          lm->move(environment(me));              
          message_vision(HIW"ͻȻ��Χ���˴󺰣�ץ����ץ����$N����һ����һ��$n���Ĵ����ӡ�\n"NOR  
                             HIR"ֻ��$N���һ���������ӣ��漴�ܲ����������$n��\n" NOR, me, lm);
          me->competition_with(lm);
          lm->competition_with(me);      
}

int help(object me)
{
        write(@HELP
���ָ����Ѳ��ʱʹ�á�
HELP );
        return 1;
}

