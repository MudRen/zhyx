//updated bu kasumi

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([      "action": "$N���е�$w����������󽭶�ȥ�������Ʋ��ɵ�",
        "force" : 350,
        "attack": 170,
        "dodge" : 30,
        "parry" : 70,
        "damage": 250,
        "lvl"   : 0,
        "damage_type": "����"
]),
([      "action": "$N̤��һ��������$w���һ����������$n��$l",
        "force" : 400,
        "attack": 280,
        "dodge" : 33,
        "parry" : 79,
        "damage": 280,
        "lvl"   : 40,
        "damage_type": "����"
]),
([      "action": "$N����$wһ����һ���̳�������$n��$l��û�а�㻨��",
        "force" : 450,
        "attack": 290,
        "dodge" : 41,
        "parry" : 85,
        "damage": 310,
        "lvl"   : 80,
        "damage_type": "����"
]),
([      "action": "$N����$w΢΢��������Ȼ�̳���һ����������$n��$l",
        "force" : 500,
        "attack": 295,
        "dodge" : 45,
        "parry" : 92,
        "damage": 340,
        "lvl"   : 120,
        "damage_type": "����"
]),
([      "action": "$N���$w����Ȼ��ɨ$n��������磬�����س�",
        "force" : 550,
        "attack": 297,
        "dodge" : 47,
        "parry" : 99,
        "damage": 370,
        "lvl"   : 160,
        "damage_type": "����"
]),
([      "action": "$N���е�$w�������̣��д���һ�������ӹ�$nȫ��",
        "force" : 600,
        "attack": 300,
        "dodge" : 50,
        "parry" : 100,
        "damage": 400,
        "lvl"   : 200,
        "damage_type": "����"
])
});

int valid_enable(string usage)
{
	return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        if (me->query("int") < 13)
                return notify_fail("�����������̫��޷��������������\n");

        if (me->query("str") < 36)
                return notify_fail("������������������޷�ѧϰ����������\n");

         if (me->query("dex") < 34)
                return notify_fail("����������������޷�ѧϰ����������\n");

        if (me->query("character") == "�ĺ�����")
                return notify_fail("��һ����ɱ�����ˣ�û��������������ĵ��������塣\n");

        if (me->query("character") == "���ռ�թ")
                return notify_fail("��һ������ôѧ�ý���ȥ���ˣ����û���������������\n");

        if ((int)me->query_skill("force") < 330)
                return notify_fail("����ڹ���򲻵����޷�ѧϰ����������\n");

        if (me->query_skill("martial-cognize", 1) < 220)
                return notify_fail("����ѧ�������㣬�޷���������������\n");

        if (me->query("max_neili") < 5000)
                return notify_fail("�������̫��޷�ѧϰ����������\n");

        if (me->query_skill("force", 1) < me->query_skill("xuantie-jian", 1))
                return notify_fail("��Ļ����ڹ�ˮƽ���ޣ��޷��������������������\n");

        if (me->query_skill("sword", 1) < me->query_skill("xuantie-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷��������������������\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("xuantie-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;
        object env;
        
        int level, cost;
        level = (int) me->query_skill("xuantie-jian", 1);

        if ( level > 400 ) cost = level/3 + 100;
                     else  cost = level/3 + 50;

        if (level<200)
        {
        env = environment(me);
        if (! env->query("can_practice_xiantie-jian"))
                return notify_fail("�����𽣻����˰��죬ֻ���ô˴����ʺ���ϰ����������\n");
       
        if (!objectp(weapon = me->query_temp("weapon")) || 
            (string)weapon->query("skill_type") != "sword" ||
            weapon->query("id") != "xuantie jian")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        }

        if ((int)me->query("qi") < 100)
                return notify_fail("�����������������������\n");

        
        if (!objectp(weapon = me->query_temp("weapon")) || 
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("neili") < 100)
                return notify_fail("�����������������������\n");

        me->receive_damage("qi", 80);
        me->add("neili", -cost);

        //message_vision(HIW "$N" HIW"������Ϣ�����������е�"+ weapon->name() + HIW "������������࿹��\n", me);

        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        object weapon = me->query_temp("weapon");

        lvl = me->query_skill("xuantie-jian", 1);
		if (damage_bonus < 100 || lvl < 250 ) return 0;

         if (damage_bonus / 4 > victim->query_str()) 
        {               
            victim->receive_wound("qi", (damage_bonus - 100) / 2, me);
            return HIW "$N" HIW "����" + weapon->name() + HIW "����������������£�����"
                       "�ɵ�������$n" HIW "�����ƻֺ�֮����\n" NOR;
         }
}

int difficult_level()
{
        return 300;
}

string perform_action_file(string action)
{
        return __DIR__"xuantie-jian/" + action;
}
