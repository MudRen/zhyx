#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "����" NOR, ({ "dragon beard", "beard" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "һ�������ĺ��롣\n" NOR);
                set("unit", "��");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}