
//������Բ

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "Ԫ������Բ" NOR, ({ "tangyuan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "Ԫ���ڲ��ܳԵ�����Բ,����ʦ��������������,��Ҫ�иж�����Ŷ,�������绰����?\n" NOR);
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

        if ( ! arg || (arg != "tangyuan") )
          return 0;
	
	 me = this_player();

        if (me->query("gf09tangyuan/eat") >= 3 )
        {
             write("����ô����Բ,���뱥����?\n");
             return 1;
        }

        message_vision(HIY "$N����Բһ�����ˣ�������˳����Ǿ����˳�����\n" +
				"��һ��������˵:ζ���ü���Ӵ������������һ��!\nͻȻԶ��Ʈ��һ������\n\n���б������\n��������Բȱ\n���¹���ȫ\n��Ը�˳���\nǧ�ﹲ濾�.\n\n������,����һ��ʧ��,����Զ��������.����Ȼ������.\n"NOR, me);


	 me->add("combat_exp",60000);
	 me->add("potential",60000);

	 mapsk = me->query_skill_mapped("force");
        //	if (me->can_improve_skill("force"))
         //       	me->improve_skill("force", 1500000);
     	if (stringp(mapsk) && me->can_improve_skill(mapsk))
              	me->improve_skill(mapsk, 1500000);

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
        me->add("gf09tangyuan/eat",1);
tell_object(me, HIG"��ϲ�������˾����Ǳ�ܡ�"
                    "ף��Ԫ�����֣�\n"NOR);
		destruct(this_object());
      return 1;
}


		


       	