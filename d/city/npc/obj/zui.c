// zui.c  ������
// created by cpu 2002
#include <ansi.h>
inherit ITEM;
void setup()
{}
void init()
{
        add_action("do_drink", "drink");
}
void create()
{
	set_name(HIG"�������"NOR, ({"shenxian zui", "jiubei"}));
	set_weight(700);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", HIB"һֻ�������صľƱ�������װ���ƺ���һ�����԰׾ơ�\n"NOR);
		set("unit", "��");
		set("value", 5000);
		
	}

}

int do_drink(string arg)
{
            int drk;
            object me;
            me =  this_player();
	drk = ((int)me->query("con") + (int)me->query("max_neili") / 50) * 2;
            
if (!id(arg))
        return notify_fail("��Ҫ��ʲô��\n");
me->apply_condition("drunk",drk-1);
message_vision(HIG"$N����һ��������ƣ�����ȥ��ʱ���˼������⣡\n"NOR,me);
        destruct(this_object());
        return 1;
}

