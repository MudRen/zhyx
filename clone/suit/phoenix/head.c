// ����װ��
// update by kasumi
#include <ansi.h> 
#include <armor.h> 
 
inherit HEAD; 
 
void create() 
{ 
        set_name( YEL"��ȸ֮��"NOR , ({ "phoenix eye","eye" }) ); 
        set_weight(800); 
        if( clonep() ) 
                set_default_object(__FILE__); 
        else { 
                set("unit", "��"); 
                set("long", YEL"����һ����״�����ͷ����"NOR"
����ָ����40~70
����Ч���������Ч�ڹ�50~100����
����װ����"HIR"[��ȸ֮��]"NOR" "RED"��ȸ֮��"NOR" "YEL"��ȸ֮��"NOR" "GRN"��ȸ֮צ"NOR" "HIC"��ȸ֮��"NOR"
��װЧ����"HIG"��ʱ���Ӷ��ټ��������ԡ�"NOR"\n");
                set("value", 150000); 
                set("material", "head"); 
                set("armor_prop/force", 50+random(50));
		            set("armor_prop/armor", 40+random(30));  
		            set("no_sell", 1 );
                set("no_steal", 1 );              
        } 
        setup(); 
} 
int query_autoload()
{
        return 1;
}