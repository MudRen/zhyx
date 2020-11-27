// throw.c ������ʩ��
// By Yzuo 97.04

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object obj;
        string msg,str;
        int lvl, dp;

        if (! target) target = offensive_target(me);

        if (environment(me)->query("no_fight"))
                return notify_fail("���ﲻ�ܹ�������! \n");

        if (! target || ! target->is_character())
                return notify_fail("ʩ��ֻ�ܶԶ���ʹ�á�\n");

        if (me->query_temp("weapon"))
                return notify_fail("��ֻ�п��ֲ���ʹ�ó����ơ�\n");

        if (!(me->query_skill_mapped("strike") == "chousui-zhang"))
                return notify_fail("�㲢û�м��������ƣ�����ø�ʬ����\n");

        if (!(me->query_skill_prepared("strike") == "chousui-zhang"))
                return notify_fail("�㲢û��׼�������ƣ�����ø�ʬ����\n");


        if (target->query("not_living"))
                return notify_fail("��������ǲ��ǻ��ˡ�\n");

        if ((int)me->query_skill("huagong-dafa", 1) < 40)
                return notify_fail("��Ļ����󷨲�����죬����ʩ����\n");

        if ((int)me->query_skill("chousui-zhang", 1) < 40)
                return notify_fail("��ĳ����Ʋ�����죬����ʩ����\n");

        if (! (objectp(obj=present("corpse", environment(me)))  ||
            objectp(obj = present("corpse", me)) ||
            objectp(obj = present("Skeleton", environment(me))) ||
            objectp(obj = present("Skeleton", me)) ) )
                return notify_fail("����Χû��ʬ�壬�޷�ʩչ������\n");

        msg = CYN "$N" CYN " ˳��ץ��ʬ�壬�������������ϣ�����$n"
              CYN "��\n" NOR;

        if (living(target))
                dp = target->query_skill("dodge") / 2;
        else    dp = 0;

        if (random(lvl = (int)me->query_skill("chousui-zhang", 1)) > dp)
        {
                msg += HIR " ���$p" HIR "��$P" HIR "���˸����ţ�\n" NOR;
                target->receive_damage("qi",(int)me->query_skill("chousui-zhang", 1),me);
                target->receive_wound("qi",15 + random(10),me);
                target->receive_wound("jing", 10,me);
                target->affect_by("xx_poison",
                        ([ "level" : me->query_skill("poison",1),
                           "id"    : me->query("id"),
                           "duration" : me->query("poison",1)/20 ]));
                str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                msg += "($n"+str+")\n";
                me->start_busy(2);
        } else
        {
                msg += CYN "����$p" CYN "��æ����һ�ԣ����˿�ȥ��\n" NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        destruct(obj);
        return 1;
}

