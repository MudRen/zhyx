#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIG"�꺮����"NOR, ({"dish"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ʼ�����÷���������ɣ�һ������Ĳõ�С�ˡ�\n");
                set("unit", "��");
                set("value", 120);
                set("food_remaining", 10);
                set("food_supply", 30);
        }
}

