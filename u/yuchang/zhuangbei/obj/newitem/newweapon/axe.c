// bigaxe.c

#include <weapon.h>

inherit AXE;

void create()
{
	set_name("��", ({ "axe" }) );
	set_weight(6000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("material", "steel");
		set("long", "����һ�ѳ��صĸ�ͷ�����������ǳ�˳�֣�");
		set("value", 1100);
		set("wield_msg", "$N�ó�һ��$n���������е���������\n");
		set("unwield_msg", "$N�������е�$n��\n");
	}
	init_axe(25, TWO_HANDED);
	setup();
}
