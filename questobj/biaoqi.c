#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(HIY"���㻨���ط�"NOR, ({ "hsmfang" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "��");
            set("material", "paper");
            set("long", "���㻨���ط���\n");
          }

    setup();
}
