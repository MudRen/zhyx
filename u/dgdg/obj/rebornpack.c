//ת���������


#include <ansi.h>
inherit ITEM;


void create()
{
        set_name(NOR + HIY "ת���������" NOR, ({ "reborn pack" ,"pack" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "�������������Է��ŵ�ת�����������"
                            "������������Ŷ��\n");                
                set("no_put", "�������������뿪�㡣\n");
                set("no_sell", "�������������뿪�㡣\n");
        }
        setup();
}

void init()
{
     add_action("do_open","open");    
}

int do_open( string arg )
{
    object me, gift; 
    object where; 


    if ( !arg || arg != "reborn pack")
    return notify_fail("��Ҫ��ʲô��\n");


    me = this_player(); 
    where = environment(me); 
    gift = new("/clone/fam/max/noname");
    gift->move(me);
    tell_object(me, HIY"��ϲ������ת�����\n"NOR);  

    destruct(this_object());   
    return 1;

}

