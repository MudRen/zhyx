#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + MAG "����Ƥ��" NOR, ({ "dragon pige", "pige" }));
        set_weight(8000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + MAG "һ�ž޴���Ƥ�����Ϻ�ɫ����Ӳ�ޱȡ�\n" NOR);
                set("unit", "��");
                set("value", 1000000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
