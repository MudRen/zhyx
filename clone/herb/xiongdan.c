#include "herb.h"

void create()
{
        set_name(HIR "�ܵ�" NOR, ({ "xiong dan", "xiong", "dan", "herb_xiongdan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "����һ�����ʵ��ܵ����ľ�ҩ����\n" NOR);
                set("base_unit", "��");
                set("base_value", 15000);
                set("base_weight", 200);
             // set("only_do_effect", 1);
        }
        setup();
}

/* int do_effect(object me)
{
        mapping my = me->query_entire_dbase(); 
        message_vision(HIG "$N" HIG "һ��������" + name() +
                       HIG "�������£��������졣\n" NOR, me);
        tell_object(me, HIY"��е��Լ�������������!\n"NOR);

        add_amount(-1);

        if (query_amount() < 1)
                destruct(this_object());

        me->improve_neili(1); 
      
        if (me->query("neili") < me->query("max_neili")) 
             my["neili"]  = my["max_neili"];
        return 1;
} */