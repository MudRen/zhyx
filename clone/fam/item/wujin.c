#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + YEL "�ڽ��" NOR, ({"wujin kuang", "wujin", "kuang"}));
        set_weight(1800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "����һ�鼫Ϊ�������ڽ��ʯ����������������ޱȡ�\n"
				                 "���Դ��쵶�����̱��������˺���75~85\n" NOR);
                set("unit", "��");
                set("value", 8000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + YEL "�ڽ��" NOR);
                set("can_make", ({ "��", "��", "�̱�"}));
                set("power_point", 75);
        }
}

int query_autoload()
{
        return 1;
}

