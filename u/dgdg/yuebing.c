
//�����±�(��50��Ǳ��)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "�����±�" NOR, ({ "huotui yuebing", "bing" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "���Ǵ���Ϊ��ף�������ڷ��ŵ��±���Ը��������³ɡ�\n" NOR);
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
        
        if ( ! arg || (arg != "huotui yuebing" &&
             arg != "bing") )
        return 0;
        


        message_vision(HIW "$N" HIW "���±���������ҧ�����¡�\n" NOR, me);
        me->add("combat_exp", 500000);
        me->add("potential",500000);
        me->improve_neili(500); 
        me->improve_skill("martial-cognize", 1500000); 	   	    

        tell_object(me, HIG"��ϲ����������ʮ��㾭���Ǳ�ܣ������������������ѧ���������������"
                    "��ף�����������죡\n"NOR);

        destruct(this_object());
        return 1;    
}

