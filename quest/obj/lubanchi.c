#include <weapon.h>
#include <ansi.h>
inherit SWORD;
void create()
{
        set_name(HIW"���齣"NOR, ({ "chongling-sword" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "iron");
                set("long", "����һ��������\n");
        }
        init_sword(5);
        setup();
}

