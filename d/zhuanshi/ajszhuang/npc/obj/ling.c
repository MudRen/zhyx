// tu.c BY YUCHANG

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIB"����"NOR, ({"ling pai", "lingpai"}) );
        set_weight(10);
        set("no_steal", 1);
        set("no_beg", 1);
        set("no_sell", 1);
        set("value",1);
        set("long",@LONG
�����Ͽ��š����������ĸ����֣����������»Ჽ�������У�
������ȥ���ԭ��?
LONG );
        if( clonep() )
               set_default_object(__FILE__);
        else
       {
                set("unit", "��");
                set("material", "unknow");
        }
}

int query_autoload() { return 1; }

