// jiexue.c
// �忪��յ�Ѩ��

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
         int force;
         object ob;

         if (me->is_busy() || me->is_fighting())
                 return notify_fail("����æ����˵�ɣ�\n");

         force = me->query_skill("force");

         if (1)
         {
                if (! me->query_temp("fengxue"))
                      return notify_fail("��Ѩ����û�з�հ���\n");
          
                if (force < 300)
                      return notify_fail("���ڹ���Ϊ���㣬�޷�����յ�Ѩ���忪��\n");

                if (me->query("max_neili") < 2000)
                      return notify_fail("��������Ϊ���㣬�޷�����յ�Ѩ���忪��\n");

                message_vision(HIW "$N" HIW "�����ڹ���һ����������ȫ�������\n" NOR, me);

                write(HIG "��������յ�Ѩ���ѱ��忪��\n" NOR);

                me->delete_temp("fengxue");
                me->set_temp("last_fengxue", time());
                me->start_busy(2);

                return 1;
         }    
}

int help(object me)
{
  write(@HELP
ָ���ʽ : chongxue

��ָ����Խ�����յ�Ѩ���忪��
HELP
);
    return 1;
}
 
