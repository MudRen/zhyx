#include <ansi.h>
inherit ITEM;
void create()
{
    set_name( HIR "���" NOR, ({ "hongbao" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "��");
            set("material", "cloth");
            set("long", "һ��СС�ĺ�����������ţ������ĳ�����\n");
          }
    setup();
}

