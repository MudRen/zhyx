#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "��ɫ���" NOR, ({"qise yinluo", "qise", "yinluo"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "\nһ�鴿��ɫ��ˮ������Ө��͸����Ͼ�ı�����\n"
                            "��ҫ�۵Ĺ������з·��̲���ǧǧ�������\n"
                            "��������������Ϣ��ɢ������������������\n"
                            "�Ǵ�˵�е�����������ɫ����ഫֻ���ڵ�\n"
                            "���вŻ���֡�\n" NOR);
                set("unit", "��");
                set("value", 10000000);
                set("item_origin", 1);
                set("material_attrib", "yin luo");
                set("material_name", HIW "��ɫ���" NOR);
                set("can_make", "all");
                set("power_point", 200);
        }
}
