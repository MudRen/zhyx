// ITEM Made by player(Ӱ��:shadow) /data/item/s/shadow-puti.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu May 17 02:18:55 2001
#include <ansi.h>
#include <weapon.h>

inherit DAGGER;
inherit F_MINGREN_ITEMMAKE;

void create()
{
	set_name("[1;32m������[2;37;0m", ({ "puti" }));
	set_weight(15000);
	set("item_make", 1);
	set("unit", "֧");
	set("long", "������[1;35m����[2;37;0m���ƶ��ɵ�һ֧�̱���
[1;32m����һ�ž�Ө����������ӣ�������ɽ������ǰ����ϡ�ޱȣ�
������������֮ʵ�����ܻ��ٽ٣���ǧ�֣������ͬ�١�[2;37;0m
�̱����Ͽ���һ��С�֣�Ӱ��(shadow)
");
	set("value", 2100000);
	set("point", 136);
	set("materail", "magic stone");
	set("wield_msg", "$N�ó�һ��[1;32m������[2;37;0m���������С�[2;37;0m\n");
	set("unwield_msg", "$N��[1;32m������[2;37;0m�ջذ��ҡ�[2;37;0m\n");
	restore();
	init_dagger(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
