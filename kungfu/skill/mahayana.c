//mahayana.c  ������͹�
inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{   
	int level;
	level = (int) me->query_skill("linji-zhuang", 1) ;
    if ( level > 200 && (int) me->query_skill("mahayana", 1) > (level + 50) )			
       return notify_fail("����ټ�ʮ��ׯ��������͹�̫�࣬��Ҫ��һ���ˡ�\n");
	
    if ((int)me->query("shen") < 0 )
       return notify_fail("���а��̫�أ��޷�����������͹���\n");

    return 1;
}

void skill_improved(object me)
{
}
