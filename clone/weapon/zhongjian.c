// heavysword.c �ؽ�

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("������", ({ "heavy sword", "sword", "jian" }));
        set_weight(30000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ������������ؽ�������ʮ�ֳ��ء�\n");
                set("value", 200);
                set("material", "xuantie");
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ؽ��ʡ�\n");
        }
        init_sword(80);
        setup();
}
