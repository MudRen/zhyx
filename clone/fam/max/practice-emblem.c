#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(MAG "�Ͻ���ϰѫ��" NOR, ({ "practice emblem", "emblem" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", MAG "�������Ͽ���������ϰ���������ٴΡ�\n" NOR);
                set("unit", "��");
                set("can_summon", 1);
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}

