inherit F_CLEAN_UP;

#ifndef ADV_D
#define ADV_D          "/adm/daemons/advd"
#endif

int main(object me, string arg)
{
        if (! arg || arg == "" || arg == "all")
        {
                ADV_D->show_advs(me, (arg != "all") ? 1 : 0);
                return 1;
        }

	if (arg == "start")
	{
		ADV_D->start_adv();
		write("���ϵͳ������\n");
		return 1;	
	}
	
	if (arg == "stop")
	{
		ADV_D->stop_adv();
		write("���ϵͳֹͣ��\n");
		return 1;
	}
	
        if (sscanf(arg, "discard %s", arg))
        {
                ADV_D->do_discard(me, arg);
                return 1;
        }

        if (sscanf(arg, "post %s", arg))
        {
                ADV_D->do_post(me, arg);
                return 1;
        }
        
	ADV_D->do_read(me, arg);
	
        return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : adv [<all> || <num>] || [post ����] || [discard num]
		|| start || stop

����ָ������ʦ������档

ʹ�� all ������������鿴ϵͳĿǰ���еĹ�棬ָ�����ֿ��Բ鿴��
��������ϸ���ݡ�

adv post <����>��������档
adv discard��ɾ����档
adv start �������ϵͳ��
adv stop  ֹͣ���ϵͳ��

ע�⣺���ı�����Ϊ����ʦ�Ķ��͹���ķ��㣬��沥�͵�ʱ��ֻ����
      ��������ݡ�
HELP );
    return 1;
}
