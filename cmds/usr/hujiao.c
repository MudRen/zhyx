// hujiao.c

#include <ansi.h>

inherit F_CLEAN_UP;

int help(object me);

void create()
{
        seteuid(getuid());
}

int main(object me, string arg)
{
        object obj;

        if( ((int)me->query("jing") < 50) &&(!wizardp(me)))
                return notify_fail("��Ŀ�ˮ������ˣ�Ъ���������ɡ�\n");
         if (me->is_busy()) 
          return notify_fail("�԰����꣬�԰����ꡣ\n"); 
        if(!arg || arg == "")
        {
           message_vision(CYN"$N�������ıȻ��˼������ƣ���Ȼ�벻���Լ�����Ҫ��ʲô�ˡ�\n"NOR,me);
           return 1;
        }
        obj = find_player(arg);
        if(!obj || !me->visible(obj)) 
           return notify_fail("û�������....\n");
        if(obj->query("id") == me->query("id"))
        {
           message_vision(CYN"$N�������ıȻ��˼������ƣ������������������ɳ��һ���ӽ���һ����....��\n"NOR,me);
           return 1;
        }
    message_vision(CYN"$N�������ıȻ��˼������ƣ�һ��͵͵������������飬�����飬�������������....��\n"NOR,me);
    tell_object(obj,HIW"������������������"+me->name(1)+"�����������㣡\n"+
BEEP BEEP NOR);
        call_out("do_beep",1,obj);
    call_out("do_beep",2,obj);
    call_out("do_beep",4,obj);
        if( !wizardp(me) )
        {
         me->start_busy(2); 
                me->receive_damage("jing", 50);
        }
        return 1;
}

int do_beep(object obj)
{
   if(!obj)   return 1;
   tell_object(obj,
BEEP);
   return 1;
}


int help(object me)
{
        write(@HELP
ָ���ʽ��hujiao <ĳ��>

ֻҪ�����δ����䣬������е��˵������ڱ������ʾ��������

HELP
        );
        return 1;
}


