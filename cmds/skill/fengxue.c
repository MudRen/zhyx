// fengxue.c
// ���Ѩ����ֹ������ɢ�ͷ���

#include <ansi.h>

inherit F_CLEAN_UP;

void end_fengxue(object me)
{
         if (me->query_temp("fengxue"))
         {
               write(HIG "�㳤��һ������������յ�Ѩ�����Զ��⿪��\n");
 
               me->delete_temp("fengxue");

               me->set_temp("last_fengxue", time());        
         }

         return;         
}

// ��Ҫ���set fengxue 1

int main(object me, string arg)
{
         int force;
         object ob;

         if (me->is_busy() || me->is_fighting())
                 return notify_fail("����æ����˵�ɣ�\n");


         if (time() - me->query_temp("last_fengxue") < 60)
                 return notify_fail("���Ѩ���ճ忪�����ܼ�����Ѩ�ˡ�\n");

         force = me->query_skill("force");
/*
         if (me->query_skill("jingluo-xue", 1) < 100)
                  return notify_fail("��Ծ���ѧ�˽ⲻ�����޷���Ѩ��\n");
*/
         if (! arg)
         {
                if (me->query_temp("fengxue"))
                      return notify_fail("���Ѿ�������ҪѨ��ա�\n");                
          
                if (force < 300)
                      return notify_fail("���ڹ���Ϊ���㣬�޷����Լ�Ѩ����ա�\n");

                if (me->query("max_neili") < 2000)
                      return notify_fail("��������Ϊ���㣬�޷����Լ�Ѩ����ա�\n");

                message_vision(HIW "$N" HIW "������Ϣ������ʳָ�͵ص��������"
                               "������ҪѨ��ա�\n" NOR, me);

                me->set_temp("fengxue", 1);

                me->start_busy(2);

                me->start_call_out((: call_other, __FILE__,
                               "end_fengxue", me:), force / 5);

                return 1;                
         }    
         
         if( !objectp(ob = present(arg, environment(me))) )
		 return notify_fail("����û�� " + arg + "��\n");
         
         if (! playerp(ob))
                 return notify_fail("��ֻ�ܰ�����ҷ�Ѩ��\n");

         if (! ob->query("env/fengxue") || ob->query_temp("fengxue"))
                 return notify_fail("�Է����ڲ���Ҫ�������Ѩ��\n");

         if (force < 400)
                 return notify_fail("���ڹ���Ϊ���㣬�޷�����������ҷ�Ѩ��\n");

         if (me->query("neili") < 300)
                 return notify_fail("���������㣬�޷�����������ҷ�Ѩ��\n");

         if (me->query("max_neili") < 3000)
                 return notify_fail("��������Ϊ���㣬�޷�����������ҷ�Ѩ��\n");

         message_vision(HIY "$N" HIY "����������ָ�䣬�͵ص���$n" HIY "��"
                        "�����������ҪѨ��ա�\n" NOR, me, ob);

         ob->set_temp("fengxue", 1);

         ob->start_busy(2);
         me->start_busy(2);
         me->add("neili", -220);

         me->start_call_out((: call_other, __FILE__,
                           "end_fengxue", ob:), force / 5);
         return 1;
}

int help(object me)
{
  write(@HELP
ָ���ʽ : fengxue [���ID]

��ָ��������ж�ʱ��ʱ��Ѩ����գ����ⶾ�Է�����
��Ѩ���忪��һ�����ڲ����ټ�����Ѩ��

HELP
);
    return 1;
}
 
