#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "����������" NOR, ({ "buchen sheli", "sheli" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "������ʦ�����������һ�������ӡ�\n" NOR);
                set("unit", "��");
                set("value", 5000);
                set("weight", 50);
		set("no_sell", 1);
        }
        setup();
}
