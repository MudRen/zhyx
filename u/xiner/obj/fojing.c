// fojing.c

inherit ITEM;
#include <ansi.h>

string* titles = ({
	"����ؾ���",
	"�����վ���",
});

string* skills = ({
	"buddhism",
        "lamaism",
});

void create()
{
	int i = random(sizeof(titles));
	set_name(HIW + titles[i] + NOR, ({ "fo jing", "book" }));
	set_weight(200);
	set("unit", "��");
	set("long", "����һ����������д�ķ𾭡�\n");
	set("value", 0);
	set("no_sell", "�⡭��ֵʲôǮ��\n");
	set("material", "paper");
	set("skill", ([
		"name":	skills[i],
		"exp_required":	1000000,
		"jing_cost":	100 + random(50),
		"difficulty":	150 + random(100),
		"max_skill":	349,
		"min_skill":	249,
        	"need" : ([ "sanscrit" : 300,
                	"literate" : 300 ]),
		]) );
}
