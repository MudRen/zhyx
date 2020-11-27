inherit FORCE;

int valid_enable(string usage)
{
	return usage == "force";
}

int valid_force(string force)
{
        return force == "xiantian-gong" ||
               force == "quanzhen-xinfa"  ||
               force == "duanshi-xinfa";
}

int query_neili_improve(object me)
{
    	int lvl,n;

    	lvl = (int)me->query_skill("kurong-changong", 1);
    	if (lvl>=900)
    		n=25;
    	else if (lvl>=600)
    	  n=22;
    	else if (lvl>=300)
    	  n=19;
    	else n=16;
    				
    	return lvl * lvl * 15 * n / 100 / 200;
}

int valid_learn(object me)
{
    	if (me->query("gender") == "����")
        	return notify_fail("���޸����ԣ���������������������������\n");

    	return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("��������ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"kurong-changong/" + func;
}
