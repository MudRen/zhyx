
inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object obj;

        if (! arg)return notify_fail("��Ҫ����˭��\n");

        if (! objectp(obj = present(arg, environment(me))))
                return notify_fail("����û������ˡ�\n");

        if (obj->query_temp("need_accede/user") != me->query("id"))    
               return notify_fail("����˲���Ҫ�������\n");
        
        ULTRA_D->need_accede(obj, me);

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : accede <id>

���ض��ģΣУñ��Ի��߰����ض��ΣУá�

HELP
    );
    return 1;
}
 