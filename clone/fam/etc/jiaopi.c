#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + MAG "����Ƥ" NOR, ({ "dragon skin", "skin" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + MAG "һ����Ƥ�����Ϻ�ɫ����Ӳ�ޱȣ����ϵ�Ƥ��ԭ�ϡ�\n" NOR);
                set("unit", "��");
                set("value", 100000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
