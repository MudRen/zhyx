// murong-daofa.c Ľ�ݵ���
// by Lonely

#include <ansi.h>
inherit SKILL;

string *action_msg = ({
        "$NͻȻ���һ�������С���һ�С�"HIC"����ǵ���׳־"NOR"�����������϶�����$n��$l��ȥ",
        "$N���λ���һ�С�"HIR"�䵶��ת��Ǭ��"NOR"��������$w�ڿ��м���ת����Ȧ������$n��$l",
        "$N��һ����һ�С�"HIW"ң����ǧ��ѩ"NOR"��,$w�Ӳ���˼�ǵķ����$n�ľ���նȥ",
        "$N����ӯ�ޱȣ�һ�С�"HIY"׳־����������"NOR"�����������⻯����㷱�ǣ���$n��$l��ȥ",
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }


int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("shenyuan-gong", 1) < 10)
                return notify_fail("�����Ԫ�����̫ǳ��\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 90 + random(20),
                "attack": 40 + random(10),
                "dodge" : 40 + random(10),
                "parry" : 40 + random(10),
                "damage_type" : random(2)?"����":"����",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("qi") < 30)
                return notify_fail("�������������Ľ�ݵ�����\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("�������������\n");
        me->add("neili", -10);        
        me->receive_damage("qi", 20);
        return 1;
}
           
string perform_action_file(string action)
{
        return __DIR__"murong-daofa/" + action;
}

