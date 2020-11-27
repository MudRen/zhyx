#include <ansi.h>
inherit SKILL;


mapping *action = ({
([      "action":"$Nʹһʽ��̽��������������$w�������Һ�ɨ����$n��$l",
        "force" : 170,
        "attack": 100,
        "dodge" : 100,
        "damage": 130,
        "lvl" : 0,
        "skill_name" : "̽������",
        "damage_type":  "����"
]),
([      "action":"$N����$wбָ���죬һʽ������Į��������׼$n��$lбб����",
        "force" : 200,
        "attack": 110,
        "dodge" : 120,
        "damage": 140,
        "lvl" : 80,
        "skill_name" : "����Į��",
        "damage_type":  "����"
]),
([      "action":"$Nһʽ�������仨�������󼱶�������������⣬����$n��$l",
        "force" : 220,
        "attack": 130,
        "dodge" : 130,
        "damage": 150,
        "lvl" : 100,
        "skill_name" : "�����仨",
        "damage_type":  "����"
]),
([      "action":"$N�ؽ����أ�ʹһʽ��������项���������$w��$n����",
        "force" : 300,
        "attack": 140,
        "dodge" : 120,
        "damage": 160,
        "lvl" : 180,
        "skill_name" : "�������",
        "damage_type":  "����"
]),
([      "action":"$N��������һʽ�������߶�����$w�Ӳ���˼��ĽǶȴ���$n",
        "force" : 340,
        "attack": 150,
        "dodge" : 130,
        "damage": 170,
        "lvl" : 200,
        "skill_name" : "�����߶�",
        "damage_type":  "����"
]),
([      "action":"$Nһʽ���ϵ紩�ơ���$wͻȻ���������һƬ���Χ��$nȫ��",
        "force" : 380,
        "attack": 160,
        "dodge" : 140,
        "damage": 180,
        "lvl" : 220,
        "skill_name" : "�ϵ紩��",
        "damage_type":  "����"
])
});

int valid_enable(string usage)
{
	return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ�����㣬�޷�ѧϰȫ�潣����\n");

        if (me->query("max_neili") < 1000)
                return notify_fail("���������Ϊ̫��޷�ѧϰȫ�潣����\n");

        if (me->query_skill("sword", 1) < 100)
                return notify_fail("��Ļ���������Ϊ�������޷�ѧϰȫ�潣����\n");

        if (me->query_skill("sword", 1) < me->query_skill("quanzhen-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������ȫ�潣����\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("quanzhen-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
	    string wn;
		object weapon;
		int lvl;

		weapon = me->query_temp("weapon");
		wn = weapon->name();
		lvl = me->query_skill("yunv-xinjing", 1);

        if (lvl < 150
            || me->query("neili") < 300
            || ! objectp(weapon = me->query_temp("weapon"))            
            || ! me->query("can_learn/yunv-xinjing/wall")
			|| random(5) < 1 )
                return 0;

        if ((string)weapon->query("skill_type") == "sword"
            && me->query_skill_mapped("sword") == "quanzhen-jian")
        {
                damage_bonus = lvl + random(lvl / 2 );

                victim->receive_damage("qi", damage_bonus, me);
                victim->receive_wound("qi", damage_bonus * 2 / 3, me);
				return HIG ""+ me->name() + HIG "����" + wn + HIG "����һ�񣬽���"
                       "Ů�ľ��������ڽ��ˣ�ȫ�潣�����ӵ����쾡�¡�\n" NOR; 
                
        }
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp;
        object weapon1, weapon2;

        if (me->query_skill_mapped("sword") == "suxin-jian" && me->query_skill_mapped("parry") != "quanzhen-jian")
		return;
		
		if (me->query_skill_mapped("sword") == "quanzhen-jian" && me->query_skill_mapped("parry") != "suxin-jian")
		return;
		
		if (!(weapon1 = me->query_temp("weapon"))
           ||!( weapon2 = me->query_temp("handing"))
           || ! living(me))
        return;
        
        ap = ob->query_skill("parry");
        dp = me->query_skill("parry", 1) / 2 + (me->query_skill("quanzhen-jian", 1) + me->query_skill("suxin-jian", 1))/2;       
             if (ap / 2 + random(ap) < dp)
             {
                        result = ([ "damage": -damage ]);
                        result += (["msg" : MAG "$n" MAG "˫���׷ɣ���ʽ������������Ϊ��һ����ȥ���ܿ���$N" MAG "�Ĺ��ơ�\n" NOR]);                                           
                       
             }             
             return result;
             
}


int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 60)
                return notify_fail("�������������ȫ�潣����\n");

        if ((int)me->query("neili") < 60)
                return notify_fail("�������������ȫ�潣����\n");

        me->receive_damage("qi", 55);
        me->add("neili", -53);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"quanzhen-jian/" + action;
}
