#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "����" NOR, ({ "dragon palta", "palta" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "һƬ���ۣ���ʶ�Ŀ��\n" NOR);
                set("unit", "Ƭ");
                set("value", 100000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
