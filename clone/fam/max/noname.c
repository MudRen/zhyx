#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "����֮��" NOR, ({"no name", "no", "name"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", sort_msg(HIM "�ǽ�����ʯ��ľ����֮�����ƽ��"
                                         "�����Ʋ�ƽ�����������֣�����������"
                                         "�ƺ������Ų�Ϊ��֪����������ȴ�о�"
                                         "����һ��������\n" NOR));
                set("unit", "��");
                set("value", 20000000);
                set("item_origin", 1);
                set("material_attrib", "no name");
                set("material_name", HIM "����֮��" NOR);
                set("can_make", "all");
                set("power_point", 300);
        }
}
