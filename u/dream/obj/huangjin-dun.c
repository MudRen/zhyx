// huangjin-dun.c
// by dream

#include <armor.h>
#include <ansi.h>

inherit DUNPAI;

void create()
{
        set_name(HIY "�ƽ�֮��" NOR, ({ "huangjin dun", "dun" }));
        set("long", "����һ�洿�ƽ��ֹ�����ľ��»ƽ�ܡ�\n");
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "dunpai");
                set("unit", "��");
                set("armor_prop/armor", 90);
                set("value", 2000000);
        }
        setup();
}

