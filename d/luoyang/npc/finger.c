// zhitao.c ָ��

#include <armor.h>
#include <ansi.h>

inherit HANDS;

void create()
{
	set_name( HIY"�ƽ�ָ��"NOR, ({ "gold finger", "finger", "zhitao" }) );
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����������������Ļƽ�ָ�ף����Լ�ǿָ����צ�����˺�����\n");
		set("value", 200000);
		set("material", "steel");		
              set("armor_prop/finger", 80);              
              set("armor_prop/unarmed_damage", 80); 
              set("armor_prop/claw", 80); 
	}
	setup();
}
void owner_is_killed()
{
        destruct(this_object());
} 
int query_autoload() { return 1; }


