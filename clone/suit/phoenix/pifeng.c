// ����װ��
// update by kasumi                                                         

#include <ansi.h>
#include <armor.h>

inherit SURCOAT;

void create()
{
        set_name( HIC"��ȸ֮��"NOR, ({ "phoenix wing", "wing" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIC"����һ����ɫ֯�ɵ����磬���Ʈ��ʱ����һ���ſ��ĳ��"NOR"
����ָ����50~80
����Ч���������Ч�Ṧ40~60����
����װ����"HIR"[��ȸ֮��]"NOR" "RED"��ȸ֮��"NOR" "YEL"��ȸ֮��"NOR" "GRN"��ȸ֮צ"NOR" "HIC"��ȸ֮��"NOR"
��װЧ����"HIG"��ʱ���Ӷ��ټ��������ԡ�"NOR"\n");
                set("value", 200000); 
                set("material", "feather");
                set("armor_prop/armor", 50+random(30));
                set("armor_prop/dodge", 40+random(20));
                set("no_sell", 1 );
                set("no_steal", 1 );   
                
        }
        setup();
}
int query_autoload()
{
        return 1;
}