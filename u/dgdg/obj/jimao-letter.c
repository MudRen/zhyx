#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "��ë��" NOR, ({ "jimao letter", "jimao", "letter"}) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ���ţ��ŵķ�ڴ�����һ����ë��\n" );
                set("value", 1);
        }
}

int is_container() { return 1; }


