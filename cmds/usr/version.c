// version.c
#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	write(HIY"��"HIR+LOCAL_MUD_NAME()+HIY"��"NOR+"1.0�汾,������"+__VERSION__+"��\n");
	return 1;
}
int help(object me)
{
  write(@HELP
ָ���ʽ : version
 
���ָ�����ʾ��ϷĿǰ���õ� MudOS driver �汾.
 
HELP
    );
    return 1;
}
 
