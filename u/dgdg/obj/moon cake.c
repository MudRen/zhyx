
//���������

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "�±�" NOR, ({ "moon cake" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "������ʦ����������Ϊ��������Ƶġ��±�������˵���ԳԺü��������Զ��˾ͻ������С��Ŷ��������\n" NOR);
                set("unit", "��");
                set("value", 10);
                set("weight", 10);                
             }
        setup();
}

void init()
	{
		add_action("do_eat","eat");
	}
		

int do_eat( string arg )
{		
	 string mapsk;	 
	 object me;

        if ( ! arg || (arg != "moon cake") )
          return 0;
	
	 me = this_player();

        if (me->query("moon cake/eat") >= 3 )
        {
             write("����ô���±����뱻������?\n");
             return 1;
        }

        message_vision(HIY "$N���±�һ�����ˣ�������˳����Ǿ����˳�����\n" +
				"һ�������ش��ű���!\n\n"NOR, me);


	 me->add("combat_exp",random(5)*10000);
	 me->add("potential",random(5)*10000);

	 mapsk = me->query_skill_mapped("force");
        //	if (me->can_improve_skill("force"))
         //       	me->improve_skill("force", int(random(3000000));
     	if (stringp(mapsk) && me->can_improve_skill(mapsk))
              	me->improve_skill(mapsk,random(500)*10000);

        	mapsk = me->query_skill_mapped("parry");
        	if (me->can_improve_skill("parry"))
                	me->improve_skill("parry",random(500)*10000);
     //   	if (stringp(mapsk) && me->can_improve_skill(mapsk))
     //           	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("dodge");
        	if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", random(500)*10000);
    //    	if (stringp(mapsk) && me->can_improve_skill(mapsk))
      //          	me->improve_skill(mapsk, 1500000);
        me->add("moon cake/eat",1);
tell_object(me, HIG"��ϲ�㡣"
                    "ף������ڿ��֣�\n"NOR);
		destruct(this_object());
      return 1;
}


		


       	