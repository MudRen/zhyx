// ת������֮ ���Ȧ
// Create by Yuchang

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "���Ȧ" NOR, ({ "jingang quan", "jingang", "quan" }) );
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", HIM "����һ��ӵ�����ǻ���֮���ı����ʱ�ش���Ͷ���\n"
                                "����Ĺ�â��\n" NOR);
                set("value", 10000);
                set("no_sell", 1);
        }
        setup();
}

