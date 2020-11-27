// murong-jiafa Ľ�ݽ���
// by Lonely

inherit SKILL;

string *action_msg = ({
        "$N������ָ��һʽ��ϴ����������˫�ź�������������ֱ��$n�Ȳ�",
        "$N̤ǰ�����������ʵ������ʹһʽ�����������ֱ��$n������",
        "$Nһ�С�������������ⶶ����佣�����ֱ����$n���������Ҷ�",
        "$N�����ڣ�����ָ��$n��������һ�С�����Ī��������������ǧ��һ�㣬��ɨ$n��$l",
        "$N˫����أ�ʹ�����Ϸɣ�����ֱ��$n��һ�С��ﻢ���¡��������й���ƽ��$n��$l",
        "$N��Цһ�����ὣб����һ�С���ש���񡹣��������$n��$l",
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }
int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("shenyuan-gong", 1) < 20)
                return notify_fail("�����Ԫ�����̫ǳ��\n");
        if ((int)me->query_skill("parry", 1) < 10)
                return notify_fail("��Ļ����мܻ��̫ǳ��\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(50),
                "attack": 60 + random(10),
                "dodge" : 60 + random(10),
                "parry" : 60 + random(10),
                "damage_type" : random(2)?"����":"����",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("qi") < 70)
                return notify_fail("�������������Ľ�ݽ�����\n");
        if ((int)me->query("neili") < 70)
                return notify_fail("�������������Ľ�ݽ�����\n");
        me->receive_damage("qi", 60);
        me->add("neili", -60);
        return 1;
}
           
string perform_action_file(string action)
{
        return __DIR__"murong-jianfa/" + action;
}

