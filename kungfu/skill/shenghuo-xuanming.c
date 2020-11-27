// Code of JHSH
// shenghuo-xuanming.c	����  ʥ����ڤ��
// Zhangchi 2/2000

inherit FORCE;

#include <ansi.h>

int valid_enable(string usage)
{
	return usage == "force";
}

int valid_force(string force)
{
        return force == "shenghuo-xinfa";
}

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("shenghuo-xuanming", 1);
    return lvl * lvl * 16 * 15 / 100 / 200;
}

int valid_learn(object me)
{
	mapping skill;
	string *skname;
	int i, n = 0;

	skill = this_player()->query_skills();
	skname = sort_array(keys(skill), (: strcmp :) );

	if ((int)me->query_skill("force", 1) < 10 )
		return notify_fail("��Ļ����ڹ�����㣬����ѧʥ����ڤ����\n");

	if (me->query("gender") == "����")
		return notify_fail("���޸����ԣ�������������"
                                   "���������ʥ����ڤ��\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
    return notify_fail("ʥ����ڤֻ����ѧ�ģ����Ǵ�����(exert)�����������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"shenghuo-xuanming/" + func;
}
mapping curing_msg(object me)
{
        return ([
"apply_short" :me->name()+"�������࣬��Ŀ���ƣ�����ȼ��һ�Ż��档",
"start_self" :HIR"����ϥ������˫��ʮָ�ſ���������ǰ�����������֮״������ʥ����ڤ�ķ����ˡ�\n"NOR,
"on_self" :HIM"�����Ĭ��ģ�һ��ů���������������ߣ������������ϡ�\n"NOR,
"start_other" :HIM""+me->name()+"����ߴߴ��������߶���ģ��������Խ��Խ����\n"NOR,
"finish_self" :HIR"��е�ů���α����죬ȫ������˵���������������վ��������\n"NOR,
"finish_other" :me->name()+"��ɫ���죬����Ļ��潥�����ˣ�����վ��������\n",
"unfinish_self" :"��������ʥ����ڤ�ķ����ˣ���Ȼ�����������ã�����ů��ͣ�Ͳ�ǰ��ֻ�����գ��ݻ����ˡ�\n",
"unfinish_other":me->name()+"��ɫ�԰ף�����վ���������㼴Ϩ��\n",
"halt_self" :"��������ϼ��������߶�����ǿ�н�����ů���ջء�\n",
"halt_other" :me->name() +"�������˼�������վ��������������滺��Ϩ��\n",
        ]);
} 
