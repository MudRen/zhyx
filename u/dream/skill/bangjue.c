// bangjue.c �򹷰��ķ�
// by Lonely

inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me) 
{
        if ((int)me->query_skill("staff", 1) < 30)
                return notify_fail("��Ļ����ȷ�̫��, ����᲻�˰�����\n");
        return 1;
}

int practice_skill(object me)
{       
        return notify_fail("�򹷰��ķ�ֻ�ܿ�ѧ(learn)����ߡ�\n");
}

