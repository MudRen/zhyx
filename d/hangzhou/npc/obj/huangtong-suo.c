// fu

#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
	set_name(YEL"��ͭ��" NOR, ({ "huangtong suo", "suo" }));
       	set("long", "����ͬ������Ԣ����ס���˵��ġ�\n");
	set("weight", 1000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 5000);
		set("material", "ͭ");
		set("armor_prop/armor", 2);
		}
	setup();
}	
