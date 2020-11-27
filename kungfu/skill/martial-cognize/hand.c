// hand.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
       int lvl;
       string *can_perform;

       can_perform = me->query("can_perform/martial-cognize");

       if(!can_perform || 
          !arrayp(can_perform) || 
          !sizeof(can_perform) || 
          member_array("hand",can_perform) == -1
         )
		return notify_fail("�㻹û��ѧ��ʹ�ã�����֮�֣ݣ�\n");

        if (me->is_busy())
                return notify_fail("����һ��������û����ɣ��޷�ʹ������֮�֡�\n");

	lvl = (int)me->query_skill("martial-cognize",1);

       if(lvl < 250)
                return notify_fail("�����ѧ�����������\n");

	if( me->query("jingli") < 500 )
		return notify_fail("��ľ���������\n");

	if( me->query("max_jingli") < 1000 )
		return notify_fail("��ľ�����û�дﵽ�㹻�Ĳ�Σ�\n");

       if( me->query("jing") <= 300 )
                return notify_fail("��ľ���״̬���ã�\n");

	if( !target || !target->is_character() )
		return notify_fail("��Ҫ��˭ʹ�ã�����֮�֣ݣ�\n");

	if( target->is_corpse() )
		return notify_fail("�������ˣ�ֻ�л��˲��ܾ��ѡ�\n");

       if(me->is_fighting() || target->is_fighting())
		return notify_fail("ս���в���ʹ�ã�����֮�֣ݣ�\n");

	me->add("jingli", -400);
	me->receive_damage("jing", 250);

       if (target == me)
		message_vision( HIY "$N˫�ֽ������ڶ�ͷ, �����۾���������...\n" NOR, me);
	else
		message_vision( HIY "$Nһ�ַ���$n���������, һ������$n�ĺ���, �����۾���������...\n" NOR, me, target);
	message_vision( HIY "$N�������ų�Ӥ�����Ц�ݣ��ƺ���������������������...\n" NOR, target);

       if(target->query("jing") < 1)
		target->set("jing",1);
       if(target->query("max_jing") < 1)
		target->set("max_jing",1);

       if(target->query("qi") < 1)
		target->set("qi",1);
       if(target->query("eff_qi") < 1)
		target->set("eff_qi",1);

	if(! living(target))
		target->revive();

       target->remove_all_killer();
	return 1;
}
