
//���ڽ���

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "���ڽ���" NOR, ({ "jiaozi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "���ڲ��ܳԵ��Ľ��ӡ�\n" NOR);
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

        if ( ! arg || (arg != "jiaozi") )
          return 0;
	
	 me = this_player();

        if (me->query("gift2007/eat") >= 5 )
        {
             write("������������Ѿ���̫����,�ٳԾ�����������!\n");
             return 1;
        }

        message_vision(HIY "$N������һ�����ˣ�������˳����Ǿ����˳�����\n" +
				"��һ��������˵:ζ���ü���Ӵ������������һ��!\n" NOR, me);


	 me->add("combat_exp", 50000);

	 mapsk = me->query_skill_mapped("force");
        	if (me->can_improve_skill("force"))
                	me->improve_skill("force", 1500000);
      //  	if (stringp(mapsk) && me->can_improve_skill(mapsk))
      //          	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("parry");
        	if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
     //   	if (stringp(mapsk) && me->can_improve_skill(mapsk))
     //           	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("dodge");
        	if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
    //    	if (stringp(mapsk) && me->can_improve_skill(mapsk))
      //          	me->improve_skill(mapsk, 1500000);
        me->add("gift2007/eat",1);

		destruct(this_object());
      return 1;
}


		


       	