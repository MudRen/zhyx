inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return force == "shenlong-xinfa" ||
               force == "xuanming-shengong" ||
               force == "minggu-xinfa" ;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("huaxue-shengong", 1);
        return lvl * lvl * 15 * 16 / 100 / 200;
}

int valid_learn(object me)
{
        if (me->query("gender") == "����"
           && (int)me->query_skill("huaxue-shengong", 1) > 99)
                return notify_fail("���޸����ԣ���������������������Ļ�Ѫ�񹦡�\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ���򻹲�����\n");

        if ((int)me->query_skill("shenlong-xinfa", 1) < 100)
                return notify_fail("��������ķ������̫ǳ���޷���⻯Ѫ�񹦡�\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("��Ѫ��ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"huaxue-shengong/" + func;
}
