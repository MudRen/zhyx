#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(HIW "ˮ�����" NOR, ({ "jie zhi" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("long", "����һöˮ����䣮\n");
          }

    setup();
}


