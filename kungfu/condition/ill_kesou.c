// ill_kesou.c

#include <ansi.h>
#include <condition.h>

inherit ILLNESS;

string name() { return "ill_kesou"; }

int min_qi_needed() { return 10; }

int update_condition(object me, int duration)
{
if( duration < 1||(me->query("age")<=15)) return 0;

        message("vision", HIG + me->name() + "˻����ɤ�ӿ���������Ȼ��"
		          "���������˺�һ�󣬿����ǲ��Ĳ��ᣡ\n" NOR,
                environment(me), me);

        if( !living(me) && me->query("qi") < 1 ) {
                me->set_temp("die_reason", "���Ծò���������Ѫ������");
                me->die();
                return 0;
        }
        else
                tell_object(me, HIB "��˻����ɤ�ӿ���������Ȼ��"
		                "���������˺�һ�󣬿����ǲ��Ĳ��ᣡ\n" NOR );

        me->receive_wound("qi", 1);
        me->receive_damage("qi", 1);
        me->apply_condition(name(), duration - 1);

        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}