// huashan-neigong.c ��ɽ�ķ�
// by Lonely

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int level = (int)me->query_skill("huashan-neigong", 1);
        if (me->query("gender") == "����" && level > 49)
                return notify_fail("���޸����ԣ���������������������Ļ�ɽ�ڹ���\n");
        return ::valid_learn(me);
}

int valid_force(string force) { return 1; }       

int query_neili_improve(object me)  
{
        int lvl; 
        lvl = (int)me->query_skill("huashan-neigong", 1); 
        return lvl * lvl * 18 * 15 / 100 / 200; 
}

int practice_skill(object me)
{
        return notify_fail("��ɽ�ķ�ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"huashan-neigong/" + func;
}


