// juehu-shou.c -
// updated by Lonely

inherit SKILL;

mapping *action_msg = ({
        "$Nһʽ����ţ�����������ƻ�צ����ָ�繳�����۵ɵ�ͨ�죬ֱ��$n���ɲ�",
        "$N��֫���أ�ͷ���״�������������������ͻȻ��֫����һ���Ѵܵ�$n���£������͵��ϴ�����һʽ����ƣ������",
        "$N���ָ߸߾���������磬һʽ��׳ʿ���󡹣����۾ͳ�$n�����忳ȥ",
        "$NһԾ����ֱ��$n��˫�����£�˫����ס$n�ľ�����һŤ����˫�ֳɹ���֮�ƣ���$n���ɲ��ݺ���ȥ������һʽ����Ҷ�����",
        "$Nʹһʽ����ǰ���󡹣�����һ��Ϊ������ֻ�����������ư㳯$n�ĺ������ɲ���ȥ",
        "$Nȫ��ؽ�žž���죬�����ֽ��һʽ�����Ӿ��������ӥצץ��$nȫ��Ҫ����˲������ӥצ�ֺ�Ϊһצֱ��$n���ɲ�ץ��",
});

int valid_enable(string usage) { return usage == "claw" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����ץ�����ֱ�����֡�\n");
                
        if ((int)me->query_skill("taiji-shengong", 1) < 40)
        
                return notify_fail("���̫���񹦻�򲻹����޷�ѧ��ץ�����֡�\n");
                
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������̫�����޷�����ץ�����֡�\n");
                
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(20),
                "attack": 60 + random(10),
                "dodge" : 60 + random(10),
                "parry" : 60 + random(10),
                "damage_type" : random(2)?"ץ��":"����",
        ]);
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 30)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("���������������ץ�����֡�\n");
        me->receive_damage("qi", 25);
        me->add("shen", -10);
        me->add("neili", -10);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"juehu-shou/" + action;
}


