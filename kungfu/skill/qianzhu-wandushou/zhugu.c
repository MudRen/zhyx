#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int lvl,ap,dp;
        int damage;

	if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/qianzhu-wandushou/zhugu"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

	if (environment(me)->query("no_fight"))
		return notify_fail("���ﲻ�ܹ������ˣ�\n");

	if (! target || ! target->is_character())
		return notify_fail("��Ҫ��˭ʩչ��ƾ���\n");

	if (target->query("not_living"))
		return notify_fail("��������ǲ��ǻ��ˡ�\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ��������ʩչ��ƾ���\n");

        if ((int)me->query_skill("qianzhu-wandushou", 1) < 150)
                return notify_fail("���ǧ��������Ϊ���������ڻ��޷�ʩչ��ƾ���\n");

        if (me->query_skill_mapped("hand") != "qianzhu-wandushou")
                return notify_fail("��û�м���ǧ�����֣��޷�ʩչ��ƾ���\n");

        if (me->query("neili") < 400)
                return notify_fail("������������������޷�ʩչ��ƾ���\n");

        msg = HIB "$N" HIB "ʩ����ƾ���ֻ��һ�ƺ�����"
              "ָ��͸����ֻһ����û����$n" HIB "��ü�ģ�\n" NOR;

        ap = (int)me->query_skill("force") + me->query("dex") * 10 + (int)me->query_skill("qianzhu-wandushou", 1);
        dp = (int)target->query_skill("force") + (int)target->query_skill("parry",1) + target->query("dex") * 10;
        lvl = (int)me->query_skill("qianzhu-wandushou",1);
        if (ap * 3 /5 +random(ap)> dp)
        {
                damage = me->query_skill("hand") + me->query_skill("force");
                damage = damage + random(damage/2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                           HIR "$p" HIR "ֻ����һ����ɽ�ľ���˳ָ����"
                                           "��������ֻ����ȫ������ܣ����ۡ���һ��"
                                           "�³�һ�ں�Ѫ��\n" NOR);
                                           
                if (target->query("per")>10 && random(5)==1)
                	{
                		msg += HIG "$n" HIG "ֻ�������ϻ������ģ�����һ������Ȼ����һ���!!"
                		                    "���ﲻ�ɵ�һ�������ˣ���������......\n" NOR;  
                		target->set("per", target->query("per")-1);
                	}
                target->affect_by("qianzhu_wandushou",
                                  ([ "level" : lvl * 3/5 + random(lvl / 2),
                                     "id"    : me->query("id"),
                                     "duration" : lvl / 40 + random(lvl / 18) ]));
                me->add("neili", -200);
                me->start_busy(2);
        } else
        {
                msg += CYN "����$p" CYN "�����������������ڹ�"
                       "��������һָ�Ķ�����\n" NOR;
                me->start_busy(3);
                me->add("neili", -80);
        }
        message_combatd(msg, me, target);
        

        return 1;
}
