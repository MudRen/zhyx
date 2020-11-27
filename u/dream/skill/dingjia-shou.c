// dingjia-qinnashou.c ����������


inherit SKILL;

string *action_msg = ({
        "$Nʹ��һ�С���β�֡��������Ƹ���Ȧ������ȥץס��$n������һŤ��",
        "$N����ʹ��һ�С������֡����������������ֱ�ȥץ$n�ļ�ͷ��",
        "$NͻȻһ�С�����ץ����˫��һǰһ��ֱȡ$n����硣",
        "$N����һ�С���צ�֡���ץ��$n���ĺ�ġ���̨Ѩ����",
        "$N����ʹ��һ�С���Ů���롹������ֱ͸��ָָ�⣬����$n�ĺ�����",
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�����������ֱ�����֡�\n");
                
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������̫�����޷������������֡�\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 260 + random(50), 
                "attack": 40 + random(10), 
                "dodge" : 40 + random(10), 
                "parry" : 40 + random(10), 
                "damage_type" : random(2)?"����":"����", 
        ]); 
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 50)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 50)
                return notify_fail("����������������������֡�\n");
        me->receive_damage("qi", 40);
        me->add("shen", -10);
        me->add("neili", -40);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"dingjia-shou/" + action;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if (me->query_temp("weapon"))
                return 0;

        lvl = me->query_skill("dingjia-shou", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

