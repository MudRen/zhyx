// news cmds
// by Doing
 
inherit F_CLEAN_UP;

#ifndef NEWS_D
#define NEWS_D          "/adm/daemons/newsd"
#endif

int main(object me, string arg)
{
        if (! arg || arg == "" || arg == "all")
        {
                NEWS_D->show_news(me, (arg != "all") ? 1 : 0);
                return 1;
        }

        if (sscanf(arg, "discard %s", arg))
        {
                NEWS_D->do_discard(me, arg);
                return 1;
        }

        if (sscanf(arg, "post %s", arg))
        {
                NEWS_D->do_post(me, arg);
                return 1;
        }
        if (sscanf(arg, "search %s", arg)) 
        { 
                NEWS_D->search_content(me, arg); 
                return 1; 
        } 

        NEWS_D->do_read(me, arg);
        return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : 	news [next] | [<���ű��>] | new | all
			news search [�ؼ���]

����ָ������������Ķ���Ϸ�е����š����еĸ��º���Ϣ����ͨ��
���ŷ����ġ�

ʹ�� new �������������Ķ���û�ж��������š�
ʹ�� all ������������鿴ϵͳĿǰ���е����š�

ʹ�� news search [����] ���������������ϵͳ�к��� �ؼ��� �����е����š�
���磺news search �л�Ӣ�� ϵͳ�᷵�������к��� �л�Ӣ�� ���������š�

��վ����ʦ����ͨ��news post <����>���������š�news discard��
ɾ�����š�
HELP );
    return 1;
}
