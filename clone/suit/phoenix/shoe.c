
// ����װ��
// update by kasumi
#include <ansi.h>
#include <armor.h>
inherit BOOTS;

void create()
{
        set_name(HIG"��ȸ֮צ"NOR, ({ "phoenix shoes","shoes", "xie" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
		  set("long", GRN"����һ˫����������Ƭ��Ь�ӡ�"NOR"
����ָ����20~40
����Ч���������Ч�Ṧ60~80����
����װ����"HIR"[��ȸ֮��]"NOR" "RED"��ȸ֮��"NOR" "YEL"��ȸ֮��"NOR" "GRN"��ȸ֮צ"NOR" "HIC"��ȸ֮��"NOR"
��װЧ����"HIG"��ʱ���Ӷ��ټ��������ԡ�"NOR"\n");

                set("unit", "˫");
                set("value",5000);		
                set("material", "boots");                
                set("armor_prop/armor",20+random(20));
                set("armor_prop/dodge", 60+random(20));
                set("no_sell", 1 );
                set("no_steal", 1 ); 

        }
        setup();
}
int query_autoload()
{
        return 1;
}