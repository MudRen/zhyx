// ����ɢ(jinmi san)
// by April 2001.11.10

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIW "����ɢ" NOR, ({"jinmi san", "jinmi", "san"}));
    set_weight(25);
    if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 8000);
		set("only_do_effect", 1); 
	}

    setup();
}

int do_effect(object me)
{
	if (!me->query_condition("yf_zhen_poison"))
	{
		tell_object(me,"�㲢û���з䶾����\n");
		return 1;
	}

        me->clear_condition("yf_zhen_poison");
	message_vision(HIY "$N������һ������ɢ�����д������д��࣬һ������������Ƣ��\n"NOR,me);
	tell_object(me,HIY "��о����ڵķ䶾��������ȥ��\n" NOR, me);

	destruct(this_object());
	return 1;
}
