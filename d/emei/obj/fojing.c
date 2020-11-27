// fojing.c
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIY "������;�" NOR, ({ "niepan jing", "jing" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��𾭡�\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":	"mahayana",	// name of the skill
			"exp_required":	600000,	// minimum combat experience required
			"jing_cost":	10,	// jing cost every time study this
			"difficulty":	10,	// the base int to learn this skill
			"max_skill":	500,	// the maximum level you can learn
			"min_skill": 100   // the min level you can learn
 		]) );
	}
}
