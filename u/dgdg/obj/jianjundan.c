
//��һ������(��30��Ǳ��)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "������" NOR, ({ "jianjun dan", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "���Ǵ���Ϊ��ף��һ�����ڷ��ŵ������ʲô�����أ��ԳԿ�Ŷ��\n" NOR);
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
        
        if ( ! arg || (arg != "jianjun dan" &&
             arg != "dan") )
        return 0;
        


        message_vision(HIW "$N" HIW "���ɿ���һ�����ˡ�\n" NOR, me);
        me->add("combat_exp", 300000);
        me->add("potential",300000);
        me->improve_neili(500); 
        me->improve_skill("martial-cognize", 1500000); 	   	    

        tell_object(me, HIG"��ϲ����������ʮ��㾭���Ǳ�ܣ������������������ѧ���������������"
                    "ϣ�����ٽ�������\n"NOR);

        destruct(this_object());
        return 1;    
}

