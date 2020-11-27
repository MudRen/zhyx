#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force) { return 1; }       

int query_neili_improve(object me)   
{
        int lvl;  
        lvl = (int)me->query_skill("shenyuan-gong", 1);  
        return lvl /10 * lvl /10 * 20 * 15 / 10 / 20;  
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("shenyuan-gong", 1);
        if (me->query("gender") == "����" && lvl > 49)
                return notify_fail("���޸����ԣ������������������������Ԫ����\n");
        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("��Ļ����ڹ���򻹲������޷������Ԫ����\n");
        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("��Ԫ��ֻ����ѧ(learn)�������������ȡ�\n");
              
}

string exert_function_file(string func)
{
        return __DIR__"shenyuan-gong/" + func;
}
mapping exercise_msg(object me)
{
        return ([
                "status_msg" : "������������̬��Ϊ���ء�",
                "start_my_msg" : "����һվ��˫�ֻ���̧������һ������������ʼ��������ת��\n",
                "start_other_msg" : "����������һվ��˫�ֻ���̧������ʼ�������������\n",
                "halt_msg" : "üͷһ�壬�������������ַ���������\n",
                "end_my_msg" : "������������������������һȦ���������뵤������֣�������һ������\n",
                "end_other_msg" : "���۾��������ϣ��������������ַ��£�������һ������\n"
        ]);
}

