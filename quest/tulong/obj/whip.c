// Jay May 27, 96

#include <weapon.h>
inherit WHIP;

void create()
{
        set_name("���", ({ "whip" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ����ɫ�ĳ�������赸ʱ�ĵ��ߡ�\n");
                set("value", 300);
                set("material", "cloth");
                set("wield_msg", "$NǳЦ��Ȼ������������һ��$n��\n");
                set("unwield_msg", "$N�����е�$n�������䡣\n");
        }
        init_whip(40);
        setup();
}

