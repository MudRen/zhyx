// he.c ��Ů��-˫������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int skill;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("˫������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
	
	if (!mapp(me->query("family")) ||
	    me->query("family/family_name") != "��Ĺ��")
		return notify_fail("�㲢û�������Ĺ����Ů�����ľ��壡\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ�������죬����ʹ��˫������\n");

        if ((int)me->query_skill("yunv-jian", 1) < 80)
                return notify_fail("�����Ů����������죬����ʹ��˫������\n");

        if ((int)me->query_skill("quanzhen-jian", 1) < 50)
                return notify_fail("���ȫ�潣��������죬����ʹ��˫������\n");

        if ((int)me->query("neili", 1) < 400)
                return notify_fail("����������̫��������ʹ��˫������\n");

        if (me->query_skill_mapped("sword") != "yunv-jian")
                return notify_fail("��û�м�����Ů����������ʹ��˫������\n");

        if( (int)me->query_temp("hebi") ) 
                return notify_fail("��������˽��кϱڣ������ٽ�����Ů��ȫ�潣��˫������\n");

        if( (int)me->query_temp("yunv_hebi") ) 
                return notify_fail("���Ѿ���������Ů��ȫ�潣��˫�������ˡ�\n");

        message_vision( HIY "$N" HIY "��ʽ��Ȼһ�䣬��Ů�����м�����ȫ�潣��������Ź�ȴ�ֻ�Ȼ��ɣ�\n" NOR, me);

        skill = ( me->query_skill("sword",1) + me->query_skill("yunv-jian",1)
                + me->query_skill("quanzhen-jian",1) +me->query_skill("force") ) / 12; 

        me->add_temp("apply/attack", skill/2);
        me->add_temp("apply/damage", skill/2);
        me->add_temp("apply/dodge",  skill/2);
        me->add_temp("apply/parry",  skill/2);
        me->set_temp("yunv_hebi", 1);

    me->add_temp("apply/damage", skill/2);

    me->map_skill("sword", "yunv-jian");
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
    me->map_skill("sword", "quanzhen-jian");
        me->setup();
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
    me->map_skill("sword", "yunv-jian");
        me->setup();
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
    me->map_skill("sword", "quanzhen-jian");
        me->setup();
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
    me->map_skill("sword", "yunv-jian");
        me->setup();
    me->add_temp("apply/damage", -skill/2);

        me->add("neili", -300);
        me->start_busy(1+random(2));

	call_out("remove_effect", (skill/4 > 40) ? 40 : skill/4, me, skill/2);
        return 1;
}

private int remove_effect(object me, int amount)
{
        if (!me) return 1;
	me->add_temp("apply/attack", -amount);
	me->add_temp("apply/damage", -amount);
	me->add_temp("apply/parry", -amount);
	me->add_temp("apply/dodge", -amount);
	me->setup();
	me->delete_temp("yunv_hebi");
	return 0;
}
