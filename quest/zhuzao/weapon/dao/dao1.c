// gangdao.c

#include <weapon.h>
#include <ansi.h>
inherit BLADE;

void create()
{
        set_name(HIC"���ֵ�"NOR, ({ "gang dao","dao"}) );   
        set_weight(7000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�����λεĸֵ���������������������Ƿ�����\n"); 
                set("value", 10000);
                set("material", "steel");
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ص��ʡ�\n");
        }
        init_blade(100);
        setup();
}

