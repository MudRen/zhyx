// qingtong-dun.c
// by dream

#include <armor.h>
#include <ansi.h>

 inherit DUNPAI;

void create()
{
        set_name(HIC "��֮ͭ��" NOR, ({ "qingtong dun", "dun" }));
        set("long", "����һ�洿��ͭ�ֹ�����ľ�����ͭ�ܡ�\n");
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "dunpai");
                set("unit", "��");
                set("armor_prop/armor", 30);
                set("value", 1000000);
        }
        setup();
}

