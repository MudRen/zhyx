#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIB "�ϹŻ���" NOR, ({"hu po", "hu", "po"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIB "\nһ����ɫ�Ļ��ǣ���Ͼ�ı������ǳ���õĹ�\n"
                            "�����з·��̲��������ħ��������Ǵ�˵\n"
                            "�е�����������֮�׵ġ����ϹŻ��ǣ��ഫΪ\n"
                            "�Ϲ�ʱ������������������ƶ��ɡ�\n" NOR);
                set("unit", "��");
                set("value", 10000000);
                set("item_origin", 1);
                set("material_attrib", "hu po");
                set("material_name", HIB "�ϹŻ���" NOR);
                set("can_make", "all");
                set("power_point", 180);
        }
}
