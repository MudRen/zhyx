#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "�׻���" NOR, ({ "tiger bone", "bone" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "һ���׻��ǣ������¼�Ʒ�����亱�С�\n" NOR);
                set("unit", "��");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
