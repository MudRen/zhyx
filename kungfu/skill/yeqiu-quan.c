// yeqiuquan.c Ұ��ȭ
// by xiner 09/3/2009

#include <ansi.h>
inherit SKILL;

string *msg = ({
"ֻ��$NһԾ���𣬴��һ����ʯͷ����׼$n�������˹�ȥ",
"$N����ʳָ��ָһ�֣���ȵ���������������ָͷ����$n��ȥ",
"$N�����󹭲�������һ�ţ���е���������һ����$n��ȥ",
});

string *usage_skills = ({ "unarmed", "finger", "hand", "cuff" });

int valid_enable(string usage)	{return (member_array(usage, usage_skills) != -1);}

//int valid_combine(string combo) { return combo=="sanshou"; }

mapping query_action(object me, object weapon)
{
	int lvl = me->query_skill("yeqiu-quan", 1);

	if (lvl > 500)
	{
		return ([
			"action" : msg[random(sizeof(msg))],
			"attack" : 200+random(lvl),
			"force"  : 200+random(lvl),
			"dodge"  : 200+random(200),
			"parry"  : 200+random(200),
			"damage" : 200+random(lvl),
			"damage_type" : "����",
			]);
	}else if (lvl > 250)
	{
		return ([
			"action" : msg[random(sizeof(msg))],
			"attack" : 10+random(lvl),
			"dodge"  : 10+random(lvl),
			"parry"  : 0,
			"force"  : 10+random(lvl),
			"damage" : 10+random(lvl),
			"damage_type" : "����",
			]);
	}else
	{
		return ([
			"action" : msg[random(sizeof(msg))],
			"attack" : 10,
			"dodge"  : 10,
			"parry"  :-10,
			"force"  : 10,
			"damage" : 10,
			"damage_type" : "����",
			]);
	}
}

int valid_learn(object me)
{
	int layer;
	if( me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��Ұ��ȭ������֡�\n");

        layer = (int)me->query_skill("yeqiu-quan", 1) / 50;

        if (layer > 10) layer = 10;

	if (layer * 30 > me->query_skill("literate", 1))
		return notify_fail("�����Ұ��ȭ��" + chinese_number(layer) +
			"�㾳��ʵ��������ޱȣ������Լ�����д��������������\n");

        return 1;
}

int difficult_level(object me) {return 2000;}

int practice_skill(object me)
{

        int i,level = me->query_skill("yeqiu-quan", 1);

	if(me->query_skill("yeqiu-quan", 1) < 100)
		return notify_fail("�����ڵ�Ұ��ȭ�ȼ��в�����������ϰ��\n");
	
	if (level<500)
	{
	        for (i = 0; i < sizeof(usage_skills); i++)
        	        if (me->query_skill(usage_skills[i], 1) < level)
                	        return notify_fail("���" + to_chinese(usage_skills[i]) + "����⻹"
                        	                   "�������޷����Ұ��ȭ�ĵȼ���\n");
		if( (int)me->query("jing") < 300)
			return notify_fail("��ľ����޷������ˣ���Ϣһ�������ɡ�\n");

		if( (int)me->query("qi") < 300 )
			return notify_fail("������̫���ˣ���Ϣһ�������ɡ�\n");

		if( (int)me->query("neili") < 10 )
			return notify_fail("������������ˡ�\n");

		me->receive_damage("jing", 250);
		me->receive_damage("qi", 250);
		me->add("neili", -10);
		return 1;
	}else
	{
		if (me->query_skill("finger", 1) < level &&
			me->query_skill("hand", 1) < level &&
			me->query_skill("cuff", 1) < level &&
			me->query_skill("unarmed", 1) < level)
		return notify_fail("��Ļ������ܵȼ�̫�Ͳ������Ұ��ȭ�ĵȼ���\n");

		if( (int)me->query("jing") < level*2)
			return notify_fail("��ľ����޷������ˣ���Ϣһ�������ɡ�\n");

		if( (int)me->query("qi") <level*2)
			return notify_fail("������̫���ˣ���Ϣһ�������ɡ�\n");

		if( (int)me->query("neili") < level*2)
			return notify_fail("������������ˡ�\n");

		me->receive_damage("jing", level*2);
		me->receive_damage("qi", level*2);
		me->add("neili", -level*2);
		return 1;
	}
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (me->query_skill("yeqiu-quan", 1) < 500) return 0;

	switch(random(3))
	{
	case 1:
	        if (random(me->query_int()) > victim->query_int() / 3)
        	{
			me->start_busy(1);
			victim->start_busy(1 + random(10));
			return HIR "$n" HIR "һʱ��ⲻ������$N"HIR"���У�ֻ���������ˡ�\n" NOR;
	        }
		break;

	case 2:
	        if (random(me->query_int()) > victim->query_int() / 3)
        	{
                	victim->receive_wound("jing", damage_bonus * 2/3, me);
		                return HIR "$n" HIR "��ȫ�²�͸$N"HIR"�Ĺ�����ͷ���ۻ�ƣ��Ӧ�ԡ�\n" NOR;
	        }
		break;

	default :
	        if (random(me->query_int()) > victim->query_int() / 3)
        	{
                	victim->receive_wound("qi", damage_bonus * 2, me);
		                return HIR "$n" HIR "���$N"HIR"��ͣ�任����������ȫ"
				"�޷�Ӧ�ԣ�������Ѫ���硣\n" NOR;
	        }
		break;
	}
}

string perform_action_file(string action)
{
	return __DIR__"yeqiu-quan/" + action;
}

void skill_improved(object me) 
{ 
	int lvl;
	int layer;
	lvl = me->query_skill("yeqiu-quan", 1);
        layer = (int)me->query_skill("yeqiu-quan", 1) / 50;
	if (layer > 10) layer = 10;

	if (! layer)
        {
                tell_object(me, HIM "���Ұ��ȭ�ȼ�����ˡ�\n" NOR);
	} else
	{
		if ((lvl % 50) == 0)
        	{
			tell_object(me, HIM "���Ұ��ȭ�Ѿ������ɵ��˵�" + chinese_number(layer) +
				"��ľ��硣\n" NOR);
			if (lvl > 250)
				me->set("title",HIG"Ұ��ȭ��ʦ"NOR);
        	} else
		tell_object(me, HIM "��Ե�" + chinese_number(layer) +
				"���Ұ��ȭ�ּ�����һ���˽⡣\n" NOR);
	}
}