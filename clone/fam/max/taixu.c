#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "�Ϲ�̫��" NOR, ({"tai xu", "tai", "xu"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "\nһ����ɫ��̫�飬ӵ������仯��ħ������\n"
                            "���Ǵ�˵�е����������Ϲ�̫�飬�ഫΪ�Ϲ�\n"
                            "ʱ�����Ƶ۵þ�����Ů�����ϱ��������ƶ��ɡ�\n" NOR);
                set("unit", "��");
                set("value", 10000000);
                set("item_origin", 1);
                set("material_attrib", "tai xu");
                set("material_name", HIY "�Ϲ�̫��" NOR);
                set("can_make", "all");
                set("power_point", 180);
        }
}
