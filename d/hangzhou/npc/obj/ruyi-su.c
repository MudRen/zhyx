// food by ruri
#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name(HIM"������"NOR, ({"ruyi su", "su"}));
	set_weight(80);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ��õ��ɫ�ĵ��ģ���˵�Ǻ����������ģ���֪�����Ǽ٣�\n");
		set("unit", "��");
		set("value", 5000);
		set("food_remaining", 3);
		set("food_supply", 20);
	}
}
