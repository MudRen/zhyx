#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "�ŵ�����" NOR, ({"xuan yu", "xuan", "yu"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "\nһ����ɫ�ľŵ�����ӵ����ҽ�ز������ܶ�\n"
                            "ɱ����һ������������ŵ������ഫ��ũ��\n"
                            "������ũ�߾�������ö�ŵ����������ɡ�\n" NOR);
                set("unit", "��");
                set("value", 10000000);
                set("item_origin", 1);
                set("material_attrib", "xuan yu");
                set("material_name", HIG "�ŵ�����" NOR);
                set("can_make", "all");
                set("power_point", 160);
        }
}
