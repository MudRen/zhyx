//update by xiner
#include <ansi.h> 
#include <armor.h> 
 
inherit HEAD; 
 
void create() 
{ 
        set_name( HIR"���֮��"NOR , ({ "seraphim horn","horn","jiao" }) ); 
        set_weight(1000);
        if( clonep() ) 
                set_default_object(__FILE__); 
        else { 
                set("unit", "��"); 
                set("long", HIW"���һ�䲨��ϴ��ǧ�򴺡�"NOR"
��װЧ����"HIW"��ʱ���������˺����ٵ㡣"NOR"\n");
		set("value", 150000); 
		set("material", "head"); 
		set("armor_prop/force", 40+random(60));
		set("armor_prop/armor", 40+random(60));  
		set("no_sell", 1 );
		set("no_steal", 1 );              
        } 
        setup(); 
} 
int query_autoload()
{
        return 1;
}