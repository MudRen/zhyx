// huangqi.c ����
// By Alf, Last Update 2001.11

#include <ansi.h>
inherit ITEM;

void create()
{
    set_name(YEL"����"NOR, ({"huang qi", "huangqi"}));
    set_weight(40);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "���ǲ�������ɽ�еĻ��Σ�ʳ֮��˵���������١�\n");
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
    if (me->is_busy())
        return notify_fail("�𼱣������ԣ�С�ı�ҭ���ˡ�\n");
    if (!id(arg))
        return notify_fail("��Ҫ��ʲô��\n");
    if(arg=="huang qi" || "huangqi") 
    {
        this_player()->set("eff_qi",this_player()->query("max_qi"));
        this_player()->set("qi",this_player()->query("max_qi"));
        message_vision(HIY"$N����һ����Σ�ֻ����ȫ��ů����ģ����������ʢ��\n"NOR,me);
        me->start_busy(1);
        destruct(this_object());
    }
    return 1;
}


