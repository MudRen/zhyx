// roar.c �������

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;

        if (environment(me)->query("no_fight"))
                return notify_fail("���ﲻ�ܹ�������! \n");

        if (((int)me->query("neili") < 500) || (int)me->query_skill("biyun-xinfa", 1) < 50) 
                return notify_fail("���������\"��\"�ĺ���һ��, ��������˼�ֻ����\n");

        skill = me->query_skill("force");

        me->add("neili", -150);
        me->receive_damage("qi", 10);

        me->start_busy(1);
        message_combatd(
                HIY "$N�������һ�����������ŷ�������һ�����춯�صľ޺�" + HIR "�����޵а�" NOR + "��\n" NOR, me);

        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++) 
        {
                if (! ob[i]->is_character() || ob[i] == me)
                        continue;
                        
                if (skill / 2 + random(skill / 2) < (int)ob[i]->query("con") * 2) continue;
                
                me->want_kill(ob[i]);
                me->fight_ob(ob[i]);
                ob[i]->kill_ob(me);

                damage = skill - (int)ob[i]->query("max_neili") / 10;
                if (damage > 0) 
                {
                        ob[i]->set("last_damage_from", me);
                        ob[i]->receive_damage("jing", damage * 2, me);
                        if ((int)ob[i]->query("neili") < skill * 2)
                                ob[i]->receive_wound("jing", damage, me);
                        tell_object(ob[i], "�������ǰһ�������ð������ʹ������Ҫ�ѿ�һ����\n");
                }
        }

        return 1;
}




