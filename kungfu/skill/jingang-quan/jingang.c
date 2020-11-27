// jingsng.c ���ȭ ������ͨ
//update by akasumi

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
	object weapon;	
  	string msg;
	int d_count, count, qi, maxqi, skill;

	if ((int)me->query_temp("jingang"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }
	if (! target || ! me->is_fighting(target))
		return notify_fail("��������ͨ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((me->query_skill_mapped("force") != "hunyuan-yiqi") && (me->query_skill_mapped("force") != "yijinjing") && (me->query_skill_mapped("force") != "luohan-fumogong")) 
                return notify_fail("������û�м��������ڹ�Ϊ�ڹ�������ʩչ"  "��\n"); 
	if ((int)me->query("neili") < 500)
		return notify_fail("��������������޷�ʩչ��������ͨ����\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���Ϊ����������ʹ�ô�����ͨ��\n");

	if ((int)me->query_skill("cuff") < 150)
		return notify_fail("���ȭ���������ң��޷�ʹ�ô�����ͨ��\n");

	if (me->query_skill_mapped("cuff") != "jingang-quan") 
		return notify_fail("��û�м������ȭ���޷�ʹ�ô�����ͨ��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "ʹ������ȭ�ľ�����������ͨ����������Ȼ���ӣ�\n" NOR;
	
	qi = me->query("qi");
	maxqi = me->query("max_qi");
	skill = me->query_skill("jingang-quan", 1) ;
	count = (int) (skill/5);	

	if (qi > (maxqi * 0.4))
	{	
		message_combatd(msg, me, target);
		
		me->add_temp("str", count);
		me->add_temp("dex", -count);
		me->set_temp("jingang", 1);
		me->start_call_out((: call_other, __FILE__, "remove_effect", me, count :), skill/3);

		me->add("neili", -200);
	} else
        {
		msg = HIR "$N" HIR "ƴ����������ʹ���˴���ȭ����"
                      "������, ȫ�����һ����, ����$n" HIR "ͬ���ھ���\n" NOR;
		message_combatd(msg, me, target);
		me->add_temp("str", count * 9);
		me->set_temp("jingang", 1);

		me->start_call_out((: call_other, __FILE__, "remove_effect", me, count * 9 :), 2);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
		me->set("neili",0);
		me->add("max_neili", -10);

		msg = HIR "$N" HIR "�þ������һ������, ���һ����Ѫ, һͷ�Ե��ڵأ�\n" NOR;
		message_combatd(msg, me, target);
		me->unconcious();
	}
	return 1;
}

void remove_effect(object me, int amount)
{
	if ((int)me->query_temp("jingang"))
	{
		me->add_temp("str", -amount);
		me->add_temp("dex", amount);
		me->delete_temp("jingang");
		tell_object(me, "��Ĵ�����ͨ������ϣ��������ջص��\n");
	}
}
