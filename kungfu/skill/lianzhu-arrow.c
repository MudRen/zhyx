// by Lonely

inherit SKILL;

int valid_enable(string usage) { return  usage == "arrow"; }

int valid_learn(object me)
{
        return notify_fail("�������ֻ����������(qingjiao)��ѧϰ��\n");    
}

string perform_action_file(string action)
{
        return __DIR__"lianzhu-arrow/" + action;
}                 


