
//����

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(WHT "����" NOR, ({ "wane guo", "guo"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIB "�������������˻�ʹ��а������!\n" NOR);
                set("unit", "��");
                set("value", 10);
                set("no_sell",1);
                set("weight", 10); 
                set("can_cun",1);               
             }
        setup();
}

void init()
{                       
        add_action("do_eat","eat");
}
                
int do_eat( string arg )
{     
         object me;        
         me = this_player();
        

        if ( ! arg || ( arg != "wane guo" && arg != "guo"))        
        return 0;
             

         if (me->query("shen") < -1000000)
         {
            tell_object(me, HIR"���а���Ѿ���ʢ�ˣ��ٳ�Ҳû����!\n"NOR);
            return 1;
         }
       
         message_vision(WHT "$Nһ�ڽ����������˶��ӣ���ʱһ��а��Ϯ����ͷ!\n" NOR, me);
         tell_object(me, HIB"���а��������!\n"NOR);

         me->add("shen", - 2000 - random(500));

         destruct(this_object());
         return 1;
}
                
int query_autoload() 
{ return 1; }


        
