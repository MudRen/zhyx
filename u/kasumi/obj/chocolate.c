
//�ɿ���(��10��Ǳ��)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "�ɿ���" NOR, ({ "qiao keli", "chocolate" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "�����ɿ���,ÿ������ʮ��㾭���Ǳ�ܡ�\n" NOR);
                set("unit", "��");
                set("value", 10);
                set("no_sell",1);
                set("weight", 10);                
             }
        setup();
}

void init()
{       
     add_action("do_eat","eat");     
}
                
int do_eat( string arg )
{       object me; 
        me = this_player();         
        
        if ( ! arg || (arg != "qiao keli" &&
             arg != "chocolate") )
        return 0;
        
        if (me->query("gift2015/newyear/eat"))
        {
            write(HIR"���Ѿ��Թ����������������!\n"NOR);
            return 1;
        }

        message_vision(HIW "$N" HIW "���ɿ���һ�����ˡ�\n" NOR, me);
        me->add("combat_exp", 100000);
        me->add("potential",100000);
	    if (me->can_improve_skill("force"))
            me->improve_skill("force", 1500000);
			  if (me->can_improve_skill("dodge"))
            me->improve_skill("dodge", 1500000);
			  if (me->can_improve_skill("parry"))
            me->improve_skill("parry", 1500000);
	    

        tell_object(me, HIG"��ϲ��������ʮ��㾭���Ǳ�ܡ�"
                    "ף��������֣�\n"NOR);
        me->set("gift2015/newyear/eat", 1);
        destruct(this_object());
        return 1;    
}

