#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + MAG "������" NOR, ({ "dragon beard", "beard" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + MAG "һ���Ϻ����Ե����룬���Ϻ�ɫ��\n" NOR);
                set("unit", "��");
                set("value", 200000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
