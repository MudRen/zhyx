#include <armor.h>
inherit CLOTH;
#include <ansi.h>
void create()
{
        set_name(HIR"�Ͼ�����"NOR, ({ "daopao" }) );
        set_weight(3000);
        if(clonep())
                set_default_object(__FILE__);
        else {          set("unit", "��");
                set("long", "һ����ߵ������\n");
                set("material", "cloth");
        }
        setup();
}

