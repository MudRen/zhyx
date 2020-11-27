#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action":"$N���˽ŵף�����������֮���" ]),
});
mapping query_action(object me, object weapon)
{
        return action[0];
}

string *dodge_msg = ({
        "$n���˽ŵף�����������֮��ˣ���$P�����ʵ����룬���������޴ӡ�\n"
});

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

string main_skill() { return "sixiang-shengong"; }

int valid_learn(object me)
{
        object ob;
  
        if ((int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("���ѽ����־������������񹦣������ٷֿ���ϰ�ˡ�\n");
        
        if (me->query("dex") < 30)
                return notify_fail("������������㣬�޷������ȸ�衣\n");

        if (me->query_skill("throwing", 1) < 10)
                return notify_fail("��İ������ܲ�����졣\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("zhuque-wu", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ����������������ȸ�衣\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("zhuque-wu", 1))
                return notify_fail("��Ļ���ȭ��ˮƽ���ޣ����Ա�����ǿ������ȸ�衣\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "dodge";
}

int practice_skill(object me)
{
	return notify_fail("��ȸ��ֻ��ͨ��������ȸ������ߡ�\n");
}