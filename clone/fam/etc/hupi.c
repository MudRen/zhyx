#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "�׻�Ƥ" NOR, ({ "tiger skin", "skin" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "һ�Ű׻�Ƥ�������¼�Ʒ�����亱�С�\n" NOR);
                set("unit", "��");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
