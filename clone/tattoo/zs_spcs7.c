#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + MAG "��ͼ��Ƭ" NOR, ({ "xian tu7", "xiantu7", "tu7" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "����һ�ű����˿����ͼ��Ƭ��������в�ȱ��ȫ"
                            "�Ĺ�ʿ��˫������\n" NOR);
                set("unit", "��");
                set("value", 10);
                set("material", "paper");
        }
}

int query_autoload()
{
        return 1;
}

