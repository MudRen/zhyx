#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIC "�����ɻ�" NOR, ({"shi hun", "shi", "hun"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "\nһ����ɫ�ĵ����ɻ꣬ӵ�м������򶾼�а��\n"
                            "��һ����������������ɻ꣬�ഫΪа��֮��\n"
                            "��ɲ������֮�ף�������걻Ů����������\n"
                            "���ǣ��Ե��Ķ��������ɡ�\n" NOR);
                set("unit", "��");
                set("value", 10000000);
                set("item_origin", 1);
                set("material_attrib", "shi hun");
                set("material_name", HIC "�����ɻ�" NOR);
                set("can_make", "all");
                set("power_point", 160);
        }
}
