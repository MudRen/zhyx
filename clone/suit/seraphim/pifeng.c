//update by xiner

#include <ansi.h>
#include <armor.h>

inherit SURCOAT;

void create()
{
	set_name(HIR"应龙之翼"NOR,({"seraphim wing","wing"}));
	set_weight(1500);
	if(clonep())
		set_default_object(__FILE__);
	else{
		set("unit","件");
		set("long",HIW"《山海经·大荒东经》：“应龙处南极，杀蚩尤与夸父，不得复上。故下数旱，旱而为应龙之状，乃得大雨。”"NOR"
套装效果："HIW"临时增加武器伤害二百点。"NOR"\n");
		set("value",200000);
		set("material","feather");
		set("armor_prop/armor", 40 + random(10));
		set("armor_prop/dodge", 40 + random(10));
		set("no_sell",1);
		set("no_steal",1);
	}
	setup();
}

int query_autoload()
{
	return 1;
}