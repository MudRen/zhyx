#include <ansi.h>

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIC"��𳤽�"NOR, ({ "long sword", "sword"}));   
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ���������ĳ������쳣������\n");
                set("value", 8000);
                set("material", "steel");
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ؽ��ʡ�\n");
        }
        init_sword(50);
        setup();
}

