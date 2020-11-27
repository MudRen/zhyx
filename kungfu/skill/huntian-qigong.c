// huntian-qigong.c

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return force == "jiaohua-neigong" || force == "huimeng-xinfa";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("huntian-qigong", 1);
        return lvl * lvl * 15 * 14 / 100 / 200;
}

int valid_learn(object me)
{
        if (me->query_skill("force", 1) < 30)
                return notify_fail("��Ļ����ڹ���򲻹����޷�ѧϰ����������\n");

	    return 1;
}

int practice_skill(object me)
{
	    return notify_fail("��������ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"huntian-qigong/" + func;
}