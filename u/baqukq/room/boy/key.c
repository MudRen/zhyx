// File(/data/room/boy/key.c) of boy's key
// Create by LUBAN written by Doing Lu

#include <ansi.h>

inherit ITEM;

string query_autoload() { return "1"; }

void create()
{
	set_name(YEL "�������߼ҵ�Կ��" NOR, ({ "key", "1 of boy" }));
	set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", @LONG
һ������������Ȼ��(you)��Կ�ס�
����ԭ��Կ�ס�
LONG );
		set("unit", "��");
		set("no_pawn", 1);
                set("no_sell", 1);
		set("item_make", 1);
		set("value", 1);
	}
}
