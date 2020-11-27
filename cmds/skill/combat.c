// combat.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int count;

	if (!ultrap(me)) return notify_fail("�㲻�Ǵ���ʦ��δ��ת��ʵս����Ϊ��������\n");
        if (!arg || !(sscanf(arg,"%d",count) == 1)) count = 100;
        if (count < 100) return notify_fail("����뼤������100���ʵս���顣\n");       
        if (count > (int)me->query("combat_exp")/10) return notify_fail("������ܼ���ȫ��ʵս�����ʮ��֮һ��\n");

        if (me->query_temp("on_combat"))
                return notify_fail("�����������ڼ���ʵս�����У�û�б�Ҫ�ټ���һ�Ρ�\n");

        message_vision(HIR "$N" HIR "ͻȻȫ�����һ���죬��Ŀ��ʱ����"
                       "���䣬һ��һʽ���Գ��Ÿ�����\n" NOR, me);

        me->add("combat_exp",-count);
        count = me->query_skill("force") / 5;
        me->set_temp("combat",count);
        me->add_temp("apply/attack", count);
        me->set_temp("on_combat",1);
	me->set_temp("combating",300+random(300));
	me->apply_condition("combat",1);

	return 1;
}

int help (object me)
{
        write(@HELP
ָ���ʽ: combat [����]
 
���ָ�����㽫���۵�ʵս���鲿��ת��Ϊ��������������һ��ʱ��֮�ڿ�
�Գ�ֵ�������Ĺ���������������Ҫ����100��ʵս���飬 ���û��ָ��
���ĵĵ�����Ĭ��Ϊ100�㣻 ���һ�������Խ�ȫ��ʵս�����ʮ��֮һ
ת��Ϊ��������ֻ�д���ʦ������������

HELP
        );
        return 1;
}
