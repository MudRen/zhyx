// roar.c ����ʨ�Ӻ�

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;
	int ubound;


        if (me->query("family/family_name") != "������")
                return notify_fail("�㲻�����ֵ��ӣ��޷�ʹ���׽������\n");

        if ((int)me->query("neili") < 600)
                return notify_fail("�������������\n");

        if (environment(me)->query("no_fight"))
                return notify_fail("�����ﲻ�ܹ������ˡ�\n");

        skill = me->query_skill("force");

        me->add("neili", -150);
        me->receive_damage("qi", 0);

        me->start_busy(5);
        message_combatd(HIY "$N" HIY "�������һ�����������ŷ�������һ��"
		        "���춯�صľ޺�\n" NOR, me);

        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! living(ob[i]) || ob[i] == me) continue;
                if (skill / 2 + random(skill / 2) < (int)ob[i]->query("con") * 2)
	                continue;

                damage = skill - ((int)ob[i]->query("max_neili") / 20);
                if (damage > 0)
                {
                        if (!userp(ob[i]))
                        {
                                ob[i]->receive_damage("jing", damage * 2, me);
                                if ((int)ob[i]->query("neili") < skill * 2)
                                        ob[i]->receive_wound("jing", damage, me);
                                tell_object(ob[i], "�������ǰһ�������ð������ʹ������Ҫ�ѿ�һ����\n");
                        }else
                        {
                                ubound = damage * 2;
                                if (ob[i]->query("jing") < damage *2) ubound = ob[i]->query("jing");
                                ob[i]->receive_damage("jing", ubound, me);
                                ubound = damage;
                                if (ob[i]->query("eff_jing") < damage *2) ubound = ob[i]->query("eff_jing");
                                if ((int)ob[i]->query("neili") < skill * 2)
                                        ob[i]->receive_wound("jing", ubound, me);
                                tell_object(ob[i], "�������ǰһ�������ð������ʹ������Ҫ�ѿ�һ����\n");
                                if (ob[i]->query("jing") == 0) ob[i]->unconcious();
                        }
                }
                if (!userp(ob[i]))
                {
                	me->want_kill(ob[i]);
                	ob[i]->kill_ob(me);
                }
        }

        return 1;
}
