// added can't pfm after ����������צ��ȥ�� wsky 7/3/00
// added zouhuo_damage(�߻���ħ) April 2001.09.23
// added ����� April 2001.09.26

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object weapon;
	string martial, skill;
	int result;
	
	seteuid(getuid());

	if (me->is_busy())
		return notify_fail("( ����һ��������û����ɣ�����ʩ���⹦��)\n");

	if( me->query_temp("huagong")) return notify_fail(" ( ���������ۣ����������ڹ���)\n");
	if( me->query_temp("feng")) return notify_fail(" ( �����������ס�ˣ��޷�ʹ�����С�)\n");
	if( me->query_condition("zouhuo_damage"))
		return notify_fail(" ( ���߻���ħ�ˣ��޷������ڹ���)\n");
	if (me->query_temp("armor/embed") == "�����")
		return notify_fail(" ( ���һ�������ڴ����������̣�ֻ�����ա�)\n");

	if (! arg) return notify_fail("��Ҫ���⹦��ʲ�᣿\n");

	if (sscanf(arg, "%s.%s", martial, arg) != 2)
        {
		if (weapon = me->query_temp("weapon"))
			martial = weapon->query("skill_type");
		else
			martial = "unarmed";
	}

	me->clean_up_enemy();
	if (stringp(skill = me->query_skill_mapped(martial)))
        {
		notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");
		if (SKILL_D(skill)->perform_action(me, arg))
                {
			if (random(120) < (int)me->query_skill(skill))
				me->improve_skill(skill, 1, 1);
			return 1;
		} else
                if (SKILL_D(martial)->perform_action(me, arg))
                {
			if (random(120) < (int)me->query_skill(martial, 1))
				me->improve_skill(martial, 1, 1);
			return 1;
		}
		return 0;
	}

	return notify_fail("�����ڵ�" + to_chinese(martial)[4..7] +
			   "(" + martial + ")�в�û�������⹦��\n");
}

int help (object me)
{
        write(@HELP
ָ���ʽ��perfrom | yong [<�书����>.]<��ʽ����> [<ʩ�ö���>]

�������ѧ���⹦(ȭ�š�����������....)��һЩ����Ĺ�����ʽ����ʽ������
�����ָ����ʹ�ã���������� enable ָ��ָ����ʹ�õ��书����ָ���书��
��ʱ�����ֵ��⹦��ָ���ȭ�Ź���ʹ������ʱ���Ǳ��е��书��

��������⹦�������಻ͬ��������ʽ������ͬ�ģ����߲����ȭ�Ÿ���������
���书(���Ṧ)�������� <�书>.<��ʽ>  �ķ�ʽָ�����磺

perform sword.chan

���仰˵��ֻҪ�� enable �е��书��������ʽ�ģ������������ָ��ʹ�á�
HELP
        );
        return 1;
}
