#include <ansi.h>
#include "pill.h"

void create()
{
        set_name(HIM "�����" NOR, ({"yuchi zhou", "yuchi", "zhou"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
              set("long", HIC "������������ɵ��࣬���Ǹ߼�����\n" NOR);
              set("base_unit", "��");
              set("base_value", 100);
              set("base_weight", 55);
              set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        int na, un, limit1, limit2;

        na = query("name");
        un = query("base_unit");

        limit1 = me->max_food_capacity();
        limit2 = me->max_water_capacity();

        message_vision(HIC "$N" HIC "������һ" + un + na + HIW "��\n" NOR, me);

	if (me->query("food") < limit1 * 4 || me->query("water") < limit2 * 4)
	{
       		tell_object(me, HIY "��ֻ��ƣ��һɨ���գ���Ҳ�����ü�����\n" NOR);

	        if (me->query("food") < limit1 * 4)
		        me->set("food", limit1 * 4);

	        if (me->query("water") < limit2 * 4)
        		me->set("water", limit2 * 4);
	} else
	{
       		tell_object(me, HIR "��ֻ�����ӡ����������и���ͣ�������˸����"
                                "�ޱȵ�ƨ��\n" NOR);

	        if (me->query("food") > limit1 / 10)
		        me->set("food", limit1 / 10);

	        if (me->query("water") > limit2 / 10)
        		me->set("water", limit2 / 10);
	}
        me->start_busy(random(1) + 1);
        add_amount(-1);

        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}
