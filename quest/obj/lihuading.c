#include <ansi.h> 
#include <combat.h>
inherit ITEM;
void create()
{
        set_name( HIW "��ľ����" NOR, ({ "shenmu-wangding"}) );
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
            set("unit", "��");
            set("long","����һ���ߴ糤��������ľ��������������Ӷ���\n");
            set("material", "silver");
        }
        setup();
}

