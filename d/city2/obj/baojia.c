
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_NOCLONE;

void create()
{
        set_name(HIY "��˿����" NOR, ({ "bao jia", "jia" }) );
        set_weight(5000);
        set("unit", "��");
        set("value", 50000);
        set("no_sell", 1);
        set("material", "gold");
        set("armor_prop/armor", 200);
        setup();
        set("startroom", "/d/city2/aobai9");
        check_clone();
}
