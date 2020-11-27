//update by xiner

#include <ansi.h>
#include <armor.h>

inherit SURCOAT;

void create()
{
	set_name(HIW"白虎披风"NOR,({"tiger coat","coat"}));
	set_weight(1500);
	if(clonep())
		set_default_object(__FILE__);
	else{
		set("unit","件");
		set("long",HIW"这是一件白虎的皮毛织成的披风。"NOR"
套装效果："HIW"临时增加空手伤害二百点。"NOR"\n");
		set("value",200000);
		set("material","feather");
		set("armor_prop/armor", 30 + random(20));
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