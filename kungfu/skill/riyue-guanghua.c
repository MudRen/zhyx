// riyue-guanghua.c ���¹⻪
// By haiyan

#include <combat.h> 
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force) { return force == "riyue-xinfa"; }

int query_neili_improve(object me)
{
    int lvl;
    lvl = (int)me->query_skill("riyue-guanghua", 1);
    return lvl * lvl * 15 * 15 / 100 / 200;
}

int valid_learn(object me)
{
    if ( (string)me->query("gender") == "����" &&
         (int)me->query_skill("riyue-guanghua", 1) > 49 )
            return notify_fail("������δ����������������ġ����¹⻪����\n");

    if ( me->query("gender") == "Ů��" )
            return notify_fail("���޷���ᡸ���¹⻪�����ž�ѧ��\n");

    if ((string)me->query("character") == "��������")
            return notify_fail("�����а��룺��Ϊ�˹������䣬����а�̹���ѧ��������\n");

    if ( (int)me->query_skill("xixing-dafa", 1) > 0 )
            return notify_fail("����ѧ�����Ǵ󷨣������������¹⻪��\n");

    if (me->query("dex") < 25)
            return notify_fail("������ֲ������޷�������¹⻪����Ҫ��\n");

    if ((int)me->query_skill("riyue-xinfa", 1) < 100)
            return notify_fail("��������ķ���򻹲���������������¹⻪��\n");

    if ((int)me->query_skill("force", 1) < (int)me->query_skill("riyue-guanghua", 1))
            return notify_fail("��Ļ����ڹ�ˮƽ���ޣ�����������������¹⻪��\n");

    return ::valid_learn(me);
}

int practice_skill(object me)
{
    return notify_fail("���¹⻪ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
    mapping sk;
    string *skname;
    int i, k=0;

    if (mapp(this_player()->query("tianmo_jieti")))
        return __DIR__"riyue-guanghua/" + func;

    sk=this_player()->query_skills();
    skname=sort_array( keys(sk), (: strcmp :) );

    for(i=0; i < sizeof(sk); i++)
    {
        if (SKILL_D(skname[i])->valid_enable("force"))  k++;
    }

    if ( k >=3 )
    {
        tell_object(this_player(), "�����ڲ�ͬ���������ײ������ʩչ���¹⻪��\n");
        return 0;
    }

    return __DIR__"riyue-guanghua/" + func;
}

