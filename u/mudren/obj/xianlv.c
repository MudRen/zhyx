// xianlv.c

#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name( HIW "����" NOR, ({ "shoe", "xian lv" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "˫");
                set("long", "һ˫���˲Ŵ���Ь������������ͨͨ�ġ�\n");
                set("value", 100);
                set("armor_prop/armor", 1);
                set("material", "boots");
        }
        setup();
}
void init()
{
add_action("do_beep","bbb");
}

do_beep()
{
	tell_object(this_player(),BEEP);
}
