#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
        set_name(HIR "��ȸ��ë" NOR, ({ "zhuque yumao", "zhuque", "yumao" }));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {               
		    set("long", HIR "һ����ȸ���ϵ���ë���ʻ��ɫ��\n" NOR);
            set("unit", "��");
            set("value", 100000);

        }
        setup();
}

int query_autoload()
{
        return 1;
}
