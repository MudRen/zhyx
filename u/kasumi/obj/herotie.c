


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "����Ӣ����" NOR, ({ "yingxiong tie"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "\nһ�ž���������Ӣ����������������Բμӻ�ɽ�۽������ᡣ\n" NOR);
                set("unit", "��");
                set("value", 200000);
                set("weight", 10);                
             }
        setup();
}
