// roar.c 佛门狮子吼

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;
	int ubound;


        if (me->query("family/family_name") != "少林派")
                return notify_fail("你不是少林弟子，无法使用易筋经绝技。\n");

        if ((int)me->query("neili") < 600)
                return notify_fail("你的真气不够。\n");

        if (environment(me)->query("no_fight"))
                return notify_fail("在这里不能攻击他人。\n");

        skill = me->query_skill("force");

        me->add("neili", -150);
        me->receive_damage("qi", 0);

        me->start_busy(5);
        message_combatd(HIY "$N" HIY "深深地吸一囗气，真力迸发，发出一声"
		        "惊天动地的巨吼！\n" NOR, me);

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
                                tell_object(ob[i], "你觉得眼前一阵金星乱冒，耳朵痛得像是要裂开一样！\n");
                        }else
                        {
                                ubound = damage * 2;
                                if (ob[i]->query("jing") < damage *2) ubound = ob[i]->query("jing");
                                ob[i]->receive_damage("jing", ubound, me);
                                ubound = damage;
                                if (ob[i]->query("eff_jing") < damage *2) ubound = ob[i]->query("eff_jing");
                                if ((int)ob[i]->query("neili") < skill * 2)
                                        ob[i]->receive_wound("jing", ubound, me);
                                tell_object(ob[i], "你觉得眼前一阵金星乱冒，耳朵痛得像是要裂开一样！\n");
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
