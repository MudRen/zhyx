//update by xiner

#include <ansi.h>
#include <armor.h>
inherit BOOTS;

void create()
{
	set_name(HIW"�׻�սѥ"NOR,({"tiger shoes","shoes","xie"}));
	set_weight(1200);
	if(clonep())
		set_default_object(__FILE__);
	else{
		set("long",GRN"����һ˫����������Ƭ��Ь�ӡ�"NOR"
��װЧ����"HIW"��ʱ���ӿ����˺����ٵ㡣"NOR"\n");
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

intquery_autoload()
{
	return 1;
}