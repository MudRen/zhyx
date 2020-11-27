#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action":"$N����˫�ۣ�ȭ�ϰ׻�֮�����֣�������$l" ]),
});
mapping query_action(object me, object weapon)
{
        return action[0];
}

string main_skill() { return "sixiang-shengong"; }

int valid_learn(object me)
{
        object ob;
  
        if ((int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("���ѽ����־������������񹦣������ٷֿ���ϰ�ˡ�\n");
        
        if (me->query("str") < 30)
                return notify_fail("��������������㣬�޷��������׻�����\n");

        if (me->query_skill("throwing", 1) < 10)
                return notify_fail("��İ������ܲ�����졣\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("baihu-jing", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ�������������İ׻�����\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("baihu-jing", 1))
                return notify_fail("��Ļ���ȭ��ˮƽ���ޣ����Ա�����ǿ���İ׻�����\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "throwing";
}

int practice_skill(object me)
{
        return notify_fail("�׻���ֻ��ͨ������׻����ʵս����ߡ�\n");
}

string perform_action_file(string action)
{
        return __DIR__"baihu-jing/" + action;
}
