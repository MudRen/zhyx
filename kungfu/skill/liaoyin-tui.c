inherit SKILL;

mapping *action = ({
([      "action": "ֻ��$N����һ�����������һ�����������¡���׼$n�ĵ���������ץ�˹�ȥ",
        "dodge": 15,
        "parry": 15,
        "attack": 20,
        "force": 120,
        "damage_type":  "ץ��"
]),
([      "action": "$N����һ������ȭ��������ȭ���磬һ�С��ɺ�ժ�ҡ��Ʋ��ɵ��ػ���$n�ĵ���",
        "dodge": 25,
        "parry": 25,
        "attack": 30,
        "force": 140,
        "damage_type":  "ץ��"
]),
([      "action": "ֻ��$N������ʽ��һ�С�����������ʹ�û����з硣����ȴ����һ������$n����",
        "dodge": 20,
        "parry": 20,
        "attack": 25,
        "force": 160,
        "damage_type":  "ץ��"
]),
([      "action": "$Nһ��ת�����ƻ��أ�����ʹ�˸��������̸������Ӻ�����$nƨ��һ����ȥ",
        "dodge": 30,
        "parry": 30,
        "attack": 40,
        "force": 270,
        "damage_type":  "ץ��"
]),
});

int valid_learn(object me)
{

        if( me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������ȱ�����֡�\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("liaoyin-tui", 1))
                return notify_fail("��Ļ���ȭ�Ż���㣬�޷���������������ȡ�\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage=="unarmed" || usage=="parry";
}

string query_skill_name(int lvl)
{
        return action[random(sizeof(action))]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if( (int)me->query("qi") < 100 )
                return notify_fail("����������������Ϣһ�������ɡ�\n");

        if( (int)me->query("neili") < 80 )
                return notify_fail("������������ˡ�\n");

        me->receive_damage("qi", 80);
        me->add("neili", -50);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liaoyin-tui/" + action;
}

