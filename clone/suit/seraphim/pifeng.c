//update by xiner

#include <ansi.h>
#include <armor.h>

inherit SURCOAT;

void create()
{
	set_name(HIR"Ӧ��֮��"NOR,({"seraphim wing","wing"}));
	set_weight(1500);
	if(clonep())
		set_default_object(__FILE__);
	else{
		set("unit","��");
		set("long",HIW"��ɽ��������Ķ���������Ӧ�����ϼ���ɱ�����丸�����ø��ϡ���������������ΪӦ��֮״���˵ô��ꡣ��"NOR"
��װЧ����"HIW"��ʱ���������˺����ٵ㡣"NOR"\n");
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