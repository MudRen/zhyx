// ding-force.c С������

inherit FORCE;

int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("ding-force", 1);
        return lvl * lvl * 19 * 15 / 100 / 200;
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        if ( me->query("gender") == "����" && (int)me->query_skill("ding-force", 1) > 49)
                return notify_fail("�����޸����ԣ�С���������Ѹ���һ��¥��\n");
        return 1;
}

int practice_skill(object me)
{
        return notify_fail("С������ֻ�ܸ�С��ѧ�����������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"ding-force/" + func;
}



