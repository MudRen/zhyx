//update by xiner

#include <ansi.h>
#include <armor.h>
inherit BOOTS;

void create()
{
	set_name(BLK"����"HIW"սѥ"NOR,({"xuanwu shoes","shoes","xie"}));
	set_weight(1200);
	if(clonep())
		set_default_object(__FILE__);
	else{
		set("long",GRN"����һ˫����������Ƭ��Ь�ӡ�"NOR"
��װЧ����"HIW"������װӵ����ǿ�ķ���������"NOR"\n");
		set("unit","˫");
		set("value",5000);		
		set("material","boots");
		set("armor_prop/armor", 50 + random(100));
		set("armor_prop/dodge", 30 + random(20));
		set("no_sell",1);
		set("no_steal",1);
		}
	setup();
}

int query_autoload()
{
	return 1;
}