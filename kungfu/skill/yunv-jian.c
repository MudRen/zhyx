//updated by kasumi

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$Nһ�С����¶��ġ���$w���������һ���󻡣�����$n��$l",
        "force"  : 200,
        "attack" : 100,
        "dodge"  : 90,
        "parry"  : 70,
        "damage" : 100,
        "lvl"    : 0,
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С�С԰�վա�������$wѸ����$n��������������",
        "attack" : 120,
        "force"  : 240,
        "dodge"  : 100,
        "parry"  : 75,
        "damage" : 110,
        "lvl"    : 40,
        "damage_type" : "����"
]),
([      "action" : "$Nʹ��������ҹ����������$w�й�ֱ�룬����$n��$l",
        "force"  : 280,
        "attack" : 140,
        "dodge"  : 110,
        "parry"  : 80,
        "damage" : 120,
        "lvl"    : 80,
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С������չȡ���$w���������һ�ӣ���$n����˼��ĽǶȹ���",
        "force"  : 300,
        "attack" : 150,
        "dodge"  : 120,
        "parry"  : 85,
        "damage" : 130,
        "lvl"    : 100,
        "damage_type" : "����"
]),
([      "action" : "$N���Ų�������$wͻȻ���Լ������´̳���ȴ��һ�С����Ľ�����",
        "force"  : 320,
        "attack" : 160,
        "dodge"  : 130,
        "parry"  :90,
        "damage" : 140,
        "lvl"    : 120,
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С��������������$w�̵�$n������",
        "force"  : 340,
        "attack" : 170,
        "dodge"  : 140,
        "parry"  : 95,
        "damage" : 150,
        "lvl"    : 160,
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С�ĵ�����᡹��$w�Ƴ�������Ȧ��ƽƽ����$n��$l��ȥ",
        "force"  : 360,
        "attack" : 180,
        "dodge"  : 150,
        "parry"  : 100,
        "damage" : 160,
        "lvl"    : 200,
        "damage_type" : "����"
]),
([      "action" : "$N������Ȼ֮ɫ������һ�С�����Բԡ���$w����$n��$l",
        "force"  : 380,
        "attack" : 190,
        "dodge"  : 160,
        "parry"  : 105,
        "damage" : 200,
        "lvl"    : 220,
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

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
				
	     if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���򲻵����޷�ѧϰ��Ů������\n");
				
		if (me->query("max_neili") < 1500)
                return notify_fail("���������Ϊ����������ѧϰ��Ů������\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("��Ļ�������ˮƽ̫�ͣ��޷�ѧϰ��Ů������\n");

        if (me->query_skill("sword", 1) < me->query_skill("yunv-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷������������Ů������\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;  
        level = (int) me->query_skill("yunv-jian", 1);
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
            || me->query_skill_mapped("parry") != "quanzhen-jian"
			|| me->query_skill_mapped("force") != "yunv-xinjing"
			|| random(5) < 2 
			|| me->query_skill("zuoyou-hubo", 1) < 200)
                return 0;

        if ((string)weapon->query("skill_type") == "sword"
            && me->query_skill_mapped("sword") == "yunv-jian")
            {               
                victim->receive_wound("qi", (damage_bonus - 100) / 3, me);
				return HIG ""+ me->name() + HIG "����˫������" +victim->name()+ HIG"����Ѫ"
                       "��"HIW"���콣��"HIG"��Ʈ����\n" NOR;              
            }
}


mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp;
        object m_weapon;

        if ((int) me->query_skill("yunv-jian", 1) < 180
		   || me->query("neili") < 300
           || ! (m_weapon = me->query_temp("weapon"))
		   || me->query_skill_mapped("sword") != "quanzhen-jian"
		   || me->query_skill_mapped("force") != "yunv-xinjing"
		   || me->query_skill("zuoyou-hubo", 1) < 200
           || ! living(me) 
           )
                return;
        
        ap = ob->query_skill("dodge",1);
        dp = (me->query_skill("quanzhen-jian", 1) + me->query_skill("yunv-jian", 1))/2;       
             if (ap / 2 + random(ap) < dp * 3 / 4)
             {
                        result = ([ "damage": -damage ]);
                        result += (["msg" : HIM "$n" HIM "����˫�����裬��ʽ������"
                                           "������Ϊ��һ����ȥ ��\n" NOR]);            
                        
             }             
             return result;
             
}

int practice_skill(object me)
{
        object weapon;
		int cost;

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

		cost = me->query_skill("yunv-jian", 1) / 3 + 40;

        if ((int)me->query("qi") < 80)
                return notify_fail("���������������Ů������\n");

        if ((int)me->query("neili") < cost)
                return notify_fail("�����������������Ů������\n");		 

        me->receive_damage("qi", 60);
        me->add("neili", -cost);

        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"yunv-jian/" + action;
}
