#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY "��ӥ����ͼ" NOR, ({ "cangying hua", "cangying", "hua"}) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "���ǳ½���ƽ����ϲ���Ĳ�ӥ����ͼ��\n" );
                set("value", 1);
        }
}

int is_container() { return 1; }


