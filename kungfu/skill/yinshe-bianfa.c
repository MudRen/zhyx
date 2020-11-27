// yinshe-bianfa ���߱޷� by kasumi

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([     "action":   "$N���β�����һ�С����߶��项������$wֱ��$n��˫Ŀ��ȥ",
       "dodge":        100,
       "parry":        80,
	   "attack":       100,
       "damage":       100,
       "force":        300,
       "lvl" : 0,
       "skill_name" : "���߶���",
       "damage_type":  "����"
]),
([     "action":   "$Nһ�С����߸��������$w��Ӱ���Σ���$n�ľ�����ȥ",
       "dodge":     110,
       "parry":     90,
	   "attack":    110,
       "damage":    120,
       "force":     340,
       "lvl" : 40,
       "skill_name" : "���߸���",
       "damage_type":  "����"
]),
([     "action":   "$NͻȻ������ˣ���$n�Ƚ�ʱ������һ�С����߰�β��������$w������֮����ֱ��$n��ǰ�ض�ȥ",
       "dodge":     120,
       "parry":     100,
	   "attack":    120,
       "damage":    140,
       "force":     380,
       "lvl" : 80,
       "skill_name" : "���߰�β",
       "damage_type":  "����"
]),
([     "action":   "$N�͵�һ��������$w��������Բ����һ�С����߽�������Ȧ��$n������",
       "dodge":     130,
       "parry":     100,
	   "attack":    130,
       "damage":    160,
       "force":     420,
       "lvl" : 120,
       "skill_name" : "���߽���",
       "damage_type":  "����"
]),
([     "action":  "$N���ΰ���������ң�һ�С������·���������$w�γ�������Ӱ����$nӭͷ����",
       "dodge":    140,
       "parry":    100,
       "damage":   180,
	   "attack":   140,
       "force":    440,
       "lvl" : 160,
       "skill_name" : "�����·�",
       "damage_type":  "����"
]),
([     "action":  "$N���ؾ͵�һ����һ�С����ߴ����������$w��Ѹ�ײ����ڶ�֮��ɨ��$n��˫��",
       "dodge":    150,
       "parry":    100,
	   "attack":   150,
       "damage":   200,
       "force":    480,
       "lvl" : 200,
       "skill_name" : "���ߴ��",
       "damage_type":  "����"
]),
([     "action": "$N���η��ͣ�һ�С����߹鳲��������$w����������Ӱ����׼$n������ȥ",
       "dodge":   160,
       "parry":   110,
       "damage":  220,
	   "attack":  160,
       "force":   520,
       "lvl" : 240,
       "skill_name" : "���߹鳲",
       "damage_type":  "����"
]),
([     "action": "$N�͵ض�ֱ���е�$w��һ�С����߳�����������$n�ĽŸ�ֱ�ö��ϣ�ֱ��$n��ͷ����ȥ",
       "dodge":   160,
       "parry":   120,
	   "attack":  170,
       "damage":  240,
       "force":   560,
       "lvl" : 260,
       "skill_name" : "���߳���",
       "damage_type":  "����"
])
});
int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
       object weapon;

       if( (int)me->query("max_neili") < 100 )
               return notify_fail("����������㣬�޷������߱޷���\n");

	     if( (int)me->query_skill("xiuluo-yinshagong",1) < 180 )
               return notify_fail("���������ɷ���ȼ��������޷��������߱޷���\n");


       if ( !objectp(weapon = me->query_temp("weapon"))
       || ( string)weapon->query("skill_type") != "whip" )
               return notify_fail("���������һ�����Ӳ������޷���\n");
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
       level   = (int) me->query_skill("yinshe-bianfa",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       object weapon;
	   int cost;   

       if (!objectp(weapon = me->query_temp("weapon"))
       || (string)weapon->query("skill_type") != "whip")
               return notify_fail("��ʹ�õ��������ԡ�\n");	      

        if ((int)me->query("qi") < 100)
                return notify_fail("�������̫���ˡ�\n");

        cost = me->query_skill("yinshe-bianfa", 1) / 3 + 80;

        if ((int)me->query("neili") < cost)
                return notify_fail("������������ˡ�\n");

        me->receive_damage("qi", 100);
        me->add("neili", -cost);
        return 1;
}

string perform_action_file(string action)
{
       return __DIR__"yinshe-bianfa/" + action;
}
