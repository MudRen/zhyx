// huntian-qigong.c

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return force == "jiaohua-neigong" || force == "huntian-qigong";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("huimeng-xinfa", 1);
        return lvl * lvl * 15 * 17 / 100 / 200;
}

int valid_learn(object me)
{
        if (me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ���򲻹����޷�ѧϰ�����ķ���\n");

	    return 1;
}

int practice_skill(object me)
{
	    return notify_fail("��������ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"huimeng-xinfa/" + func;
}
