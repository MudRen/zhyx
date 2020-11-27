// busi-shenlong.c ��������
// smallbear 11/2/2002
       
inherit FORCE; 
   
int valid_enable(string usage) { return usage == "force"; } 

int valid_force(string force)
{
        return force == "shenlong-xinfa" ||
               force == "shedao-neigong";
}

int query_neili_improve(object me) 
{ 
        int lvl; 
        lvl = (int)me->query_skill("busi-shenlong", 1);  
        return lvl * lvl * 15 * 15 / 100 / 200;  
} 
int valid_learn(object me) 
{ 
        if (me->query("gender") == "����" && 
        (int)me->query_skill("busi-shenlong", 1) > 49) 
                return notify_fail("���޸����ԣ���������������������Ĳ��������ķ���\n"); 

        return ::valid_learn(me); 
} 

int practice_skill(object me) 
{ 
        return notify_fail("��������ֻ��ͨ��ѧ���Ǵ�����(exert)�����������ȡ�\n"); 
} 

string exert_function_file(string func) 
{ 
        return __DIR__"busi-shenlong/" + func; 
} 
     

