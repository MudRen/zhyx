// douzhuan-xingyi ��ת����
// Created by Lonely (06/11/2002)

#include <ansi.h>
inherit SKILL;

string *parry_msg = ({
        YEL"�����һ��������������$Nһ��һ����$N��������Խ����������һ��"NOR,
        BLU"$N����һ����������$L��$n����$N��$L������Ī��������ﻬ��һ��"NOR,
        HIW"$N˫��ǰ̽����۴���$n�ұۣ��ұ�ʹ��$n��������$n���л�ȥ"NOR,
        HIY"$N���ƶ�ת��$n����Ī�����������;ת�˷���ֱ���Լ�Ϯ��"NOR,
        YEL"$N�����Ϲۣ�˫����Է��ཻ���ƣ�̸Ц�侹ʹ��$n�������գ�ʹ��$n��֪����Ǻ�"NOR,
        BLU"$N����������$n�͹����ʹ������������$n�ĳ�����������$n��������������"NOR,
        HIW"ֻ��$N����Ʈ�磬ǡ���������ƣ������һʽ��˫�ƶ����޶�����׽��������$n��$l"NOR,
        HIY"$N����Ʈ�������������ƶ�ת֮�䷴��$n����������$n��ȴ����$n��˼�������"NOR,
});

int valid_enable(string usage)
{
        return usage == "parry";
}

string query_parry_msg(object weapon)
{
        
        return parry_msg[random(sizeof(parry_msg))] + "��\n";
}

int valid_learn(object me)
{
        // return notify_fail("��ת����ֻ��ͨ����������ߡ�\n");
        return 1;
}

int practice_skill(object me)
{
        return notify_fail("��ת����ֻ��ͨ����������ߣ��޷�ͨ����ϰ����ߡ�\n");
}

string perform_action_file(string action)
{
        return __DIR__"douzhuan-xingyi/" + action;
}

int parry_action(object me, object target, object target_weapon, int attack_type, mapping action, string limb)
{
        string msg;
        object weapon, *enemy;
        int dp, ap, i, nb;

        if (me->query_condition("dugu_damage") ||
            (string)target->query("race") == "Ұ��" ||
            ! living(me) ||
            me->is_busy())
                return 0;
        
        weapon = me->query_temp("weapon");
        
        if (target_weapon)       
        {
                if(! weapon) return 0;
        }
                
        msg = "\n" + action["action"] + "\n";
        msg += HIW "$n���㲻�ܣ�΢΢һЦ��ʹ��$N�ľ������Ա�֮�����Ʊ���\n" NOR;
        
        if (target_weapon)
        {
                ap = target->query_skill(target_weapon->query("skill_type"));
                msg = replace_string(msg, "$w", target_weapon->query("name"));        
        }
        else    ap = target->query_skill("force");
        ap += target->query_skill("count", 1);         
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("douzhuan-xingyi", 1);

        msg = replace_string(msg, "$l", limb);
        
        if (ap / 2 + random(ap) < dp)
        {        
                message_combatd(msg, target, me);
                if (! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack1(me, target, weapon, 2, action, limb);
                return 1;
        }
        
        return 0;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if (me->query_skill("shenyuan-gong", 1) < 100
        ||  me->query_skill_mapped("force") != "shenyuan-gong")
                return 0;

        lvl = me->query_skill("douzhuan-xingyi", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

