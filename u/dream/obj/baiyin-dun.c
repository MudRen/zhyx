// baiyin-dun.c
// by dream

#include <armor.h>
#include <ansi.h>

inherit DUNPAI;

void create()
{
        set_name(HIW "����֮��" NOR, ({ "baiyin dun", "dun" }));
        set("long", "����һ�洿�����ֹ�����ľ��°����ܡ�\n");
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "dunpai");
                set("unit", "��");
                set("armor_prop/armor", 60);
                set("value", 1500000);
        }
        setup();
}

