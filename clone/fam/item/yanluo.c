#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + HIR "���޳�" NOR, ({ "yanluo chou", "yanluo", "chou" }));
        set_weight(1200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "��˸�������Ϲ�ĳ�У���������������\n"
				                 "���Դ���ޡ������˺���75~85��\n"NOR);
                set("unit", "��");
                set("value", 30000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + HIR "���޳�" NOR);
                set("can_make", ({ "��" }));
                set("power_point", 75);
        }
}

int query_autoload()
{
        return 1;
}

