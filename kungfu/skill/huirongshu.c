// ������.c

#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int practice_skill(object me)
{
        return notify_fail("������ֻ�ܿ�ѧ(learn)����ߡ�\n");
}
int valid_learn(object me)
{
        if (me->query("per") < 14 )
                return notify_fail("��û��Ҫѧ���ż����ˡ�\n");

        return 1;
}

void skill_improved(object me)
{
    tell_object(me, HIM "���ڻ��ݼ��ɷ�����ĵ�������ߣ�\n" NOR );
    me->add("per", -0.1);
}



