// yunxiu.c

#include <ansi.h>
#include <armor.h>
inherit CLOTH;

void create()
{
	set_name(CYN"���"NOR HIR"����"NOR HIM"ˮ����"NOR, ({ "yunxiu" }));
	set("long", "����һ��ո�µ��������ʱ���������\n");
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("material", "cloth");
		set("unit", "��");
set("armor_prop/armor", 100);
    set("female_only", 1);
	}
	setup();
}

