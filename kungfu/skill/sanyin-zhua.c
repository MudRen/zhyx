//sanyin-zhua.c �������ץ
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([  "action" : "$Nצ����ף��ǽ�¡�����϶���˺��$n��$l",
    "force" : 120,
    "dodge" : 10,
    "damage": 30,
    "damage_type" : "ץ��"
]),
([  "action" : "$N˫�ֺ������֣�צצ���Ȱ�ץ��$n��$l",
    "force" : 150,
    "dodge" : 20,
    "damage": 45,
    "lvl"   : 30,
    "damage_type" : "ץ��"
]),
([  "action" : "$N����Χ$nһת��צӰ�ݺ�����������$n��$lץ��",
    "force" : 180,
    "dodge" : 30,
    "damage": 55,
    "lvl"   : 60,
    "damage_type" : "ץ��"
]),
([  "action" : "$Nһ���ֽУ�һצ���ֱ��$n��$l",
    "force" : 240,
    "dodge" : 50,
    "damage": 60,
    "lvl"   : 90,
    "skill_name" : "Ψ�Ҷ���" ,
    "damage_type" : "ץ��"
]),
([  "action" : "$N����а������������ƮƮ����������̽��һצ��Ȼ����$n��$l",
    "force" : 270,
    "dodge" : 60,
    "damage": 90,
    "lvl"   : 120,
    "skill_name" : "Ψ�Ҷ���" ,
    "damage_type" : "ץ��"
]),
});

int valid_enable(string usage) { return usage == "claw" ||  usage == "parry"; }

int valid_combine(string combo) { return combo == "chousui-zhang"; }

int valid_learn(object me)
{
        
        int  nb,  nh;
        nb = (int)me->query_skill("poison", 1);
        nh = (int)me->query_skill("sanyin-zhua", 1);

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���������צ������֡�\n");
                
        if ((int)me->query_skill("huagong-dafa", 1) < 10)
                return notify_fail("��Ļ����󷨻�򲻹����޷�ѧ�������צ��\n");
                
        if ( nb < 100 && nb <= nh )
                return notify_fail("��Ķ�����Ϊ�������޷�����������צ��\n");

        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������̫�����޷����������צ��\n");
        return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action); i > 0; i--)
		if (level >= action[i - 1]["lvl"])
			return action[i - 1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
        level = (int) me->query_skill("sanyin-zhua", 1);
	for(i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 5, level / 5)];

}

int practice_skill(object me)
{
        int  nb,  nh; 
        nb = (int)me->query_skill("poison", 1); 
        nh = (int)me->query_skill("sanyin-zhua", 1); 

        if (nb < 100 && nb <= nh) 
                return notify_fail("��Ķ�����Ϊ�������޷�����������צ��\n"); 

        if ((int)me->query("qi") < 50)
                return notify_fail("�������̫���ˡ�\n");
                
        if ((int)me->query("neili") < 50)
                return notify_fail("��������������������צ��\n");
                
        me->receive_damage("qi", 40);
        me->add("neili", -40);
        
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("sanyin-zhua", 1);
        flvl = me->query("jiali");

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("xx_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id"    : me->query("id"),
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                return HIW "$n" HIW "ֻ��һ�󼫺����ĵ����𣬿���������$N" HIW "ץ�ϵľ綾��\n" NOR;
        }
}

string perform_action_file(string action)
{
	return __DIR__"sanyin-zhua/" + action;
}
