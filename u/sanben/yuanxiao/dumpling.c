
//Ԫ����Բ  (����force,force,dodge,parry)����1��
//ÿ��id��������

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "Ԫ����Բ" NOR, ({ "tang yuan", "yuan", "dumpling" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "Ϲ����������ԲԲ��Բ��\n" NOR);
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
	if (arg == "tang yuan" || arg == "yuan" || arg == "dumpling")

	{
	 string mapsk;	 
	 object me;
	
	 me = this_player();

        if (me->query("eat_dumpling") > 1 )
        {write(HIR"�����������ˣ��ٳԾ����������ˣ�\n"NOR);return 1;}

        message_vision(HIY "$N����Բһ�����ˣ��������ӡ�˳����Ǿ����˳�����\n" +
				"��һ��������˵:��ζ���ü���Ӵ������������һ��!\n" NOR, me);

	 log_file("static/yuanxiao", sprintf("%s(%s) eat Ԫ����Բ at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

        me->add("eat_dumpling", 1);

	 me->add("combat_exp", 50000);
	 mapsk = me->query_skill_mapped("force");
        	if (me->can_improve_skill("force"))
                	me->improve_skill("force", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("parry");
        	if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("dodge");
        	if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);

		destruct(this_object());
		return 1;
	}
else {	return 0;}
}
		


       	