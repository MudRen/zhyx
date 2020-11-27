#include <ansi.h>

inherit SKILL;
mapping *action = ({
([      "action":"$N������������������������ƾ����������������ת" ]),
});

mapping query_action(object me, object weapon)
{
        return action[0];
}

string *parry_msg = ({
        "$n������������������������ƾ���������ص�ˮй��ͨ��$Pһʱ�޷����֡�\n",
      });

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

string main_skill() { return "sixiang-shengong"; }

int valid_learn(object me)
{
        object ob;
  
        if ((int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("���ѽ����־������������񹦣������ٷֿ���ϰ�ˡ�\n");
        
        if (me->query("con") < 30)
                return notify_fail("���������ǲ��㣬�޷��������ʽ��\n");

        if (me->query_skill("throwing", 1) < 10)
                return notify_fail("��İ������ܲ�����졣\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("xuanwu-shi", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ������������������ʽ��\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("xuanwu-shi", 1))
                return notify_fail("��Ļ���ȭ��ˮƽ���ޣ����Ա�����ǿ��������ʽ��\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "parry";
}

int practice_skill(object me)
{
	return notify_fail("����ʽֻ��ͨ���������������ߡ�\n");
}

string perform_action_file(string action)
{
        return __DIR__"xuanwu-shi/" + action;
}
