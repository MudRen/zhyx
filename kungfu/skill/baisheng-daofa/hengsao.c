// hengshao.c ��ɨǧ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string final(object me, object target, int ap, int dp);
 
int perform(object me, object target)
{
	object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("����ɨǧ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("���á���ɨǧ�����������гֵ���\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹���\n");

	if ((int)me->query_skill("baisheng-daofa",1) < 150)
		return notify_fail("��İ�ʤ�����������ң��޷�ʹ�á���ɨǧ������\n");

        if (me->query_skill_mapped("blade") != "baisheng-daofa")
                return notify_fail("��û�м�����ʤ�������޷�ʹ�á���ɨǧ������\n");

        ap = me->query_skill("blade") + me->query_str() * 10;
        if (me->query("character") == "��������")
        {
                msg = HIR "$N" HIR "��Ŀ��ȣ�ɱ����Ȼ�����ֳ�" + weapon->name() +
                      HIR "���޷��˵���Ȼ��ɨ$n" HIR "��ȫȻ����������������Ȼ��\n" NOR;
                ap += ap * 3 / 10;
        } else
                msg = HIR "$N" HIR "����������" + weapon->name() +
                      HIR "���棬��ৡ���һ��ɨ��$n��\n" NOR;


        if (living(target))
             dp = target->query_skill("parry") + target->query_str() * 10;
        else   dp = 0;

        damage = 0;
        if (ap / 2 + random(ap) > dp)
	{
		damage = ap / 2 + random(ap / 2);
                me->add("neili", -350);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           (: final, me, target, ap, dp :));
		me->start_busy(4);
                target->start_busy(1);
	} else 
	{
		msg += HIC "$n" HIC "�����мܣ�Ӳ�����ĵ�ס���������ʧɫ֮��ɱһ����\n" NOR;
                me->add("neili", -150);
		me->start_busy(4);
                target->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}

string final(object me, object target, int ap, int dp)
{
        object weapon;
        string msg;

        msg = HIR "$n" HIR "��æ�ֵ���ȴ�����мܵ�ס��������"
              "����һ����÷������Զ��ƽɳ��";
        if (ap / 3 > dp)
        {
                msg += "�ʹ˱�����\n" NOR;
                call_out("char_killed", 0, target);
        } else
        if ((ap / 2 > dp) && objectp(weapon = target->query_temp("weapon")))
        {
                msg += "���е�" + weapon->name() + HIR "��Ҳ����ס��Ӧ��������\n" NOR;
                weapon->move(environment(me));
        } else
                msg += "\n" NOR;
        return msg;
}

void char_killed(object ob)
{
        if (objectp(ob))
                ob->die();
}
