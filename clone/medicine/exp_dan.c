//exp dan for sun.

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIG "���鵤" NOR, ({"exp dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ������ɫ���ɵ������������Ƶ���Ʒ����˵����....\n");
                set("base_unit", "��");
                set("no_pown",1);
                set("no_give",1);
                set("no_drop",1);
                set("no_sell",1);
                set("no_put",1);
                set("no_get",1);
                set("base_weight", 80);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        mapping my;
        
        int exp,qn;
        
        if ( me->query("new_yeah_2001")>0)
        {
                write("������ǰ�Ѿ��Թ������ֶ����������������Ѿ�û���ˡ�\n");
                destruct(this_object());
                return 1;
        }

        message_vision(HIG "$N" HIG "����һ��" + name() +
                       HIG "���۾�ֱð��⣡\n", me);
        tell_object(me, HIG "��һ�����ֻ���þ�����������ʮ�㡣\n" NOR);

        log_file("static/using", sprintf("%s(%s) eat ���鵤 at %s.\n",
                        me->name(1), me->query("id"), ctime(time())));

        exp = 5000 + random(5000);
        qn  = 2500 + random(2500);
        
        me->set("new_yeah_2001",1);
        me->add("combat_exp",exp); 
        me->add("potential",qn);
        me->start_busy(3);
        destruct(this_object());
        return 1;
}
