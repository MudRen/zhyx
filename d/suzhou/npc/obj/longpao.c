// longpao.c

#include <ansi.h>
#include <armor.h>
inherit CLOTH;

void create()
{
	set_name(HIR"���"NOR HIY"���"NOR HIR"������"NOR, ({ "longpao" }));
	set("long", "����һ��ո�´���߹����ۣ������ɵ�ר�������\n");
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("material", "cloth");
		set("unit", "��");
    set("armor_prop/armor", 100);
    set("male_only", 1);
	}
	setup();
}

