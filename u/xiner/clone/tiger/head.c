//update by xiner
#include <ansi.h> 
#include <armor.h> 
 
inherit HEAD; 
 
void create() 
{ 
        set_name( HIW"�׻�ս��"NOR , ({ "tiger helmet","helmet","kui" }) ); 
        set_weight(1000);
        if( clonep() ) 
                set_default_object(__FILE__); 
        else { 
                set("unit", "��"); 
                set("long", HIW"����һ����״�����ͷ����"NOR"
��װЧ����"HIW"��ʱ���ӿ����˺����ٵ㡣"NOR"\n");
		set("value", 150000); 
		set("material", "head"); 
		set("armor_prop/force", 50+random(50));
		set("armor_prop/armor", 50+random(50));  
		set("no_sell", 1 );
		set("no_steal", 1 );              
        } 
        setup(); 
} 
int query_autoload()
{
        return 1;
}