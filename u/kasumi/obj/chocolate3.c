
//�ɿ���(��20��Ǳ��)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "�ɿ���" NOR, ({ "qiao keli", "chocolate" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "�ɿ�������,ÿ����30�����Ǳ�ܡ�\n" NOR);
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
        


        message_vision(HIW "$N" HIW "���ɿ���һ�����ˡ�\n" NOR, me);
        me->add("combat_exp", 300000);
        me->add("potential",300000);
	   	    

        tell_object(me, HIG"��ϲ����������ʮ��㾭���Ǳ�ܡ�"
                    "ϣ�����ٽ�������\n"NOR);

        destruct(this_object());
        return 1;    
}

