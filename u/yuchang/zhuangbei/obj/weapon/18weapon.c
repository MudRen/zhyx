//create by huarong 2004/2
//���ܱ���  �μ�perform.c  huarong 2004/2
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name("ʮ��������", ({"eighteen weapon", "eighteen", "weapon"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 100);
                set("unbreak", 1);
                set("material", "wood");
                set("long", "����ʮ��������������ʱ�õġ�\n");
                set("wield_msg", "$N���һ��$n�������С�\n");
                set("unequip_msg", "$N�����е�$n��������\n");
        }
        init_sword(30);
        setup();
}

