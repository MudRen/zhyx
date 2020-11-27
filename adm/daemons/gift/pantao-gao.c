// pantao-gao.c ��Ҹ�
// By Alf, Last Update 2001.11

#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
    set_name(HIW"��Ҹ�"NOR, ({"pantao gao", "pantaogao"}));
    set_weight(40);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "����������ɽ���ز�������Ƴɵĸ�㣬�����������˱ǡ�\n");
        set("unit", "��");
        set("value", 80);
    }
}

void init()
{
    add_action("do_eat", "eat");
}

int do_eat(string arg)
{
    object me = this_player();
    if (!id(arg))
        return notify_fail("��Ҫ��ʲô��\n");
    if(arg=="pantao gao" || "pantaogao") 
    {
        me->set("food",(int)me->max_food_capacity());
        me->set("water",(int)me->max_water_capacity());
        message_vision(HIW"$N����һ����Ҹ⣬ֻ���ÿڳ����㣬���ٸе����ʡ�\n"NOR,me);
        destruct(this_object());
    }
    return 1;
}


