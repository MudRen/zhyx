//update by xiner

#include <ansi.h>
#include <armor.h>

inherit SURCOAT;

void create()
{
	set_name(BLK"����"HIW"����"NOR,({"xuanwu coat","coat"}));
	set_weight(1500);
	if(clonep())
		set_default_object(__FILE__);
	else{
		set("unit","��");
		set("long",HIW"����һ����������ͼ�ڵ����硣"NOR"
��װЧ����"HIW"������װӵ����ǿ�ķ���������"NOR"\n");
		set("value",200000);
		set("material","feather");
		set("armor_prop/armor", 50 + random(100));
		set("armor_prop/parry", 20 + random(20));
		set("armor_prop/dodge", 20 + random(20));
		set("no_sell",1);
		set("no_steal",1);
	}
	setup();
}

int query_autoload()
{
	return 1;
}