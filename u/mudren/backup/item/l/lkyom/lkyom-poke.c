// ITEM Made by player(������:lkyom) /data/item/l/lkyom-poke.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue May  8 01:49:24 2001
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("����[2;37;0m", ({ "poke" }));
	set_weight(15000);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;35m����[2;37;0m���ƶ��ɵ�һ������
�����Ͽ���һ��С�֣�������(lkyom)
");
	set("value", 2100000);
	set("point", 118);
	set("materail", "magic stone");
	set("wield_msg", "[1;36m$N[1;36mһ����Х������һ��[1;36m$n[1;36m��[2;37;0m\n");
	set("unwield_msg", "$N����һĨ��������$n��\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
