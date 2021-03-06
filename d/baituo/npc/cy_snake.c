// Code of JHSH
// cy_snake.c 赤炎(考据：本草纲目)
// by maco

#include <ansi.h>

inherit NPC;

int auto_perform_duwu();

void create()
{
	int poison = 10;
        set_name(HIR"赤炎"NOR, ({ "chi yan", "she", "snake" }) );
	set("long", "这是一条遍体通红的毒蛇，长仅数寸，细小如指。\n宋朝时於陕西请泉初次发现，剧毒无比，听说若是被其咬到，七步必亡。\n");
	set("race", "蛇类");
	set("age", 100);
	set("attitude", "aggressive");

	set_weight(8000);

	set("str", 30 + poison );
	set("con", 30 + poison );
	set("int", 20);
	set("dex", 30 + poison );

	set("max_jing", 10000);
	set("max_qi", 12000);
	set("qi", 12000);
	set("max_jingli", 10000);

	set("combat_exp", 2000000);

	set_temp("apply/attack", 500);
	set_temp("apply/damage", 300);
	set_temp("apply/dodge", 400);
	set_temp("apply/armor", 200);

	set("chat_chance_combat", 40);
	set("chat_msg_combat", ({
		(: auto_perform_duwu :),
	}));

	set("snake_poison", 60 + poison*40 +random(61));
	set("bt_snake", 1);

	setup();
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
       int poison;
       poison = me->query("snake_poison");

	if( poison > 0 && !victim->query("snake_poison")) 
             victim->affect_by("snake_poison",
                              ([ "level" : poison/5 + random(poison/5),
                                 "id"    : me->query("id"),
                                 "duration" :  poison/20 ]));
       return HIR "只听$n痛呼了一声，给赤炎狠狠的咬了一口！\n" NOR;
}

#include "snake_perform.h"
