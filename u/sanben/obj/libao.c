
//������� �򿪺�Ϊ�޻���һ����Ǳ��ҩ��һ��(��10��Ǳ��)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "�������" NOR, ({ "libao", "bag" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "�Ͽ�open libao�������õ�ʲô�ɡ�\n" NOR);
                set("unit", "��");
                set("value", 10);
                set("no_sell",1);
                set("weight", 10);                
             }
        setup();
}

void init()
{       
     add_action("do_open","open");     
}
                
int do_open( string arg )
{       object me; 
        me = this_player();         
        
        if ( ! arg || (arg != "libao" &&
             arg != "bag") )
        return 0;

        message_vision(HIW "$N" HIW "������������˿�����\n" NOR, me);

        if (random(3) == 1)
        {
           tell_object(me, HIG"��ϲ������һeat guo��\n\n"NOR); 
        }
        write(HIG"��ָ����Ҫ���" + arg + "�����ԣ�������eat guo��\n\n"NOR); 
        return 1;    
}

