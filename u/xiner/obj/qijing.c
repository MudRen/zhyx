#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
        set_name(HIR "��������" NOR, ({ "sixiang qijing", "qijing" }) );
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("base_unit", "˿");
                set("base_weight", 1);
                set("base_value", 0);
//              set("material", "paper");  
                set("long", HIW "������˸�����Ĺ�â����ɵ�һ��" HIR "��������" HIW "��\n" NOR); 
	    	set("no_put", 1); 
        	set("no_steal", 1); 
//	        set("no_drop", 1); 
	        set("no_get", 1); 

        }
        set_amount(1);
        init_throwing(100);
        setup();
}
