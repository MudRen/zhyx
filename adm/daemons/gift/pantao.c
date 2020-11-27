// pantao.c ���
// By Alf, Last Update 2001.11

#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
    set_name(HIW"���"NOR, ({"pan tao", "pantao"}));
    set_weight(40);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "���ǲ�������ɽ�е���ң�ʳ֮��˵���������١�\n");
        set("unit", "ֻ");
        set("value", 80);
        set("food_remaining", 10);
        set("food_supply", 30);
    }
}

void init()
{
    add_action("do_eat", "eat");
}

int do_eat(string arg)
{
    if (!id(arg))
        return notify_fail("��Ҫ��ʲô��\n");
    if(arg=="pan tao" || "pantao") 
    {
        this_player()->set_temp("nopoison", 1);
        tell_object(this_player(),
        HIG"�����һֻ��ң�ֻ��һ�����������ķΣ���ʱ��̨һƬ������������ˬ��\n"NOR);
        destruct(this_object());
    }
    return 1;
}


