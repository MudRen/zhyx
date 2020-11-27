#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$Nһ�С����¶��ġ���$w���������һ���󻡣�����$n��$l",
        "force"  : 150,
        "attack" : 100,
        "dodge"  : 90,
        "parry"  : 90,
        "damage" : 100,
        "lvl"    : 40,
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С�С԰�վա�������$wѸ����$n��������������",
        "attack" : 120,
        "force"  : 180,
        "dodge"  : 100,
        "parry"  : 100,
        "damage" : 110,
        "lvl"    : 54,
        "damage_type" : "����"
]),
([      "action" : "$Nʹ��������ҹ����������$w�й�ֱ�룬����$n��$l",
        "force"  : 200,
        "attack" : 140,
        "dodge"  : 110,
        "parry"  : 100,
        "damage" : 120,
        "lvl"    : 59,
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С������չȡ���$w���������һ�ӣ���$n����˼��ĽǶȹ���",
        "force"  : 240,
        "attack" : 150,
        "dodge"  : 120,
        "parry"  : 110,
        "damage" : 130,
        "lvl"    : 94,
        "damage_type" : "����"
]),
([      "action" : "$N���Ų�������$wͻȻ���Լ������´̳���ȴ��һ�С����Ľ�����",
        "force"  : 280,
        "attack" : 160,
        "dodge"  : 120,
        "parry"  : 120,
        "damage" : 140,
        "lvl"    : 112,
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С��������������$w�̵�$n������",
        "force"  : 300,
        "attack" : 160,
        "dodge"  : 130,
        "parry"  : 120,
        "damage" : 150,
        "lvl"    : 124,
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С�ĵ�����᡹��$w�Ƴ�������Ȧ��ƽƽ����$n��$l��ȥ",
        "force"  : 340,
        "attack" : 170,
        "dodge"  : 140,
        "parry"  : 120,
        "damage" : 160,
        "lvl"    : 131,
        "damage_type" : "����"
]),
([      "action" : "$N������Ȼ֮ɫ������һ�С�����Բԡ���$w����$n��$l",
        "force"  : 380,
        "attack" : 180,
        "dodge"  : 160,
        "parry"  : 140,
        "damage" : 200,
        "lvl"    : 178,
        "damage_type" : "����"
]),
});

int valid_enable(string usage) 
{ 
        return usage == "sword" || usage == "parry"; 
}

int valid_learn(object me)
{
        object weapon;


        /*if ((int)me->query("str", 1) < 28)
                return notify_fail("�����������������޷�ѧϰ��Ů���Ľ���\n");*/

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻵����޷�ѧϰ��Ů���Ľ���\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("��Ļ�������ˮƽ̫�ͣ��޷�ѧϰ��Ů���Ľ���\n");

        if (me->query("max_neili") < 2000)
                return notify_fail("���������Ϊ����������ѧϰ��Ů���Ľ���\n");

        if (me->query_skill("sword", 1) < me->query_skill("suxin-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷������������Ů���Ľ���\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;  
        level = (int) me->query_skill("suxin-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

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
			|| random(5) < 2 )
                return 0;

        if ((string)weapon->query("skill_type") == "sword"
            && me->query_skill_mapped("sword") == "suxin-jian")
        {
                damage_bonus = lvl / 2 + random(lvl / 2);

                victim->receive_damage("qi", damage_bonus, me);
                victim->receive_wound("qi", damage_bonus * 2 / 3, me);
				return HIW ""+ me->name() + HIW "����" + wn + HIW "����һ�񣬽���"
                       "Ů�ľ��������ڽ��ˣ���Ů�������ӵ����쾡�¡�\n" NOR; 
                
        }
}

int practice_skill(object me)
{
        object weapon;
		int cost;

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

		cost = me->query_skill("suxin-jian", 1) / 3 + 40;

        if ((int)me->query("qi") < 75)
                return notify_fail("���������������Ů���Ľ���\n");

        if ((int)me->query("neili") < cost)
                return notify_fail("�����������������Ů���Ľ���\n");		 

        me->receive_damage("qi", 60);
        me->add("neili", -cost);

        return 1;
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


string perform_action_file(string action)
{
        return __DIR__"suxin-jian/" + action;
}
