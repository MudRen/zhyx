#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "��" NOR, ({ "jin dan", "jin", "dan" }) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW " �˷������Ƶ�����𵤣�\n" NOR);
                set("no_give", 1);
                set("no_drop", 1);
                set("no_sell", 1);
                set("unit", "��");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        string mapsk;
        int effect;
        int neili;

        effect = 0;

        if(! objectp(present("jin dan", me)))return 0;

        if (me->query("eat_moon_gift/y2003"))
        {
              message_vision(HIY "$N" HIY "����һЦ�����½𵤣�����ûʲô���ã�\n" NOR, me);
              destruct(this_object());
              return 1;
        }

       	message_vision(HIY "$N" HIY "����һЦ���������ˡ�\n" NOR, me);

        me->set("eat_moon_gift/y2003", 1);
       	me->add("combat_exp", 50000);
       	me->add("potential", 10000);

       	mapsk = me->query_skill_mapped("force");

       	if (me->can_improve_skill("force"))
               	me->improve_skill("force", 1500000);
       	if (stringp(mapsk) && me->can_improve_skill(mapsk))
               	me->improve_skill(mapsk, 1500000);

       	mapsk = me->query_skill_mapped("dodge");

       	if (me->can_improve_skill("dodge"))
               	me->improve_skill("dodge", 1500000);
       	if (stringp(mapsk) && me->can_improve_skill(mapsk))
               	me->improve_skill(mapsk, 1500000);

       	mapsk = me->query_skill_mapped("parry");

       	if (me->can_improve_skill("parry"))
               	me->improve_skill("parry", 1500000);
       	if (stringp(mapsk) && me->can_improve_skill(mapsk))
               	me->improve_skill(mapsk, 1500000);

       	mapsk = me->query_skill_mapped("unarmed");

       	if (me->can_improve_skill("unarmed"))
               	me->improve_skill("unarmed", 1500000);
       	if (stringp(mapsk) && me->can_improve_skill(mapsk))
               	me->improve_skill(mapsk, 1500000);

       	if (me->can_improve_skill("martial-cognize"))
               	me->improve_skill("martial-cognize", 1500000);

        message_vision(HIC "$N" HIC "����������㾭���һ���Ǳ�ܡ�\n" NOR, me);

        destruct(this_object());
        return 1;
}
