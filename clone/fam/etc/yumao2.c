#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
        set_name(HIR "�����ë" NOR, ({ "fenghuang feather", "feather", "fenghuang" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {               
		        set("long", HIR "һ��������ϵ���ë���ʻ��ɫ��\n" NOR);

                set("unit", "��");
                set("value", 10000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
