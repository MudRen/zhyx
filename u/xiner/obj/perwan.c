// perdan.c �ɵ�

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIY "������" NOR, ({ "wan", "meirong wan" }) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
                set("long", "��˵�е����ݼ�Ʒ��\n");
                set("value", 3000000);
		set("unit", "��");
		set("only_do_effect", 1);
	}
}

int do_effect(object me)
{
	int max = 30;

	if (me->query("special_skill/emperor"))	max = 35;

	if (me->query("special_skill/queen")) max = 40;

        message_vision("$Nһ������������һ��" + this_object()->name() +
                       "��\n", me);

        if ( me->query("per") >= max)
        {
                message_vision("$N��Ȼ�����ۡ�������һ�ء�\n", me);
                tell_object(me, "���������ǳ��Ŀࡣ\n");
        } 
          else
        {
                tell_object(me, HIG "һ������ᴩ�������֫�ٺ��������ֱ���º�\n"
                            "��㱼��㷢���Լ��·�����󺣣�׷��Ʈҡ\n"
			    "�㷢���ĸ�ԭ���Ǹ���ª���Լ��Ѿ���������Զȥ\n");
                me->add("per", 1 + random(1) );
                if ( me->query("per") >= max )  me->set("per", max);
        }

        destruct(this_object());
	return 1;
}


int query_autoload() { return 1; } 
