#include <weapon.h>
#include <ansi.h>

inherit THROWING;
 
void create()
{
	set_name(HIR "����" NOR, ({ "qi jing", "qi", "jing" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIW "������˸�����Ĺ�â����ɵ�һ��" HIR "��������" HIW "��\n" NOR);
		set("unit", "��");
		set("value", 0);
		set("base_unit", "��");
		set("base_weight", 1);
		set("base_value", 0);
	}
	set_amount(1);
	init_throwing(200);
	setup();
}
