// fu

#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
	set_name(HIR"ͬ�Ľ�" NOR, ({ "tongxin jie", "jie" }));
       	set("long", "һ���ʺ�ɫ���й��ᣬ����������������ͬ�ġ�\n");
	set("weight", 100);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 5000);
		set("material", "˿");
		set("armor_prop/armor", 2);
		}
	setup();
}	
