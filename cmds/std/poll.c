// Create by Rcwiz for Hero 2003
// Command of Voting System

#include <net/dns.h>
#include <ansi.h>

inherit F_CLEAN_UP;

#define POLL_D "/adm/daemons/polld"

int help(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object victim;
	string para, target, kind;
        string* kinds;
        int n;

	if (((int) me->query("age") < 18) 
          && ! wizardp(me)
          && arg != "now"
          && arg != "history" )
           	    return notify_fail("�������Ƕ�Ϸ��С����һ����ȥ��\n");

    if (me->query("combat_exp") < 1000000 
        && ! wizardp(me)
        && arg != "now"
        && arg != "history" )
                return notify_fail("Ŀǰֻ����ʵս������100�����ϵ�IDͶƱ��\n");

	if ((int) me->query("vote/deprived"))
        {
                // �Ƿ񱻰���ͶƱȨ����û�лָ��أ�
                if (time() - me->query("vote/deprived") >= 86400)
                        me->delete("vote/deprived");
                else
		        return notify_fail("�����𵱳���Ū������������ͶƱȨ���£�׷��Ī����\n");
        }
       
        if (! arg)return help(me);

        if (arg == "history")
        {
                POLL_D->show_voting(me, "history");
                return 1;
        }
        if (arg == "now")
        {
                POLL_D->show_voting(me, "now");
                return 1;               
        }
        
        if (arg == "end")
        {
                POLL_D->end_voting(me);
                return 1;
        }

        sscanf(arg, "%s %s %s", para, target, kind);

        switch (para)
        {
                case "shot":
                       sscanf(arg, "%s %s", para, kind);
                       if (! POLL_D->query_now_voting_class(kind) )
                       {
                             write(HIR "\n���������ͶƱ��\n" NOR);
                             POLL_D->show_voting(me, "now");
                             break;
                       }
                       POLL_D->shot_target(me, kind);
                       break;
               
                case "start":
                       if (sscanf(arg, "%s %s %s", para, target, kind) != 3)
                              return help(me);

                       POLL_D->start_voting(me, target, kind);
                       break;
 
                default:
                       return help(me);
        }

	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : poll shot          <����>   �� ����ͶƱ
                start  <Ŀ��> <����>   �� ����ͶƱ
                end                    �� ����ͶƱ
                history                �� ��ʾ��ʷͶƱ��¼
                now                    �� ��ʾ��ǰͶƱ��Ϣ

���統ǰ���ڶ�XXXͶƱ��ͶƱ����Ϊ���ã�һ�㣬�����ô
�����ҪͶXXXΪ���á�����

           poll shot XXX ��

��ʦ��ʹ�� poll start <Ŀ��> <����>����ʱ�����翪ʼ��
���Ƿ�ͬ�⿪��XXX���ɡ�����ͶƱ��ͶƱ����Ϊ�����ǡ��͡���
���ʱ����ӦΪ��

           poll start �Ƿ�ͬ�⿪��XXX���� ��:��

��ͶƱ��������á�:�����ŷֿ���


HELP );
    return 1;
}
