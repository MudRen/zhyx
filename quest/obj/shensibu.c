#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(HIB "̫��ȭ��" NOR, ({ "taiji-quanjing" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "��");
            set("material", "cloth");
            set("long", "һ�������˸������Ƶ������伮��\n");
          }

    setup();
}

