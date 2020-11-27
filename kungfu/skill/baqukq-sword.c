//By baqukq for 2004.08.28

#include <ansi.h>

inherit SKILL;

mapping *action = ({
	([	"name":			"����է��",
		"action":		"$Nʹһ��"HIR"��"BLINK+HIY"����է��"NOR+HIR"��"NOR"������$w����㴺������$n��$l��û����֪�������������Ҳ���޷��ֵ�",
              "parry":   -40,
              "dodge":   -40,
		"damage":		70,
		"damage_type":	"����"
	]),
	([	"name":			"ϸ������",
		"action":		"$N���е�$wһ��"HIR"��"BLINK+HIB"ϸ������"NOR+HIR"��"NOR"������ϸ�꣬�޿ײ���Ĵ���$n��$l",
              "parry":   -50,
              "dodge":   -50,
              "damage":               50,
		"damage_type":	"����"
	]),
	([	"name":			"���꽻��",
		"action":		"$N�趯$w��һ��"HIR"��"BLINK+HIG"���꽻��"NOR+HIR"��"NOR"����������������磬�˽���һ������$n��$l",
              "parry":   -60,
              "dodge":   -60,
              "damage":               100,
		"damage_type":	"����"
	]),
	([	"name":			"�������",
		"action":		"$Nһ������$w��ʹ��"HIR"��"BLINK+HIW"�������"NOR+HIR"��"NOR"�����ɵð������ˣ�����Ԧ������$n��$l�̳�һ��",
              "parry":   -70,
              "dodge":   -70,
              "damage":               60,
		"damage_type":	"����"
	]),
	([	"name":			"�������",
		"action":		"$N����$w������ɢ��һ��"HIR"��"BLINK+HIC"�������"NOR+HIR"��"NOR"���������ƣ�������$n��$l�����˲�֪�����Ժη�",
              "parry":   -80,
              "dodge":   -80,
              "damage":               90,
	        "damage_type":	"����"
	]),
	([	"name":			"��籩��",
		"action":		"$N�����������������������������$wֱָ$n$l��һ��"HIR"��"NOR+BLINK+MAG"��籩��"NOR+HIR"��"NOR"���̳��˾��춯�ص�һ��",
              "parry":   -90,
              "dodge":   -90,
		"damage":		50,
		"damage_type":	"����"
	]),
});

int valid_learn(object me)
{
	object ob;

	if( (int)me->query("max_neili") < 100 )
		return notify_fail("�������������û�а취�����콣����\n");

	if( !(ob = me->query_temp("weapon"))
	||	(string)ob->query("skill_type") != "sword" )
		return notify_fail("���������һ�ѽ�������������\n");

	return 1;
}

int valid_enable(string usage)
{
	return usage=="sword" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	if( (int)me->query("qi") < 30
	||	(int)me->query("neili") < 5 )
		return notify_fail("�����������������û�а취��ϰ���콣����\n");
	me->receive_damage("qi", 30);
	me->add("neili", -5);
	write("�㰴����ѧ����һ�����콣����\n");
	return 1;
}
int effective_level() { return 20;}
string *parry_msg = ({
        "$n���ƹ��У��ҽ�����һ��"HIG"���麣���ġ�"NOR"�����е�$v�ݺݿĿ���$N��$w��\n",
	"$n������������ס$N��$w��һ��"HIR"������ĺĺ��"NOR"��ʹ$N���԰ѳ����е�$w��\n",
});

string *unarmed_parry_msg = ({
        "$nʹ��һ��"HIG"�������¶��"NOR"�������๥����ʹ$N��֪�ǹ����ء�\n",
	"$nһ�����е�$v��ʹ��һ��"HIG"���������á�"NOR"�����е�$v������ƣ���ȫ��������ס��\n",
	
});

string query_parry_msg(object weapon)
{
        if( weapon )
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

int learn_bonus()
{
	return 0;
}
int practice_bonus()
{
	return -100;
}
int black_white_ness()
{
	return -10;
}

string perform_action_file(string action)
{
        return __DIR__"baqukq-sword/" + action;
}


