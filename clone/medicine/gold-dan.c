// baoming.c

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIY "��ת��" NOR, ({"gold dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Ž����ɫ���ɵ������������Ƶ���Ʒ����˵����....\n");
                set("base_unit", "��");
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
                write("������ǰ�Ѿ��Թ������ֶ����������������Ѿ�û���ˡ�\n");
                return 1;
        }

	message_vision(HIG "$N" HIG "����һ��" + name() +
                       HIG "���۾�ֱð��⣡\n", me);
        tell_object(me, HIG "��һ�����ֻ���þ�����������ʮ�㡣\n" NOR);

        log_file("static/using", sprintf("%s(%s) eat ��ת�� at %s.\n",
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
