// hua4.c

inherit ITEM;
inherit F_FOOD; 

#include <ansi.h>

void create()
{
	set_name(HIC "�����" NOR, ({"feicui lan", "feicui", "lan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
        	set("unit", "��");
		set("long", "����һ��ǧ���ѵ�һ�������������˵�ܽ�ٶ���\n");
        	set("value", 1000000);
                set("food_remaining", 20); 
                set("food_supply", 500); 
	}
        setup();
}