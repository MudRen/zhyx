
//�����裬��һ����ò

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "������" NOR, ({ "meirong wan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "\n��һ����ò��������������������Ʒ�����ı�֤��\n" NOR);
                set("unit", "��");
                set("value", 10);
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

        if ( ! arg || (arg != "meirong wan") )
          return 0;
	
	 me = this_player();

       /* if (me->query("gf09tangyuan/eat") >= 3 )
        {
             write("����ô����Բ,���뱥����?\n");
             return 1;
        } */
 if (me->query("per")>25)  
 	         {
 	         	 write("���Ѿ�����Ư���˰�����Ҫ���ݣ�"); 
 	         	 return 1;
 	         	 }
 	         
        message_vision(HIY "�㽫������һ�����ˣ�������˳����Ǿ����˳�����\n" NOR, me);

 	if (random(2)==1) 
  		{
  		tell_object(me,HIG"\n����Ʒ���ã���γԵ�ʧ���ˣ�δ��������ò�����Ͱ�!\n"NOR);
  		return 1;
  	}
   	 

		
			 me->add("per",1);
       tell_object(me, HIG"��ϲ��,����һ����ò���������˼��˰����������صĿ�����Ů��ά�������ƽ������ͽ�������!\n" NOR);
		  destruct(this_object());
       return 1;
}


		       	