//update by xiner

#include <ansi.h>
#include <armor.h>
inherit BOOTS;

void create()
{
	set_name(HIR"����֮��"NOR,({"seraphim foots","foots","zu"}));
	set_weight(1200);
	if(clonep())
		set_default_object(__FILE__);
	else{
		set("long",HIW"��ɽ��������Ķ���������״��ţ��������޽ǣ�һ�㣬����ˮ����з��꣬��������£��������ף�����Ի�硣��"NOR"
��װЧ����"HIW"��ʱ���������˺����ٵ㡣"NOR"\n");
		set("unit","˫");
		set("value",5000);		
		set("material","boots");
		set("armor_prop/armor",30+random(20));
		set("armor_prop/dodge",50+random(20));
		set("no_sell",1);
		set("no_steal",1);
		}
	setup();
}

int query_autoload()
{
	return 1;
}