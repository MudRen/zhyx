// ITEM Made by player(Ӱ��:shadow) /data/item/s/shadow-handz.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu May 10 08:53:44 2001
#include <ansi.h>
#include <armor.h>

inherit HANDS;

void create()
{
	set_name("������[2;37;0m", ({ "handz" }));
	set_weight(20000);
	set("item_make", 1);
	set("unit", "˫");
	set("long", "������[1;35m����[2;37;0m���ƶ��ɵ�һ˫���ơ�
����һ�����ʵ������λ��ߣ����Ա������ơ�[2;37;0m
����Ե�Ͽ���һ��С�֣�Ӱ��(shadow)
");
	set("value", 2100000);
	set("point", 123);
	set("materail", "magic stone");
	set("wear_msg", "[33m$N����һ�������ơ�[2;37;0m\n");
	set("remove_msg", "[33m$Nж�����Ƶ�װ����[2;37;0m\n");
	set("armor_prop/strike", 10);
	set("armor_prop/hand", 10);
	set("armor_prop/armor", 10);

	setup();
}

