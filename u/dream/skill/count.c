
// count.c

inherit SKILL;

string type() { return "knowledge"; }

void skill_improved(object me)
{}

int valid_learn(object me)
{
        if ((int)me->query("int") < 35)
                return notify_fail("������Բ������޷�ѧϰ��µ��������ԡ�\n");
                
        if ((int)me->query_skill("literate", 1) < 100)
                return notify_fail("��������д�ֶ�ûѧ�ã���̸ʲô�������ԣ�\n");

        if ((int)me->query_skill("literate", 1) < (int)me->query_skill("count", 1))
                return notify_fail("��Ķ���д��ˮƽ���ޣ��޷����ո���µ��������ԡ�\n");

        if ((int)me->query_skill("count", 1) > 399 && me->query("family/family_name") != "�һ���")
                return notify_fail("�������Դ����㵽��͹��ˣ����������ͱ�������һ�����\n");

        return 1;

}


