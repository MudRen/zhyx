


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "���������״�ȫ" NOR, ({ "cheat miji", "zuobi shu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "\nһ����˵�е����飬��˵���Եõ�mud���������еļ��ܡ������ͨ����use����ʹ�á�\n" NOR);
                set("unit", "��");
                set("value", 10000000);
                set("weight", 100);                
             }
        setup();
}

void init()
	{
		add_action("do_use","use");
	}
		

int do_use( string arg )
{		
	 string mapsk;	 
	 object me;

        if ( ! arg || (arg != "chat miji" && arg != "zuobi shu") )
          return 0;
	
	      me = this_player();
	      
	      	      
        message_vision(HIG "$N"HIG"�������������ϵ���......\n" NOR, me); 
        
        me->unconcious();

		destruct(this_object());
      return 1;
}

string query_autoload()
{
        if ( ! query("owner") )
                return 0;

        return query("owner");
}

void autoload(string owner)
{       
     if (owner) set("owner", owner);
}


		


       	