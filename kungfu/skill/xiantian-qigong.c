// xiantian-gong.c ��������
// by Lonely

inherit FORCE;

int valid_force(string force) { return 1; }       

int query_neili_improve(object me)  
{
        int lvl; 
        lvl = (int)me->query_skill("xiantian-qigong", 1); 
        return lvl * lvl * 22 * 15 / 100 / 200; 
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("xiantian-qigong", 1);

        if (me->query("gender") == "����")
                return notify_fail("���޸����ԣ��������������������������ڵ�����������\n");

        if (me->query("class") == "bonze")
                return notify_fail(RANK_D->query_respect(me)+"�����ҵ�����������������ȥ���˷��ţ�\n");

        if (lvl <= 100)
        {
                if (lvl > 10 && (int)me->query("shen") < lvl * 100)
                        return notify_fail("�����������̫���ˡ�\n");
        }
        else
        {
                if ((int)me->query("shen") < (51200 + (lvl - 100) * 1000))
                        return notify_fail("�����������̫���ˡ�\n");
        }

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("��������ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"xiantian-qigong/" + func;
}


