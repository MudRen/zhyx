inherit SKILL;
#include <ansi.h>

mapping *action = ({
([	"action" : "$Nһ����ȣ����Ƶ�������֮�ϣ�����$n",
	  "force" : 320,
    "attack": 130,
	  "dodge" : 90,
    "parry" : 100,
   	"damage": 90,
	  "lvl"   : 0,
	"damage_type" : "����"
]),
([	"action" : "$N��ɫ���أ�˫���ᶶ��Ʈ������������$n",
	  "force" : 350,
    "attack": 140,
	  "dodge" : 100,
    "parry" : 110,
	  "damage": 95,
	  "lvl"   : 50,
   	"damage_type" : "����"
]),
([	"action" : "$N������������˫�ƣ���ʱֻ��һƬ��Ӱ����$n",
	"force" : 380,
        "attack": 150,
	"dodge" : 110,
        "parry" : 120,
	"damage": 100,
	"lvl"   : 100,
	"damage_type" : "����"
]),
([	"action" : "$N˫��ƽ�ӣ��ͻ���$n��$l�����ް�㻨�ɿ���",
	"force" : 410,
        "attack": 160,
	"dodge" : 110,
        "parry" : 120,
	"damage": 110,
	"lvl"   : 150,
        "damage_type" : "����"
]),
([	"action" : "$N���������ŷ���˫���ͷ��ĳ�����ʱһƬ��Ӱ����$n",
	"force" : 440,
        "attack": 170,
	"dodge" : 120,
        "parry" : 130,
	"damage": 120,
	"lvl"   : 180,
	"damage_type" : "����"
]),
([	"action" : "$N������Σ�����Я��ǧ��֮����Ȼ��$n��ͷ������",
	"force" : 460,
        "attack": 180,
	"dodge" : 130,
	"damage": 130,
        "parry" : 130,
	"lvl"   : 220,
        "damage_type" : "����"
]),
([	"action" : "$N������ĺ��ƣ����ֺ�ɨ$n��$l�����ֹ���$n���ؿ�",
	"force" : 500,
        "attack": 190,
	"dodge" : 140,
        "parry" : 140,
	"damage": 140,
	"lvl"   : 260,
        "damage_type" : "����"
]),
([	"action" : "$N��Ȼһ�����ȣ������ŷ���˫��ͬʱ����$n��$l",
	"force" : 550,
        "attack": 200,
	"dodge" : 150,
        "parry" : 150,
	"damage": 150,
	"lvl"   : 300,
        "damage_type" : "����"
])
});

int valid_enable(string usage)
{
	return usage == "parry" || usage == "strike";
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����׾�Ʒ�������֡�\n");

        if (me->query("str") < 26)
                return notify_fail("�������������㣬�޷�ѧϰ����Ĺ�׾�Ʒ���\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���򲻹����޷�����׾�Ʒ���\n");

	if ((int)me->query("max_neili") < 2500)
		return notify_fail("�������̫�����޷�����׾�Ʒ���\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("��Ļ����Ʒ���򲻹����޷�����׾�Ʒ���\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("guzhuo-zhang", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������Ĺ�׾�Ʒ���\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("guzhuo-zhang",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 100)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 100)
		return notify_fail("���������������׾�Ʒ���\n");

	me->receive_damage("qi", 85);
	me->add("neili", -90);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (damage_bonus > 120 && (int)me->query_skill("xixing-dafa",1) > 300 && random(3)!=1) 	
        {
                victim->receive_wound("qi", (damage_bonus - 110) / 2, me);
                me->add("qi", (damage_bonus - 110) / 2);
                if (me->query("qi") > me->query("eff_qi"))
                	me->set("qi", me->query("eff_qi") );  
                return MAG "ֻ�����ꡱ��һ��" + victim->name() + MAG "������£���Ԫ�ѱ�"+me->name()+MAG"������"+me->name()+MAG"�������ֺ�����Щ��\n" NOR;
        }
}

string perform_action_file(string action)
{
	return __DIR__"guzhuo-zhang/" + action;
}
