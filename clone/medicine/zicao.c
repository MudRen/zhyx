// zicao.c �ϲ�
// By Alf, Last Update 2001.11

#include <ansi.h>
inherit ITEM;

void create()
{
    set_name(HIM"�ϲ�"NOR, ({"zi cao", "zicao"}));
    set_weight(40);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "��������ɽ�г������ϲݣ�ʳ֮��˵���������١�\n");
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
    if(arg=="zi cao" || "zicao") 
    {
        this_player()->set_temp("nopoison", 1);
        this_player()->set("eff_jing",this_player()->query("max_jing"));
        this_player()->set("jing",this_player()->query("max_jing"));
        this_player()->set("eff_qi",this_player()->query("max_qi"));
        this_player()->set("qi",this_player()->query("max_qi"));
        this_player()->set("food",this_player()->max_food_capacity());
        this_player()->set("water",this_player()->max_water_capacity());
        message_vision(HIM"$N����һ���ϲݣ�ֻ����ȫ��ů����ģ����������ʢ��\n"NOR,me);
        me->start_busy(1);
        destruct(this_object());
    }
    return 1;
}


