#include <weapon.h>
inherit AXE;

void create()
{
        set_name("�師", ({ "axe", "banfu", "fu" }));
        set_weight(7000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�����صİ師���������߷�ʹ��˳�֡�\n");
                set("value", 300);
                set("material", "steel");
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n������䡣\n");
        }
        init_axe(50);
        setup();
}
