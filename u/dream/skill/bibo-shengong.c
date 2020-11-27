// bibo-shengong.c �̲���
// by Lonely

inherit FORCE;

int valid_force(string force) { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("bibo-shengong", 1);
        return lvl * lvl * 20 * 15 / 100 / 200;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("bibo-shengong", 1);

        if (me->query("gender") == "����" && lvl > 49)
                return notify_fail("���޸����ԣ���������������������ı̲��񹦡�\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("�̲���ֻ����ѧ���������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"bibo-shengong/" + func;
}

mapping exercise_msg(object me)
{
        return ([
                "start_self"   : "�������£�˫Ŀ΢�գ�˫���������������̫�������˺�һ���������顣\n",
                "start_other"  : "�������£�˫Ŀ΢�գ�˫���������������̫������紵����" + me->name() + 
                                 "���ϵ����۾�Ȼ��Ϊ������\n",
                "finish_self"  : "����Ϣ������һ��С���죬�������뵤�˫��һ��վ��������\n",
                "finish_other" : "���Ϻ��է�֣���������ȥ���漴˫��һ��վ��������\n"
        ]);
}
