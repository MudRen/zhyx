#include <ansi.h>
#include <armor.h>
inherit CLOTH;
void create()
{
        set_name(CYN"������"NOR, ({ "ironrobe" }) );
        set_weight(300000);
        if( clonep() )
                set_default_object(__FILE__);
        else {  
                set("long","һ����Ϊ���ص���������.\n"); 
                set("unit", "��");
                set("material", "steel");
                set("armor_prop/armor", 50);
                set("armor_prop/spells", 1);
        }
        setup();
}

