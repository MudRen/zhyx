// ʥ��

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object item;

        if (! arg) return notify_fail("��Ҫʥ��ʲô��Ʒ��\n");

        if (! objectp(item = present(arg, me)))
                return notify_fail("������û��������Ʒ��\n");

        notify_fail(item->name() + "û�а취��ʥ����\n");
        if ( me->is_busy() )
                return notify_fail("����æ��û��ʥ����Ʒ��\n");
        if ( me->is_fighting() )
                return notify_fail("�����ڴ�ܣ���ôʥ����Ʒ��\n");

        // ʥ����Ʒ
        return item->do_san(me);
}

int help(object me)
{
write(@HELP
ָ���ʽ : san <��Ʒ����>
 
���ָ���������ʥ��ĳ����Ʒ����Ȼ�������Ʒ���ܹ�ʥ���ſ��ԣ�
��������Ҫ���㹻������������൱��ľ�����ʥ���Ժ������ʧһ
Щ�����;��������ޡ�

ֵ��ע����ǣ�ʥ��ʱ����������ˮƽû�г�ֶ�������Ŀǰ�ļ�
�ޣ���ʥ��������һ����Σ�գ��п��ܵ�����Ļ����ڹ��ܵ����ˡ�
�����ʥ��ǰ��֤�Լ��������ӽ�ƿ��ֵ�ǿɿ���������
HELP
    );
    return 1;
}