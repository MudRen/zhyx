#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(HIG"�����澭"NOR, ({ "jiuyin-zhenjing" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "��");
            set("material", "stone");
            set("long", "һ����Ƥ΢΢���Ƶ��鼮��\n");
          }

    setup();
}

