// ת������֮ Ů�ʯ 
// Create by yuchang

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "Ů�ʯ" NOR, ({ "nvwa shi", "nvwa", "shi" }) );
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", YEL "����һ�鷺���߲ʹ�â��ʯͷ����˵��ʯ��Ů洵�"
                                "�������\n" NOR);
                set("value", 10000);
                set("no_sell", 1);
        }
        setup();
}
int query_autoload()
{
       return 1;
}

