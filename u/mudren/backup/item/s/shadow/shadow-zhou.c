// ITEM Made by player(Ӱ��:shadow) /data/item/s/shadow-zhou.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu May  3 07:46:32 2001
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31m����[1;33m����[1;31m��[2;37;0m", ({ "zhou" }));
	set_weight(15000);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;35m����[2;37;0m���ƶ��ɵ�һ������
[1;33m��������[1;37mʹ�ù��������ڷ����[1;31m����[1;37m��[2;37;0m
�����Ͽ���һ��С�֣�Ӱ��(shadow)
");
	set("value", 2100000);
	set("point", 117);
	set("materail", "magic stone");
	set("wield_msg", "[1;31m����[1;33m����[1;31m��[1;37mƾ�ճ�����[1;36m$N[1;37m���У����ܿ�������쳣���ء�[2;37;0m\n");
	set("unwield_msg", "[1;37m����ͻȻ��ò���ôѹ�֣�ԭ��[1;31m����[1;33m����[1;31m��[1;37m��һ����ʧ��[1;36m$N[1;37m���С�[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
