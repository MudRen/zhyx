#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "�׻�Ƥ��" NOR, ({ "baihu pige", "pige" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "һ�ž޴�İ׻�Ƥ���������Ʒ��\n" NOR);
                set("unit", "��");
                set("value", 1000000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
