inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

int valid_force(string force)
{
        return force == "hunyuan-yiqi" ||
               force == "zhanshen-xinjing" ||
               force == "taiji-shengong" ||
               force == "taixuan-gong" ||
               force == "wudang-xinfa" ||
               force == "shaolin-xinfa";
}

int query_neili_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("yijinjing", 1);

        if (me->query_skill("lunhui-jian", 1) > 200)
                lvl += me->query_skill("lunhui-jian", 1) / 2;

        return lvl * lvl * 15 * 21 / 100 / 200;
}

int query_jingli_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("buddhism", 1);
        lvl += (int)me->query_skill("lunhui-jian", 1);
        if (me->query_skill("lunhui-jian", 1) > 200)
                return lvl * 9 / 5;
        else
                return 0;
}

int valid_learn(object me)
{
        if (me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ���򲻹����޷�ѧϰ�׽�񹦣�\n");

        if (me->query_skill("freezing-force", 1))
                return notify_fail("���Ѿ����׽�񹦺ͱ��Ϻ�����������һ�����ڹ��ˡ�\n");

        if (me->query_skill("force", 1) < me->query_skill("yijinjing", 1))
                return notify_fail("��Ļ����ڹ�ˮƽ���������������������׽�񹦣�\n");

        if (me->query("gender") != "����")
                return notify_fail("�㲻�����ԣ��޷���ϰ�׽�񹦡�\n");

        return ::valid_learn(me);
}


int practice_skill(object me)
{
        return notify_fail("�׽��ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"yijinjing/" + func;
}
