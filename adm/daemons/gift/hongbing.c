// hongbing.c ���ݺ��
// By Alf, Last Update 2001.10

#include <ansi.h>
inherit ITEM;

void init();
inherit F_FOOD;

void create()
{
    set_name(HIW"���"NOR,({"hong bing", "bing" }));
    set_weight(50);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "���������һ�����������������ƴ��࣬���������������ִࡣ\n");
        set("unit", "��");
        set("value", 50);
        set("food_remaining", 8);
        set("food_supply", 40);
    }
}


