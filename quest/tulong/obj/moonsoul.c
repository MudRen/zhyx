//zhenzhu.c
inherit ITEM;
#include <ansi.h>
void create()
{
        set_name( HIC"����"NOR, ({ "moonsoul"}));
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long","����һ��ҹ���飬������������͵Ĺ⣬�������¹�����ֵ���ǡ�\n");
                set("value", 70000);
                set("material", "iron");
              }
}

