#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "���ש" NOR, ({ "gold brick", "jinzhuan", "brick" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "����һ��ƲӲӵĽ�ש����ֵ"
                            "���Բ��ơ�\n"NOR);
                set("value", 3400000);
                set("unit", "��");
        }
}
