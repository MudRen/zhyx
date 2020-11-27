#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "ֻ��$N����һ�죬������֮����$n���ƹ�ȥ",
        "dodge": 20,
        "parry": 20,
        "attack": 20,
        "force": 20,
        "damage_type":  "����"
]),
});

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

string main_skill() { return "sixiang-shengong"; }

int valid_learn(object me)
{
        object ob;
  
        if ((int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("���ѽ����־������������񹦣������ٷֿ���ϰ�ˡ�\n");
        
        if (me->query("int") < 30)
                return notify_fail("����������Բ��㣬�޷���������ơ�\n");

        if (me->query_skill("throwing", 1) < 10)
                return notify_fail("��İ������ܲ�����졣\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("qinglong-po", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ�������������������ơ�\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("qinglong-po", 1))
                return notify_fail("��Ļ���ȭ��ˮƽ���ޣ����Ա�����ǿ���������ơ�\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "unarmed";
}

int practice_skill(object me)
{
	return notify_fail("������ֻ��ͨ����������������ߡ�\n");
}

string perform_action_file(string action)
{
        return __DIR__"qinglong-po/" + action;
}
