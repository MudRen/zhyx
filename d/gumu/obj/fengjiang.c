// fengjiang.c ��佬
// By Lgg,1998.9

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("��佬", ({"jiang", "feng jiang"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "һƿ����䳲���ɵĽ���\n");
                set("unit", "ƿ");
                set("value", 30);
		set("only_do_effect", 1); 
        }
}

int do_effect(object me)
{
	me->set("jing", (int)me->query("max_jing"));
	message_vision(HIY"$N������һƿ��佬������佬�ǳ��ĸ���ʵ���Ǻóԡ�\n"NOR,me);
	if (me->query_condition("yf_zhen_poison") > 0)
	{
	        me->clear_condition("yf_zhen_poison");
		tell_object(me,HIY "��о����ڵķ䶾��������ȥ��\n" NOR, me);
	}
	destruct(this_object());
	return 1;
}
