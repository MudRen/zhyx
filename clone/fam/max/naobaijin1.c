#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "Ԫ���Ͻ�" NOR, ({ "zijin dan", "dan", "zijin" }) );
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "һ�����۴�С��ҩ�裬���˱ǣ�һ��֮�±���Ŀ�\n"
                                "����������ҩ�������Ž�����Ĺ������ֳ��أ���\n"
                                "���Ļ�����ͣ������������һ�㡣\n" NOR);
                set("value", 500000);
                set("no_drop",1);
                set("unit", "��");
                set("no_sell",1);
                set("no_give",1);
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        string mapsk;
        int effect;
        int neili;

        log_file("static/using", sprintf("%s(%s) eat Ԫ���Ͻ� at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

        effect = 0;

       	message_vision(HIW "$N" HIW "����һЦ����һ��Ԫ���Ͻ𵤿��"
                       "���¶�ȥ��\n" NOR, me);

       	me->add("combat_exp", 50000);
       	me->add("potential", 10000);

       	mapsk = me->query_skill_mapped("force");

       	if (me->can_improve_skill("force"))
               	me->improve_skill("force", 1500000);
       	if (stringp(mapsk) && me->can_improve_skill(mapsk))
               	me->improve_skill(mapsk, 1500000);

       	mapsk = me->query_skill_mapped("parry");

       	if (me->can_improve_skill("parry"))
               	me->improve_skill("parry", 1500000);
       	if (stringp(mapsk) && me->can_improve_skill(mapsk))
               	me->improve_skill(mapsk, 1500000);

       	mapsk = me->query_skill_mapped("dodge");

       	if (me->can_improve_skill("dodge"))
               	me->improve_skill("dodge", 1500000);
       	if (stringp(mapsk) && me->can_improve_skill(mapsk))
               	me->improve_skill(mapsk, 1500000);

       	me->improve_neili(300);
       	me->improve_jingli(300);
        me->add("magic_points", 500);
        destruct(this_object());
        return 1;
}
