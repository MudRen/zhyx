// shade.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int lvl,i;
	object env, *inv;
       string *can_perform;

       can_perform = me->query("can_perform/martial-cognize");

       if(!can_perform || 
          !arrayp(can_perform) || 
          !sizeof(can_perform) || 
          member_array("shade",can_perform) == -1
         )
		return notify_fail("�㻹û��ѧ��ʹ�ã�����֮��ݣ�\n");

        if (me->is_busy())
                return notify_fail("����һ��������û����ɣ��޷�ʹ������֮��\n");

	lvl = (int)me->query_skill("martial-cognize",1);

       if(lvl < 250)
                return notify_fail("�����ѧ�����������\n");

	if( me->query("jingli") < 500 )
		return notify_fail("��ľ���������\n");

	if( me->query("max_jingli") < 1000 )
		return notify_fail("��ľ�����û�дﵽ�㹻�Ĳ�Σ�\n");

       if( me->query("jing") <= 300 )
                return notify_fail("��ľ���״̬���ã�\n");

       if(me->query("env/invisibility"))
                return notify_fail("������ʩչ������֮���\n");

       if (time() - me->query("last_shade_time") < 600)
                return notify_fail("���ʹ�ù�������֮��ݲ��ã���û����ȫ�ָ�����������Ϣһ��ɡ�\n");

       if (environment(me) && environment(me)->query("no_fight"))
                return notify_fail("���ﲻ��ʹ�ã�����֮���!\n");

	me->add("jingli", -300);
	me->receive_damage("jing", 200);

	message_vision(HIW "$N��ɫ���أ����������˫Ŀ���������һ���ɫ����Ѹ��ӿ���ǿף����Լ��������¶���Χ�ţ������˽����黯������\n" NOR, me);
	        me->set("env/invisible", 1);

       me->set("last_shade_time",time());
       me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), lvl/5);
       if( me->is_fighting() ) me->start_busy(3);
       return 1;

}
void remove_effect(object me)
{
        me->delete("env/invisible");
        tell_object(me,"�������֮��ʧЧ�ˣ�\n");
        message_vision(HIW "һ������ͻȻ���֣�����Խ��ԽŨ����������ɢ��ȴ��$N�����ˡ�\n" NOR,me);
}
