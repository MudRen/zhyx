
//����ɿ��� ָ��һ���츳 ��һ��

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "����ɿ���" NOR, ({ "chocolate", "xiao keli"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "����츳���������wish��eat��"+
				     "���������˵��ζ���ð�����\n" NOR);
                set("unit", "��");
                set("value", 10);
                set("weight", 10);                
             }
        setup();
}

void init()
	{	
		add_action("do_wish","wish");
		add_action("do_eat","eat");
	}
		

int do_wish( string arg )

	{	this_player()->set_temp("wish_tianfu1", arg);	
	    if (arg == "����")
		{ this_player()->set_temp("wish_tianfu", "str");
		  write("��ָ����Ҫ��һ��"HIY+ arg + NOR"��\n");return 1;}
	    if (arg == "����")
		{ this_player()->set_temp("wish_tianfu", "int");
		  write("��ָ����Ҫ��һ��"HIW+ arg + NOR"��\n");return 1;}
	    if (arg == "����")
		{ this_player()->set_temp("wish_tianfu", "con");
		  write("��ָ����Ҫ��һ��"YEL+ arg + NOR"��\n");return 1;}
	    if (arg == "��")
		{ this_player()->set_temp("wish_tianfu", "dex");
		  write("��ָ����Ҫ��һ��"HIR+ arg + NOR"��\n");return 1;}		

	    else { write("��Ҫ�������츳������wish ����\n");}	    
	    return 1;
	}

int do_eat( string arg )
{	
	if (arg == "chocolate" || arg == "qiao keli")

	{	 	 
	 object me;
	
	 me = this_player();

        if (me->query_temp("wish_tianfu") == 0 )
        {write(HIR"������wish <�츳> ָ����Ҫ�������츳��\n"NOR);return 1;}
	 
	 log_file("static/yuanxiao", sprintf("%s(%s) eat ����ɿ��� at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));
        message_vision(HIY "$Nһ�ڽ��ɿ��������˶��ӣ��о��������˺�����ı仯��\n" NOR, me);
	 write(HIG"�������" + me->query_temp("wish_tianfu1") + "��������һ�㡣\n"NOR);

        me->add(me->query_temp("wish_tianfu"), 1);
	        	
	 me->delete_temp("wish_tianfu");
	 me->delete_temp("wish_tianfu1");

	 destruct(this_object());
	 return 1;
	}
else {	return 0;}
}
		


       	