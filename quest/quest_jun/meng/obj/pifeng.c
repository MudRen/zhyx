#include <ansi.h>
#include <armor.h>
inherit CLOTH;
void create()
{
        set_name(HIB"��ɫ����"NOR, ({ "pi feng","cloth" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "cloth");
                set("value", 1000000);
                set("armor_prop/armor", 20);
                set("no_steal",1);
                set("no_get",1);
                set("no_put",1);
        }
        setup();
}

void owner_is_killed() { destruct(this_object()); }  

