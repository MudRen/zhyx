// yuchang /2002/3/15/
#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "�ֱ�");
        set("long", @LONG 
�����ø�����ĸֱ�,̽�첻�����ĺ��,���ǹ��Ʋ���,
�������������ڹ������Ǻܷ�������!���ǿ��(jump)����
ȥ�ɡ�
LONG);
        setup();
}

void init()
{
    object me;
    me = this_player();

    if (userp(me))
   {
       remove_call_out("do_suck");
       call_out("do_suck", 1, me);
   }
    
   add_action("do_jump", "jump"); 
}

int do_jump(string arg)
{
    object me; 
    me = this_player();

    if ( !arg || arg != "up" ) 
    {
       write("����Ҫ����(up)����!\n");
       return 1;
    }
    if (me->query_skill("dodge",1) < 600)
    {       
       write("��ƴ��������,������Ϊ�Ṧ����ʧ����!\n\n");
       write(HIR"������ֻ�й�����������ˣ�\n\n"NOR);
       return 1;
     } 

     write(HIY"����������һԾ�����ص����ܵ�!\n\n");

     write(BLINK HIR"��ͻȻ����ԭ����ť���ұ߻��и���ť!\n\n"NOR);

     me->set_temp("tongguo",1);
     me->move(__DIR__"tongdao5");
     return 1;
}

    
void do_suck(object me)
{
     if (!me) return;
     if (environment(me) != this_object()) return;  
  
     if ( me->query("neili") > 0 )
     {
       tell_object(me, HIR"��е����ϵ���������������!\n"NOR);
       me->add("neili", - (500 + random(500))); 
     }

     if (me->query("neili") <= 1500) 
    {    
        tell_object(me, BLINK HIB"��������Ѿ���ľ��ˣ�"
                        "�ٲ�����취��Σ����!\n"NOR); 
    }  

    if ( me->query("neili") > 0 )
    {
       remove_call_out("do_suck");
       call_out("do_suck", 2, me);
    }
    else
   {
       me->set_temp("die_reason", "�����޵׶�ˤ����");
       me->die();    
   }
}