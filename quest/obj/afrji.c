#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(YEL "�����ռ�" NOR, ({ "afrji" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "��");
            set("material", "paper");
            set("long", "һ������ɩ�Ķ��Ӱ�����ǰ���ռǣ�\n");
          }

    setup();
}

