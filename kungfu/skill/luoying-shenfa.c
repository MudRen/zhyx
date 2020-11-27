// Code of JHSH
// luoying-shenfa ��Ӣ��

#include <combat.h>
#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$n��ͷһ�ͣ�˫�����䣬������ǰ���Ƽ�����$N������ȥ������һ�С�����������$N��֮�£���������ͳͳ����$n��󣬾�����ա�\n",
        "dodge"  : 10,
        "skill_name" : "������"
]),
([      "action" : "$n���μ�����ʹ��һ�С������ڿա���������ͬΪ�������������Ʈ��һ�����࣬�ܹ�$N������\n",
        "dodge"  : 20,
        "skill_name" : "�����ڿ�"
]),
([      "action" : "$n����һ�ݣ�Ծ�ڰ�գ��ո����أ�һ�С��������㡱���ڿ�����������һ������������Ϣ������$N���\n",
        "dodge"  : 30,
        "skill_name" : "��������"
]),
([      "action" : "$n�ۼ����й�����ίʵ���޿ɱܣ���Ȼһ�С���Ͽ�ƶϡ������һ�������ţ�ȫ����ϥ�����ϣ�ƽƽ�۶ϣ�$N������ʱʧ��׼ͷ��ȫ�����ڿմ���\n",
        "dodge"  : 40,
        "skill_name" : "��Ͽ�ƶ�"
]),
([      "action" : "$n����������ʹ��һ�С�����������˫��չ���������������裬��̬Ʈ�ݣ�����$N������\n",
        "dodge"  : 50,
        "skill_name" : "��������"
]),
([      "action" : "$n��һ�䣬һʽ��������衱������$N���ƣ��������󣬵������ң�$N�俴�ƴ�ռ�Ϸ磬ȴ��һ���ܹ����С�\n",
        "dodge"  : 60,
        "skill_name" : "�������"
]),
([      "action" : "$nһ����Х�����ΰεض�������һ�С��������������ڿ���һ������ת�ۣ���ҡֱ�ϣ�Ѹ���������������������$N������\n",
        "dodge"  : 70,
        "skill_name" : "��������"
]),
([      "action" : "$n����������¼��Ⱥ�����Է�λ��һʽ����ȥ���⡱����������֮��ǰ�������ں�$N��æ���ң����ֵ����������ܣ������ỹ�ַ����ˡ�\n",
        "dodge"  : 80,
        "skill_name" : "��ȥ����"
])
});

mapping query_action(object me, object weapon)
{
        int zhaoshu, level;

        zhaoshu = sizeof(action);
        level   = (int) me->query_skill("luoying-shenfa");

        if (level < 60 )
                zhaoshu--;

        if (level < 50 )
                zhaoshu--;

        if (level < 40 )
                zhaoshu--;

        return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
        return usage == "dodge" || usage == "move";
}

int valid_learn(object me)
{
        return 1;
}

string query_dodge_msg(string limb)
{
        return action[random(sizeof(action))]["action"];
}

int practice_skill(object me)
{
        if( (int)me->query("jing") < 40 )
                return notify_fail("��ľ���̫���ˣ���������Ӣ����\n");
        me->receive_damage("jing", 30);
        return 1;
}

mixed valid_damage(object me, object victim, int damage, object weapon)
{
        mapping prepare,action;
	string msg,result,attack_skill;
	object w,w2;
	int ap, dp;
	w = victim->query_temp("weapon");
	w2 = me->query_temp("weapon");

	if( !victim->query_temp("wuzhuan") ) return;
	
	if( !living(victim) ) return;

	if (victim->query("neili") < 300) return;

	if( objectp(w2) )	
		attack_skill = w2->query("skill_type");
	else {
		prepare = me->query_skill_prepare();
		if (!prepare) prepare = ([]);
		else if ( sizeof(prepare) == 0)	attack_skill = "unarmed";
		else if ( sizeof(prepare) == 1)	attack_skill = (keys(prepare))[0];
		else if ( sizeof(prepare) == 2)	attack_skill = (keys(prepare))[me->query_temp("action_flag")];
	}

	attack_skill = me->query_skill_mapped(attack_skill);

	ap = me->query("combat_exp")/1000;
	ap += me->query("jiali")*2;

	dp = victim->query("combat_exp")/1000;
	dp += victim->query_skill("luoying-shenfa", 1);
	dp += victim->query_skill("tanzhi-shentong", 1);
	dp = (dp + random(dp*3/2)) / 2;

	action = me->query("actions");

	if( ap > dp ) return;

	if(victim->query_skill_mapped("parry") !="tanzhi-shentong") return;

	if((int)victim->query_skill("tanzhi-shentong", 1) < 120) return;

	if(victim->query_skill_prepared("finger") != "tanzhi-shentong") return;

	if(victim->query_temp("wuzhuan_hit") < 0) return;
	if(attack_skill=="tanzhi-shentong")
		result = HIG"$n��ָһ�����͵�һ�����죬һ��ϸϸ�ľ��������ȥ�����ɡ���ָ��ͨ��ָ����������ʱ��������Ρ�\n" NOR;
	else if( objectp(w2) )
		result = HIG"$n��ָһ�����͵�һ�����죬һ��ϸϸ�ľ��������ȥ����ʱ��$N��"+w2->name()+HIG"�������ھ���������������������"+to_chinese(attack_skill)+"��\n" NOR;
	else result = HIG"$n��ָһ�����͵�һ�����죬һ��ϸϸ�ľ��������ȥ���⡸��ָ��ͨ����$N�ġ�"+to_chinese(attack_skill)+"�����˸�����൱��˭Ҳû����˭��\n" NOR;


        victim->add("neili",- (30+me->query("jiali")/2));
        victim->add_temp("wuzhuan_hit",-1);

        damage = -damage;
        return ([ "msg" : result, "damage" : damage ]);
}
