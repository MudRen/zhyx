#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) 
{ 
        return usage == "force"; 
}

int valid_force(string force)
{
        return force == "suxin-jue" ||
               force == "quanzhen-xinfa";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("yunv-xinjing", 1);
        return lvl * lvl * 15 * 16 / 100 / 200;
}

int valid_learn(object me)
{
        if ( me->query("gender") == "����")
                return notify_fail("���޸����ԣ������ѵ���������ϰ��Ů�ľ���\n");

        if ((int)me->query_skill("force", 1) < 150)
                return notify_fail("��Ļ����ڹ���򻹲�����������ϰ��Ů�ľ���\n");
       
        if ((int)me->query("max_neili", 1) < 2000)
                return notify_fail("���������Ϊ���㣬���������Ů�ľ���\n");

        return ::valid_learn(me);
}



int practice_skill(object me)
{
        return notify_fail("��Ů�ľ�ֻ����ѧ(learn)�����������ȡ�\n");
}



string exert_function_file(string func)
{
        return __DIR__"yunv-xinjing/" + func;
}

