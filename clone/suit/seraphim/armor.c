//update by xiner
#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
	set_name( HIR"����֮��"NOR, ({ "seraphim armor","armor","jia" }) );
	set_weight(1500);
	if( clonep() )
	set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", HIB"����֮Ϊ��Ҳ�����������Ҳ��Ȼ����������۾��ߣ�����Ӥ֮�����ɱ�ˡ�"NOR"
��װЧ����"HIW"��ʱ���������˺����ٵ㡣"NOR"\n");
		set("value", 150000);
		set("material", "feather");
		set("armor_prop/armor", 100 + random(100));
		set("armor_prop/dodge", 20 + random(50));
                set("armor_prop/parry", 20 + random(50));
		set("warm_cloth", 1);
		set("no_sell", 1 );
		set("no_steal", 1 );
	}
	setup();
}

int query_autoload()
{
	return 1;
}