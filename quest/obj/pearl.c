#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW"ҹ����"NOR, ({ "lighting-pearl"}) );
        set_weight(3);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ���ں�ҹ���������ҹ���顣\n");
                set("value", 10000);
        }
}

