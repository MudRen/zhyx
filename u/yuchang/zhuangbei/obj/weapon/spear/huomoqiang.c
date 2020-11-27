// huomoqiang.c

#include <weapon.h>
#include <ansi.h>
inherit F_UNIQUE;
inherit SPEAR;

void create()
{
        set_name(HIR "��ħǹ" NOR, ({ "huomoqiang", "spear" })
);
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ��" HIR "��ħǹ" NOR "�����ǻ�ħ��������\n");
                set("value", 10000);
                set("no_sell", 1);
                set("no_give", 1);
                set("no_drop", 1);
                set("no_put", 1);
                set("unbreak", 1);
                set("replace_file", "/d/obj/weapon/spear/gangqiang");
                set("material", "blacksteel");
                set("wield_msg","$N����ħǹ�������У���Χ���˶پ��������һ�֮�����\n");
		set("weapon_prop/courage", 8);
        }
        init_spear(80+random(30));
        setup();
}

