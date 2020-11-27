

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": HIW "$N���һ����һ�С���å���С�������$wƽ�պ�ɨ��һ����������$n��$l" NOR,
        "force" : 25,
        "dodge" : 20,
        "parry" : 25,
        "lvl"   : 0,
        "damage_type" : "����"
]),
([      "action": HIW "$N��ǰ����һ��������$wʹ��һʽ���׽�����ֱ��$n��$l" NOR,
        "force" : 30,
        "dodge" : 25,
        "parry" : 30,
        "lvl"   : 6,
        "damage_type" : "����"
]),
([      "action": HIW "$N��������һ�죬����$wʹ��һʽ�����Ľ�������$n��$l" NOR,
        "force" : 30,
        "dodge" : 35,
        "parry" : 35,
        "lvl"   : 12,
        "damage_type" : "����"
]),
([      "action": HIW "$N˫ϥ�³�������$wʹ��һʽ������ʽ�������¶��ϼ���$n��$l" NOR,
        "force" : 35,
        "dodge" : 35,
        "parry" : 40,
        "lvl"   : 15,
        "damage_type" : "����"
]),
([      "action": HIW "$Nһ�С����ֽ�����$w���϶��»���һ���󻡣�ƽƽ����$n��$l��ȥ" NOR,
        "force" : 35,
        "dodge" : 45,
        "parry" : 45,
        "lvl"   : 18,
        "damage_type" : "����"
]),
([      "action": HIW "$N���������һš��һ�С�������β��������$w������$n��$l��ȥ" NOR,
        "force" : 35,
        "dodge" : 45,
        "parry" : 55,
        "lvl"   : 21,
        "damage_type" : "����"
]),
([      "action": HIW "$Nһ�С�����ʽ��������ƽָ��һ���ǳɺ�ɨ$n��$l" NOR,
        "force" : 40,
        "dodge" : 60,
        "parry" : 55,
        "lvl"   : 24,
        "damage_type" : "����"
]),
([      "action": HIW "$N������ϥ������$wбָ��һ�С���Ŀʽ������$n��$l" NOR,
        "force" : 40,
        "dodge" : 55,
        "parry" : 60,
        "lvl"   : 27,
        "damage_type" : "����"
]),
([      "action": HIW "$Nһ�С�����ʽ����$w���¶��ϻ���һ���󻡣�ƽƽ�ػ���$n��$l" NOR,
        "force" : 45,
        "dodge" : 65,
        "parry" : 65,
        "lvl"   : 30,
        "damage_type" : "����"
]),
([      "action": HIW "$Nʹ��������ʽ����$w��������ԲȦ������ֱ�������಻�ϻ���$n��$l" NOR,
        "force" : 45,
        "dodge" : 70,
        "parry" : 70,
        "lvl"   : 35,
        "damage_type" : "����"
]),
([      "action": HIW "$Nһ�С����ʽ����$w����ػ�������Բ����Ѹ�ٵ���$n��$l��ȥ" NOR,
        "force" : 50,
        "dodge" : 75,
        "parry" : 80,
        "lvl"   : 40,
        "damage_type" : "����"
]),
([      "action": HIW "$Nһ�С���ͷʽ����$w����һ������ҸߵĴ󻡣�бб��ն��$n��$l" NOR,
        "force" : 50,
        "dodge" : 75,
        "parry" : 80,
        "lvl"   : 45,
        "damage_type" : "����"
]),
([      "action": HIW "$Nʹ������˿ʽ����$w�������󻮳�һ�����֣���$nȦ������" NOR,
        "force" : 55,
        "dodge" : 85,
        "parry" : 80,
        "lvl"   : 50,
        "damage_type" : "����"
]),
([      "action": HIW "$N���̤ʵ���ҽ���㣬һ�С�����ָ·��������$w����һ�Ž���������$n��$l" NOR,
        "force" : 55,
        "dodge" : 95,
        "parry" : 80,
        "lvl"   : 60,
        "damage_type" : "����"
]),
([  "action" : HIC "$N����š���������鱧��һ�С�����ͬ�𡹣�$w�й�ֱ��������$n��$l" NOR,
        "force" : 950,
        "attack": 1140,
        "dodge" : 2220,
        "parry" : 2220,
        "damage": 1140,
        "lvl" : 2500,
        "damage_type" : "����"
]),
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 1500)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("��Ļ����������̫ǳ��\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("liumang-sword", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        object m_weapon;

        if ((int) me->query_skill("liumang-sword", 1) < 100 ||
            ! (m_weapon = me->query_temp("weapon")) ||
            m_weapon->query("skill_type") != "sword")
                return;

        ap = ob->query_skill("force");
        dp = me->query_skill("sword", 1) / 2 +
             me->query_skill("liumang-sword", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "һ�����е�" + m_weapon->name() +
                                            HIC "��������һ��ԲȦ����Ȼ��$N" +
                                            HIC "�Ĺ���ȫȻ��ա�\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIC "$n" HIC "�ζ����е�" + m_weapon->name() +
                                            HIC "����ס�ı�ý��ƣ���$N"
                                            HIC "��ȫ�޷���׽��������\n" NOR]);
                        break;
                }
                return result;
        }
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        me->receive_damage("qi", 50);
        me->add("neili", -64);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liumang-sword/" + action;
}
