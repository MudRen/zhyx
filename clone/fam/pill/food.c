// ����

#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
    set_name(NOR + WHT "����" NOR, ({ "gan liang", "gan", "liang" }));
    set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else {
        set("long", NOR + WHT "����һ�����Я���ĸ�����\n" NOR);
		set("unit", "��");
		set("value", 50);
		set("food_remaining", 20);
		set("food_supply", 500);
	}
}



