//by xiner

#include <weapon.h>
#include <ansi.h>

inherit THROWING;
 
void create()
{
	set_name(HIR "��������" NOR, ({ "qi jing" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIW "������˸�����Ĺ�â����ɵ�һ��" HIR "��������" HIW "��\n" NOR);
		set("unit", "��");
		set("value", 0);
		set("base_unit", "��");
		set("base_weight", 1);
		set("base_value", 0);
		set("no_get", 1);
		set("no_put", 1); 
		set("no_steal", 1);
		set("no_drop", "�ⶫ�������뿪������ģ�\n"); 
	}
	set_amount(50);
	init_throwing(200);
	setup();
}
