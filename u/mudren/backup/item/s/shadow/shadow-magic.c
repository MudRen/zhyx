// ITEM Made by player(Ӱ��:shadow) /data/item/s/shadow-magic.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Jul 23 20:49:56 2001
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit "/feature/mingren_itemmake.c";

void create()
{
	set_name("[1;32m������¶[2;37;0m", ({ "magic" }));
	set_weight(1400);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;37m����˿[2;37;0m���ƶ��ɵ�һ�żס�
[1;32m���Ǹ�������֥�ϵ�һ�ξ�Ө��͸����¶����˵����
��ɽ��ǧ��������֥Ϊĸ�����ϵ���ȡ���վ��»���
�������ޱ�����Ĺ�Ч��[2;37;0m
��Ե�Ͽ���һ��С�֣�Ӱ��(shadow)
");
	set("value", 2100000);
	set("point", 173);
	set("materail", "silk");
	set("wear_msg", "$N�ó�һ��$n���������С�[2;37;0m\n");
	set("remove_msg", "$N���$n�ջذ��ҡ�[2;37;0m\n");
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
