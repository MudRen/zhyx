#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N����һ�ζ�����һ�С�С���꡹��˫�ƴ���һ���ȷ�����$n��ǰ��",
        "force" : 400,
        "attack": 125,
        "dodge" : 115,
        "parry" : 120,
        "damage": 110,
        "lvl"   : 10,
        "damage_type" : "����"
]),
([      "action" : "$N���λ���һ����������$n��ת��һ�С������ֻ֡���˫�ƻó�������Ӱ����$n",
        "force" : 430,
        "attack": 130,
        "dodge" : 110,
        "parry" : 115,
        "damage": 120,
        "lvl"   : 30,
        "damage_type" : "����"
]),
([      "action" : "$N�ֽ�һ����һ�С�����ŭ�š���˫������ǵذ�����$n��$l",
        "force" : 460,
        "attack": 145,
        "dodge" : 120,
        "parry" : 120,
        "damage": 125,
        "lvl"   : 60,
        "damage_type" : "����"
]),
([      "action" : "$Nһ�ա�������硹��˫���ĳ��������磬��Ȼ����������Ϣ������$n��$l",
        "force" : 480,
        "attack": 150,
        "dodge" : 120,
        "parry" : 130,
        "damage": 130,
        "lvl"   : 80,
        "damage_type" : "����"
]),
([      "action" : "$N���һ����һ�С�������š���������޸���ɽ����һ���ȷ�������$n������",
        "force" : 510,
        "attack": 165,
        "dodge" : 125,
        "parry" : 120,
        "damage": 135,
        "lvl"   : 100,
        "damage_type" : "����"
]),
([      "action" : "$Nһ����Ц��һ�С����߾�ת��������һ��������һ�������ĳ����ֱ������޹ǣ��Ƶ���;����\n"
                   "��ű䣬����Ȱ�ӡ��$n��$l",
        "force" : 520,
        "attack": 195,
        "dodge" : 125,
        "parry" : 125,
        "damage": 145,
        "lvl"   : 120,
        "damage_type" : "����"
]),
([      "action" : "$N������ǰ��һ�С��ظ����硹��˫�������ĳ���һ���Ƴ��ǵĺ���������͸������$n��Χ�Ŀ�\n"
                   "����������",
        "force" : 540,
        "attack": 210,
        "dodge" : 130,
        "parry" : 130,
        "damage": 160,
        "lvl"   : 140,
        "damage_type" : "����"
]),
([      "action" : "$N����һ�������κ����������򣬷���ײ��$n��һ�С��Ʒ��´̡������罣��ֱ��$n������",
        "force" : 560,
        "attack": 235,
        "dodge" : 130,
        "parry" : 135,
        "damage": 175,
        "lvl"   : 160,
        "damage_type" : "����"
]),
([      "action" : "$Nһ���������������𣬰����һʽ��������β�������ֻ���$n��$l",
        "force" : 580,
        "attack": 250,
        "dodge" : 130,
        "parry" : 175,
        "damage": 190,
        "lvl"   : 180,
        "damage_type" : "����"
]),
([      "action" : "$N���һ���������嶾�񹦣�һ�С����������ɲ�Ǽ�ȫ��ë�����̣�һ�Ա��̵�˫צ�����ĳ�\n"
                   "$n��$lץȥ",
        "force" : 600,
        "attack": 285,
        "dodge" : 140,
        "parry" : 180,
        "damage": 220,
        "lvl"   : 200,
        "damage_type" : "ץ��"
])
});

int valid_enable(string usage)
{
        return usage=="hand" || usage=="parry";
}

int valid_learn(object me)
{

        if (me->query("character") == "��������")
                return notify_fail("�����а��룺��Ϊ�˹������䣬����ѧϰ���ֺ����书��\n");

        if (me->query("character") == "������")
                return notify_fail("�����а��룺�ߣ������书��Ȼ���������������𺦼���ѧ�����ã�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("��ǧ�����ֱ�����֡�\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹����޷���ϰǧ�����֡�\n");

        if ((int)me->query("max_neili") < 1000)
                return notify_fail("�������̫�����޷���ϰǧ�����֡�\n");

        if ((int)me->query_skill("hand", 1) < 80)
                return notify_fail("��Ļ����ַ���򲻹����޷���ǧ�����֡�\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("qianzhu-wandushou", 1))
                return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷����������ǧ�����֡�\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("qianzhu-wandushou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{	
	if (damage_bonus < 100 || random(3)==1) return 0;		

        if ((damage_bonus / 5 > victim->query_con()) )
        {
                victim->receive_wound("qi", (damage_bonus - 80) / 3, me);
                return HIB "$n" HIB "��Ȼ�е�һ��Ī���Ķ��ģ��������ģ�ȫ���ʱ̱��\n" NOR;
        }        
}

int practice_skill(object me)
{
	   if (me->query_skill("qianzhu-wandushou", 1) < 180)
        return notify_fail("ǧ�����ֵȼ�������ֻ��ͨ����ȡ����Ķ�����������ߡ�\n");
        
        if ((int)me->query("qi") < 100)
                return notify_fail("�������̫���ˣ�������ϰǧ�����֡�\n");

        if ((int)me->query("neili") < 120)
                return notify_fail("������������ˣ��޷���ϰǧ�����֡�\n");

        me->receive_damage("qi", 100);
        me->add("neili", -120);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qianzhu-wandushou/" + action;
}
