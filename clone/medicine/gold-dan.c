// baoming.c

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIY "九转金丹" NOR, ({"gold dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "这是一颗金黄颜色的仙丹，是神仙炼制的物品，据说吃了....\n");
                set("base_unit", "颗");
                set("base_value", 100000);
                set("base_weight", 80);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        mapping my;
	
	int exp,qn;
	
        if ( me->query("gold_dan_1")>0)
        {
                write("你好象从前已经吃过了这种东西，现在它对你已经没用了。\n");
                return 1;
        }

	message_vision(HIG "$N" HIG "吃下一粒" + name() +
                       HIG "，眼睛直冒金光！\n", me);
        tell_object(me, HIG "不一会儿你只觉得精神饱满，力量十足。\n" NOR);

        log_file("static/using", sprintf("%s(%s) eat 九转金丹 at %s.\n",
                        me->name(1), me->query("id"), ctime(time())));

	exp = 25000 + random(10000);
	qn  = 18000 + random(8000);
	
	me->set("gold_dan_1",1);
	me->add("combat_exp",exp); 
	me->add("potential",qn);
	me->start_busy(3);
        destruct(this_object());
	return 1;
}
