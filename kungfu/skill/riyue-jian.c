// riyue-jian.c ���½���

inherit SKILL;

mapping *action = ({
([      "action" : "$N����$w��������$n��",
        "force"  : 120,
        "dodge"  : 20,
        "damage" : 30,
        "lvl"    : 0,
        "damage_type": "����"
]),
([      "action" : "$Nһ������$w������бб����$n��$l��ȥ��",
        "force"  : 120,
        "dodge"  : 20,
        "damage" : 35,
        "lvl"    : 10,
        "damage_type": "����"
]),
([      "action" : "ֻ��$N����$w������㽣�⣬����һ�ߣ�����$n��������",
        "force"  : 140,
        "dodge"  : 15,
        "damage" : 40,
        "lvl"    : 10,
        "damage_type": "����"
]), 
([      "action" : "$N�鲽�������ὣ�ؽ��������ϱ���һ�С��������š�ֱȡ$n��$l",
        "force"  : 150,
        "dodge"  : 15,
        "damage" : 45,
        "lvl"    : 30,
        "damage_type": "����"
]),
([      "action" : "ֻ��$N�趯����$w,��һ�����벻���ĽǶ�ͻȻ����һ������$n��$lֱ�̡�",
        "force"  : 130,
        "dodge"  : 25,
        "damage" : 45,
        "lvl"    : 40,
        "damage_type": "����"
]),
([      "action" : "$N�ֱ���ǰһ�죬$w��$n���̹�ȥ��",
        "force"  : 120,
        "dodge"  : 25,
        "damage" : 50,
        "lvl"    : 50,
        "damage_type": "����"
]),
([      "action" : "$N����$w����$n��$l����һ����",
        "force"  : 110,
        "dodge"  : 15,
        "damage" : 70,
        "lvl"    : 60,
        "damage_type": "����"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
    object ob;

    if ((int)me->query("max_neili") < 100)
        return notify_fail("�������������\n");

    if ((int)me->query_skill("force") < 20)
        return notify_fail("����ڹ����̫ǳ��\n");

    if (!objectp(ob = me->query_temp("weapon")) 
       || (string)ob->query("skill_type") != "sword") 
        return notify_fail("���������һ�ѽ�����ѧϰ������\n"); 

    if ((int)me->query_skill("sword", 1) < (int)me->query_skill("riyue-jian", 1))
        return notify_fail("��Ļ�������ˮƽ���ޣ��޷�������������½�����\n");

    return 1;
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level = (int) me->query_skill("riyue-jian", 1);
    for (i = sizeof(action); i > 0; i--)
        if (level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level / 5)];

}

int practice_skill(object me)
{
    object weapon;

    if (! objectp(weapon = me->query_temp("weapon")) ||
       (string)weapon->query("skill_type") != "sword")
          return notify_fail("��ʹ�õ��������ԡ�\n");

    if ((int)me->query("qi") < 40)
          return notify_fail("����������������½�����\n");

    if ((int)me->query("neili") < 10)
          return notify_fail("����������������½�����\n");

    me->receive_damage("qi", 25);
    me->add("neili", -10);

    return 1;
}

