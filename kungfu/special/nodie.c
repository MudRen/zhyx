// nodie.c ��������

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return YEL "��������" NOR; }

int perform(object me)
{
      
       if (! me->query("reborn"))        
            return notify_fail("����δת���������޷�ʹ�ô˼��ܣ�\n");

       if ( time() - me->query("la_sp_tm/nodie") < 600 )        
            return notify_fail("��Ҫ��Щʱ��������ô˼��ܣ�\n");

        message_vision(YEL "$N" YEL "��ɫһ����ȫ��ɢ����һ���⣬"
                       "�����޺�ת��һ�㡣\n" NOR, me);
       
       me->set_temp("no_die",1);
       me->set("la_sp_tm/nodie", time());        

   	me->start_call_out((: call_other, __FILE__, "remove_effect", me :), 60);

        return 1;
}

void remove_effect(object me)
{
     me->delete_temp("no_die");
     tell_object(me, "��ʩչ�겻����������һ������\n");
}
