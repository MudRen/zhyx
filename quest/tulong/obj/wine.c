// wlywine.c

#include <ansi.h>

inherit ITEM;
inherit F_LIQUID;

void create()
{
        string *order = ({HIW "����Һ" NOR,HIM "���ϴ�" NOR, HIY "ȫ�˴���" NOR, HIR "�ľ�" NOR, HIG "�ž�����" NOR});
        set_name( (order[random(5)]), ({ "wine" }) );
        set_weight(10);
        if( clonep() )
             set_default_object(__FILE__);
        else {
        set("long", "һƿ���ơ�\n");
                set("unit", "ƿ");
                set("value", 0);
                set("max_liquid", 20);
        }
        // The liquid contained in the container is independent, we set a copy
        // in each cloned copy.
        set("liquid", ([
                "type": "alcohol",
                "name": "��",
                "remaining": 20,
                "drunk_apply": 5,
        ]) );
}

