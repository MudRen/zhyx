// jinshou.c

#include <armor.h>
#include <ansi.h>

inherit HANDS;

void create()
{
	set_name( HIY "�ƽ�����" NOR, ({ "gold hand", "hand" }) );
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "steel");
		set("unit", "��");
		set("long", "����һ��ƽ��Ƴɵ����ף����Լ�ǿ�ַ����Ʒ����˺�����\n");
		set("value", 200000);
              set("armor_prop/hand", 80);              
              set("armor_prop/unarmed_damage", 80); 
              set("armor_prop/strike", 80); 	
            }
	setup();
}
void owner_is_killed()
{
        destruct(this_object());
} 
int query_autoload() { return 1; }


