
//������

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "������" NOR, ({ "zhengqi guo", "guo"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "���������������˻�ʹ������֮������!\n" NOR);
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
        

        if ( ! arg || ( arg != "zhengqi guo" && arg != "guo"))
        return notify_fail("��Ҫ��ʲô?\n"); 
             

         if (me->query("shen") > 1000000)
         {
            tell_object(me, HIC"��������Ѿ������ˣ��ٳ�Ҳû����!\n"NOR);
            return 1;
         }
       
         message_vision(HIR "$Nһ�ڽ������������˶��ӣ���ʱһ����Ȼ����Ϯ������!\n" NOR, me);
         tell_object(me, HIC"�������������!\n"NOR);

         me->add("shen", 2000 + random(500));

         destruct(this_object());
         return 1;
}
                
int query_autoload() 
{ return 1; }


        
