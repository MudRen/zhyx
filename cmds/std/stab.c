// stab.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object obj;

	if (! arg)
                return notify_fail("��Ҫ��ʲô��Ʒ��\n");

	if (! objectp(obj = present(arg, me)))
		return notify_fail("������û������������\n");

  	if ( environment(me)->query("no_stab") )
		return notify_fail("���ﲻ�ܲ嶫����\n");

        notify_fail("�㷭����ȥ��Ū��һ�����Ҳû�����ں�" + obj->name() + "��\n");
        return obj->do_stab(me);
}

int help(object me)
{
	write(@HELP
ָ���ʽ : stab <��Ʒ����>
 
���ָ��������㽫ĳ���������ڵ����ϣ������־��ʲô�ġ�
 
HELP );
        return 1;
}
