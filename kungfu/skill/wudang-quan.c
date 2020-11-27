// wudang-quan.c �䵱��ȭ
// Modified by Lonely

inherit SKILL;

mapping *action = ({
([      "action" : "$N�����ұۣ�һ�С������֡���һȭֱ������$n��$l",
        "force" : 70,
        "dodge" : -10,
        "lvl" : 0,
        "skill_name" : "������",
        "damage_type" : "����"
]),
([      "action" : "$N����ǰ̽������籼$n��࣬һ�С����֡�����$n��$l��ȥ",
        "force" : 80,
        "dodge" : -15,
        "lvl" : 10,
        "skill_name" : "����",
        "damage_type" : "����"
]),
([      "action" : "$N˫��΢�������лζ���һ�С�һ���ޡ����д�������$n��$l",
        "force" : 100,
        "dodge" : -10,
        "lvl" : 20,
        "skill_name" : "һ����",
        "damage_type" : "����"
]),
([      "action" : "$N�����ȣ�������Σ�������ȭһʽ��ֱ����Ѹ�ʹ���$n���ؿ�",
        "force" : 120,
        "dodge" : -15,
        "lvl" : 40,
        "skill_name" : "ֱ��",
        "damage_type" : "����"
]),
([      "action" : "$Nʩ�������ͷ��������Ծ����У�˫��ͬʱ����$n��$l",
        "force" : 130,
        "dodge" : -20,
        "lvl" : 50,
        "skill_name" : "���ͷ",
        "damage_type" : "����"
]),
([      "action" : "$N˫�ۻػ�������΢΢������һ�С�������������$n��˫��",
        "force" : 180,
        "dodge" : -10,
        "lvl" : 60,
        "skill_name" : "����",
        "damage_type" : "����"
])
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }
int valid_combine(string combo) { return combo=="juehu-shou"; }
int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���䵱��ȭ������֡�\n");

	if ((int)me->query_skill("yinyun-ziqi", 1) < 10)
		return notify_fail("�����������򲻹����޷�ѧ�䵱��ȭ��\n");

	if ((int)me->query("max_neili") < 50)
		return notify_fail("�������̫�����޷����䵱��ȭ��\n");

	return 1;
}

string query_skill_name(int level)
{
	int i = sizeof(action);

	while (i--)
		if(level > action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        mapping a_action;
	int i, level;
	level   = (int) me->query_skill("wudang-quan",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
                {
                          a_action = action[NewRandom(i, 20, level/5)];
                          break;
                }
      a_action["dodge"]  += level / 10;
      a_action["parry"]  += level / 10;
      a_action["force"]  += level / 10;
      return a_action;
}

int practice_skill(object me)
{
	int lvl = me->query_skill("wudang-quan", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 30)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 10)
		return notify_fail("��������������䵱��ȭ��\n");
	me->receive_damage("jingli", 20);
	me->add("neili", -3);
	return 1;
}

int query_effect_parry(object attacker, object me) 
{
        int lvl;

        lvl = me->query_skill("wudang-quan", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
