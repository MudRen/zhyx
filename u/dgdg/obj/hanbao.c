
//��������������һ����ò

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "����������" NOR, ({ "hanbao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "\n�Դ���������������Ӣ�ۡ�\n" NOR);
                set("unit", "��");
                set("value", 10000000);
                set("weight", 100);                
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

        if ( ! arg || (arg != "hanbao") )
          return 0;
	
	 me = this_player();

       /* if (me->query("gf09tangyuan/eat") >= 3 )
        {
             write("����ô����Բ,���뱥����?\n");
             return 1;
        } */
 if (me->query("per")<1)  
 	         {
 	         	 write("���Ѿ������ˣ����ԣ�"); 
 	         	 return 1;
 	         	 }
 	         
        message_vision(HIY "$N������������һ�����ˣ�������˳����Ǿ����˳�����\n" NOR, me);

  
   	 
	 me->add("per",-1);
	

	 
tell_object(me, HIG"��ϲ��,����һ����ò!���˴�����������ά�������ƽ������ͽ�������!\n" NOR);
		destruct(this_object());
      return 1;
}


		       	