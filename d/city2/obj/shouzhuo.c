// shuozhuo.c ����

#include <armor.h>
#include <ansi.h>

inherit WRISTS;
inherit F_NOCLONE;

void create()
{
	set_name(HIG "����" NOR, ({ "shou zhuo", "zhuo" }));
       	set("long", "����һ������Ө�����󣬹����覣�����ϡ�����С�\n");
	set_weight(300);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 50000);
		set("material", "��");
		set("armor_prop/armor", 2);
		set("female_only", 1);
	}
	setup();
        set("startroom", "/d/city2/aobai9");
        check_clone();
}	
