// bluesea-force.c �Ϻ�����

#include <ansi.h>
inherit FORCE;

string *dodge_msg = ({
        "$n����������$N�Ľ������������ǽ�ϣ�û�а��Ч����\n",
        "$n���һ����һ������ֱ�������Ӳ����������$N��\n",
        "$n����һת��һ�����罫$N������ȫ�����⡣\n",
        "$n��Ȼ��Ц��΢΢�ƶ�����������ʹ$N�Ľ�����֮���塣\n",
});



mapping *actionf = ({
([      "action":"$N���һ����һָ��������$n��$l�������˷�Բ����ķ�Χ",
        "force" : 500,
        "attack": 150,
        "dodge" : 90,
        "parry" : 88,
        "damage": 170,
        "damage_type":  "����"
]),
([      "action":"$Nһ����ȣ��漴һ����������;ȴ��Ȼһָ����$n��$l",
        "force" : 510,
        "attack": 165,
        "dodge" : 110,
        "parry" : 90,
        "damage": 160,
        "damage_type":  "����"
]),
([      "action":"$N��������������������$n�ļ�ͷ������ʳȴ����$n��$l��",
        "force" : 515,
        "attack": 155,
        "dodge" : 85,
        "parry" : 85,
        "damage": 175,
        "damage_type":  "����"
]),
([      "action":"$N����һ�������������ƣ�˫����������$n��$l",
        "force" : 520,
        "attack": 140,
        "dodge" : 80,
        "parry" : 90,
        "damage": 180,
        "damage_type":  "����"
]),
([      "action":"$N����ԭ�ز�����˫��ƽ�ƣ�һ��������ձ�$n��ȥ",
        "force" : 535,
        "attack": 135,
        "dodge" : 80,
        "parry" : 95,
        "damage": 170,
        "damage_type":  "����"
]),
([      "action":"$N���°��Ͱ��ԣ��������Ī�⣬��������������������$n",
        "force" : 500,
        "attack": 150,
        "dodge" : 85,
        "parry" : 115,
        "damage": 165,
        "damage_type":  "����"
]),
});

mapping *actionw = ({
([      "action":"$N���һ��������$w��������$n�������˷�Բ����ķ�Χ",
        "force" : 450,
        "attack": 170,
        "dodge" : 100,
        "parry" : 110,
        "damage": 200,
        "damage_type":  "����"
]),
([      "action":"$Nһ����ȣ����е�$w�漴��ɨ$n����;ȴ��Ȼ����$n��$l",
        "force" : 460,
        "attack": 165,
        "dodge" : 80,
        "parry" : 110,
        "damage": 220,
        "damage_type":  "����"
]),
([      "action":"$N��������������������$n�ļ�ͷ�����ֵ�$wȴ����$n��$l��",
        "force" : 480,
        "attack": 175,
        "dodge" : 85,
        "parry" : 100,
        "damage": 210,
        "damage_type":  "����"
]),
([      "action":"$N����һ�������������ƣ����е�$w��������$n��$l",
        "force" : 475,
        "attack": 180,
        "dodge" : 75,
        "parry" : 120,
        "damage": 205,
        "damage_type":  "����"
]),
([      "action":"$N����ԭ�ز��������е�$wһ����һ��������ձ�$n��ȥ",
        "force" : 480,
        "attack": 175,
        "dodge" : 80,
        "parry" : 125,
        "damage": 210,
        "damage_type":  "����"
]),
([      "action":"$N���°��ϰ��ԣ��������Ī�⣬���е�$w����������â������$n",
        "force" : 490,
        "dodge" : 160,
        "parry" : 110,
        "damage": 220,
        "damage_type":  "����"
]),
});

string *usage_skills = ({ "strike", "dodge",
                          "parry", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("bluesea-force", 1);
        return lvl * lvl * 20 * 15 / 100 / 200;
}

int query_jingli_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("bluesea-force", 1);
        return lvl * 9 / 5;
}
 

string *parry_msg = ({
	"ֻ��$NĬ���Ϻ�������������סȫ��$nһ�л���$N��ֻ�����ִ�����ʯ���󺣣���о��ȣ���æ�˻ء� \n",
        "����$nһ�й�����$Nŭ��һ�������˷��������ΰ����ǽ����$n���бƻء�\n",
        "ֻ��$Nȫ������������һ�������סȫ���ѽ�$n���н�����ʽ�������֮�⡣\n",
        "����$N���˷��������һ������$n����ʽ�ƻء�\n",
});

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}
int valid_combo(string combo)
{
        return combo == "bluesea-force" ||
               combo == "tanzhi-shentong";
}

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
        return weapon ? actionw[random(sizeof(actionw))] :
                        actionf[random(sizeof(actionw))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level;
        int i;

        if ((int)me->query("combat_exp") < 3000000)
                return notify_fail("������Ϻ��������֮����"
                                   "ƾ�Լ���ս������һʱ��������ᡣ\n");

        if ((int)me->query_skill("martial-cognize", 1) < 250)
                return notify_fail("������Ϻ������������֮������"
                                   "�Լ�����ѧ����ȫȻ�޷����ס�\n");

        if (me->query("character") != "������")
                return notify_fail("�㷢���Ϻ�������������䣬��"
                                   "���޳����Լ�ʵ����᲻�ˡ�\n");

        if (me->query("con") < 22)
                return notify_fail("����ͼ�������������Ϻ�������ȴͻ"
                                   "Ȼ������ǰһ�ڣ������Ǹ��ǲ��ã�"
                                   "������ǿ���С�\n");

        if (me->query("int") > 15)
                return notify_fail("����ͼǱ�������Ϻ�������ȴͻȻ��"
                                   "����ǰ����޳������������Թ��ߣ�"
                                   "��������\n");

	if (me->query("gender") == "����" &&
	    (int)me->query_skill("bluesea-force", 1) > 1)
		return notify_fail("���޸����ԣ�����������������������Ϻ�������\n");

        level = me->query_skill("bluesea-force", 1);

        if ((int)me->query_skill("martial-cognize", 1) < 300 &&
            (int)me->query_skill("martial-cognize", 1) < level)
                return notify_fail("������Լ�����ѧ�������ޣ���������������Ϻ�������\n");

        for (i = 0; i < sizeof(usage_skills); i++)
                if (me->query_skill(usage_skills[i], 1) < level)
                        return notify_fail("���" + to_chinese(usage_skills[i]) +
                                           "����⻹�������޷���������������Ϻ�������\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("�Ϻ�����������޷��򵥵�ͨ����ϰ������\n");
}

int difficult_level()
{
        return 500;
}

string perform_action_file(string action)
{
        return __DIR__"bluesea-force/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"bluesea-force/exert/" + action;
}


