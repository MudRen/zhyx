#include <ansi.h>
#include <skill.h>

inherit SKILL;

string *xue_name = ({ 
"�͹�Ѩ", "����Ѩ", "����Ѩ", "��ԪѨ", "����Ѩ", "�м�Ѩ", "�н�Ѩ", "��ͻѨ", "�ٻ�Ѩ",
"����Ѩ", "����Ѩ", "���Ѩ", "�Ϲ�Ѩ", "��ԨѨ", "�쾮Ѩ", "��ȪѨ", "����Ѩ", "����Ѩ", }); 

mapping *action_finger = ({
([      "action" : "$N����ʳָ΢�㣬���С������������һ���ۻ��һ��ָ������$n�����ֳ��ȣ���������",
        "force" : 350,
        "attack": 100,
        "dodge" : 75,
        "parry" : 55,
        "damage": 100,
        "lvl" : 0,
        "weapon" : HIR "һ��ָ��" NOR,
        "skill_name" : "�������",
        "damage_type" : "����"
]),
([      "action" : "$Nһָ���ճ�ϼ�⡹��������һ�����ӿ��$n���������´�ƽ�ͣ�����Ȼ����޿��뿹",
        "force" : 370,
        "attack": 110,
        "dodge" : 85,
        "parry" : 65,
        "damage": 110,
        "lvl" : 20,
        "weapon" : HIR "һ��ָ��" NOR,
        "skill_name" : "�ճ�ϼ��",
        "damage_type" : "����"
]),
([      "action" : "�����������죬һ����͵�������$N��ָӿ��������һ�С�����ů�ڡ�����������$n$l",
        "force" : 410,
        "attack": 120,
        "dodge" : 95,
        "parry" : 75,
        "damage": 120,
        "lvl" : 40,
        "weapon" : HIR "һ��ָ��" NOR,
        "skill_name" : "����ů��",
        "damage_type" : "����"
]),
([      "action": "$Nһ���絽$n�������������Ծ�أ�һʽ��³�����ա�������ʳָ������ָ��$n��$l",
        "force" : 430,
        "attack": 130,
        "dodge" : 105,
        "parry" : 85,
        "damage": 130,
        "lvl" : 60,
        "weapon" : HIR "һ��ָ��" NOR,
        "skill_name" : "³������",
        "damage_type" : "����"
]),
([      "action": "$N�����������ʳָЮ���ۻ���������$n��$l����ʽ����̹��������һʽ��������ѩ��",
        "force" : 460,
        "attack": 140,
        "dodge" : 115,
        "parry" : 95,
        "damage": 140,
        "lvl" : 80,
        "weapon" : HIR "һ��ָ��" NOR,
        "skill_name" : "������ѩ",
        "damage_type" : "����"
]),
([      "action": "$N��ӰƮ��һʽ���������졹���������϶���������������Ȼ������$n��$l",
        "force" : 490,
        "attack": 150,
        "dodge" : 125,
        "parry" : 105,
        "damage": 150,
        "lvl" : 100,
        "weapon" : HIR "һ��ָ��" NOR,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([      "action" : "$N̤ǰһ������ָ�������һ�㣬$nֻ����Ϣһ�����ѱ������ս������ĸ�����������$l",
        "force" : 500,
        "attack": 160,
        "dodge" : 135,
        "parry" : 115,
        "damage": 160,
        "lvl" : 120,
        "weapon" : HIR "һ��ָ��" NOR,
        "skill_name" : "���ս���",
        "damage_type" : "����"
]),
([      "action" : "$N������ڣ������������׻ӳ���ӿ��$n��$l���������������һ�С�������ů��",
        "force" : 520,
        "attack": 170,
        "dodge" : 145,
        "parry" : 125,
        "damage": 170,
        "lvl" : 140,
        "weapon" : HIR "һ��ָ��" NOR,
        "skill_name" : "������ů",
        "damage_type" : "����"
]),
([      "action" : "$N���΢Ц�����ʳָ����$n�ؿڣ����С�ĺ��ӳ�ա�����������ȴ��˿���ƿ�֮��",
        "force" : 540,
        "attack": 180,
        "dodge" : 155,
        "parry" : 135,
        "damage": 180,
        "lvl" : 160,
        "weapon" : HIR "һ��ָ��" NOR,
        "skill_name" : "ĺ��ӳ��",
        "damage_type" : "����"
]),
([      "action": "$N����б����ͻȻ�����Ϊָ���͵�һʽ�����ﳯ������ʹ��һ��ָ��������$n��$l",
        "force" : 560,
        "attack": 180,
        "dodge" : 160,
        "parry" : 140,
        "damage": 190,
        "lvl" : 180,
        "weapon" : HIR "һ��ָ��" NOR,
        "skill_name" : "���ﳯ��",
        "damage_type" : "����"
]),
([      "action" : "$Nʳָ΢����һָ������Ǭ�������������ɭ�ϣ�Ӻ�����£�����֮�в������߷��",
        "force" : 570,
        "attack": 185,
        "dodge" : 160,
        "parry" : 140,
        "damage": 200,
        "lvl" : 200,
        "weapon" : HIR "һ��ָ��" NOR,
        "skill_name" : "����Ǭ��",
        "damage_type" : "����"
]),
([      "action" : "$Nͷ�������뵣����۽�Ũ����������һ�㣬ʳָ�����һʽ��������̩������$n$l",
        "force" : 590,
        "attack": 190,
        "dodge" : 165,
        "parry" : 145,
        "damage": 210,
        "lvl" : 220,
        "weapon" : HIR "һ��ָ��" NOR,
        "skill_name" : "������̩",
        "damage_type" : "����"
])
});


mapping *action_staff = ({
([      "action" : "$N�����Ц����$wƽ�أ���׼ʱ��һ�Ȼӳ����������������Ѹ���ޱȵ�ֱ��$n$l",
        "force" : 100,
        "dodge" : 15,
        "damage" : 50,
        "lvl" : 0,
        "damage_type" : "����",
]),
([      "action" : "$N��������Ⱦ������󴫶�����һ��ָ�񹦻���$w֮�ϣ��������أ�ƽƽ�����ش���$n",
        "force" : 150,
        "dodge" : -10,
        "damage" : 70,
        "lvl" : 20,
        "damage_type" : "����",
]),
([      "action" : "ֻ��$N��Ϣ���񣬽Ų����ţ����ߵ��ƣ�һʽ����������$n$l����ʽ��������",
        "force" : 200,
        "dodge" : 0,
        "damage" : 90,
        "lvl" : 40,
        "damage_type" : "����",
]),
([      "action" : "$N���²���΢�䣬�������ߣ��������ص�һ����$n������������ȴҲ��ʧ��������",
        "force" : 250,
        "dodge" : 10,
        "damage" : 120,
        "lvl" : 60,
        "damage_type" : "����",
]),
([      "action" : "$Nƽ��һ�ȣ����е�$w���ƽ������أ�ʹ��ʱ�Ա���ǰ��ɬ����ʵ�Ǿ������أ�����֮��",
        "force" : 300,
        "dodge" : -15,
        "damage" : 140,
        "lvl" : 80,
        "damage_type" : "����",
]),
});

int valid_enable(string usage) 
{  
	return usage == "finger" || usage == "parry" || usage == "staff"; 
}

int valid_learn(object me)
{
	if ((string)me->query("gender") == "Ů��" && (int)me->query_skill("yiyang-zhi", 1) > 300 ) 
        	return notify_fail("һ��ָ���Ǵ����������㲻�ʺ���������ȥ��\n");

        if ((int)me->query("con") < 34)
                return notify_fail("����������Ƿ�ѣ��޷�����һ��ָ��\n");

        if ((int)me->query("int") < 32)
                return notify_fail("����������Բ��㣬�޷����һ��ָ��\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("��һ��ָ������֡�\n");

        if ((int)me->query_skill("force") < 240)
                return notify_fail("����ڹ���򲻹����޷�ѧһ��ָ��\n");

        if ((int)me->query("max_neili") < 2000)
                return notify_fail("�������̫�����޷���һ��ָ��\n");

        if ((int)me->query_skill("finger", 1) < 150)
                return notify_fail("��Ļ���ָ����򲻹����޷�ѧһ��ָ��\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("yiyang-zhi", 1))
                return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷����������һ��ָ��\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action_finger)-1; i >= 0; i--)
                if(level >= action_finger[i]["lvl"])
                        return action_finger[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("yiyang-zhi", 1);

        if ( ! weapon)
        {                
             for(i = sizeof(action_finger); i > 0; i--)
                     if(level >= action_finger[i-1]["lvl"])
                             return action_finger[NewRandom(i, 20, level/5)];
        }        
        else
             for(i = sizeof(action_staff); i > 0; i--)
                     if(level > action_staff[i-1]["lvl"])
                             return action_staff[NewRandom(i, 20, level/5)];        
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 70)
                return notify_fail("�������̫���ˡ�\n");

        if ((int)me->query("neili") < 120)
                return notify_fail("�������������һ��ָ!\n");

        me->receive_damage("qi", 60);
        me->add("neili", -100);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
      	string name, weapon;
      	name = xue_name[random(sizeof(xue_name))];

      	if (damage_bonus < 120)
            	return 0;

      	if (! objectp(weapon = me->query_temp("weapon")))
      	{
            	if (me->query("neili") > 300 && me->query_skill("yiyang-zhi", 1) > 100 && me->query_skill("jingluo-xue", 1) > 100)
            	{
		      	    if (! victim->is_busy())
	        	  	    victim->start_busy(2);          	
                  	victim->receive_wound("qi", (damage_bonus - 100) / 3, me);
			        if (victim->query("neili") <= (damage_bonus / 4 + 50))
	                	victim->set("neili", 0);
                  	else
                       	victim->add("neili", -damage_bonus / 4);
		              	return HIR "ֻ�����͡���һ����$n" HIR "��$N" HIR "���һָ����" NOR +
                                       HIY + name + NOR + HIR "���������ɵ�һ�͡�\n" NOR;
            	} 
      	} else
      	{
            	if (me->query("neili") > 300 && me->query_skill("yiyang-zhi", 1) > 100 && me->query_skill("jingluo-xue", 1) > 100)
	            {                	
                  	victim->receive_wound("qi", (damage_bonus - 100) / 4, me);
	                return HIR "ֻ�����͡���һ����$n" HIR "��$N" HIR "�ȶ˷�������������" NOR +
                               HIY + name + NOR +HIR "���������ɵ�һ�͡�\n" NOR;
            	}   
      	}
 
}

string perform_action_file(string action)
{
      	return __DIR__"yiyang-zhi/" + action;
}