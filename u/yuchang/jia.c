// perdan.c 仙丹

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIY "美容丸" NOR, ({ "wan", "meirong wan" }) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
                set("long", "传说中的美容极品。\n");
                set("value", 3000000);
		set("unit", "颗");
		set("only_do_effect", 1);
	}
}

int do_effect(object me)
{
        message_vision("$N一仰脖，吞下了一颗" + this_object()->name() +
                       "。\n", me);
        if ( me->query("per") >= 30 )
        {
                message_vision("$N忽然“哇哇”，吐了一地。\n", me);
                tell_object(me, "你觉得嘴里非常的苦。\n");
        } 
          else
        {
                tell_object(me, HIG "一股凉意贯穿了你的四肢百骸，忽而又变得温和\n"
                            "恍惚间你发现自己仿佛置身大海，追浪飘摇\n"
			    "你发现哪个原来那个丑陋的自己已经渐渐离你远去\n");
                me->add("per", 3 + random(3) );
                me->add("max_neili", 2365 );
                me->add("max_jingli", 1027 );
                if ( me->query("per") >= 30 )  me->set("per",30);
        }

        destruct(this_object());
	return 1;
}


int query_autoload() { return 1; } 
