// nick.c
// by jackyboy @ cctx 98/12/12
#include <ansi.h>

inherit F_CLEAN_UP;
//string replace_color(string,int);
//�˺������ƶ���/adm/simul_efun/message.c����Ϊsim_efunʹ�ã�
//����ڶ�������Ϊ0��ʾ�����ɫ���ƣ�����Ϊ��$HIW$���ַ����滻Ϊ��ɫ���ƴ���
int help();
int wiz_set(string,string,string,int);

int main(object me, string arg)
{
	string dest;
	if(!arg) return help();
	if(sscanf(arg,"-title %s,%s",dest,arg)==2)
	{
		if(!wizardp(me))
			return notify_fail("�������ֻ������ʦʹ�á�\n");
		if(wiz_level(me)<wiz_level("(arch)")&&(dest!="me"&&dest!=me->query("id")))
			return notify_fail("���Ȩ�޲����������������\n");
		return wiz_set(dest,arg,"title",1)?1:notify_fail("����ʧ�ܡ�\n");
	}
	if(sscanf(arg,"-name %s,%s",dest,arg)==2)
	{
		if(!wizardp(me))
			return notify_fail("�������ֻ������ʦʹ�á�\n");
		if(wiz_level(me)<wiz_level("(arch)")&&(dest!="me"&&dest!=me->query("id")))
			return notify_fail("���Ȩ�޲����������������\n");
		return wiz_set(dest,arg,"name",0)?1:notify_fail("����ʧ�ܡ�\n");
	}
	if(sscanf(arg,"-id %s,%s",dest,arg)==2)
	{
		if(wiz_level(me)<wiz_level("(arch)"))
			return notify_fail("�������ֻ���ɻ���������ִ�С�\n");
		return wiz_set(dest,arg,"id",0)?1:notify_fail("����ʧ�ܡ�\n");
	}
	if(sscanf(arg,"-nick %*s")==1)
		sscanf(arg,"-nick %s",arg);
	if(sscanf(arg,"%s,%s",dest,arg)==2)
	{
		if(wiz_level(me)<wiz_level("(apprentice)"))
			return notify_fail("�������ֻ����С�����ϼ������ʦִ�С�\n");
		return wiz_set(dest,arg,"nickname",1)?1:notify_fail("����ʧ�ܡ�\n");
	}
             if (strlen(filter_color(arg)) > 500) 
              me->set("nickname", arg + NOR); 
              write("��ȡ���˴ºš�\n"); 
             return 1; 
                  }

int help()
{
	write(@HELP
ָ���ʽ : 
nick <�º�> (��������ͨ���)
nick -title <id>,<�ִ�>	��idΪ<id>����ҡ�NPC��OBJECT�趨title���� (������wiz)
nick -name  <id>,<�ִ�>	��idΪ<id>����ҡ�NPC��OBJECT�趨name���� (������wiz)
nick -id    <id>,<�ִ�>	��idΪ<id>����ҡ�NPC��OBJECT�趨id���� (������wiz)
nick <id>,<�º�>,	��idΪ<id>����ҡ�NPC��OBJECT�趨id���� (������wiz)
����hufa���¼�����ʦֻ�������Լ���tilte��name��
�κ�һ��������ܶԸ��߼������ʦ�����޸ġ�
�����ϣ��ʹ�� ANSI �Ŀ�����Ԫ�ı���ɫ�����������µĿ����ִ���
$BLK$ - ��ɫ		$NOR$ - �ָ�������ɫ
$RED$ - ��ɫ		$HIR$ - ����ɫ
$GRN$ - ��ɫ		$HIG$ - ����ɫ
$YEL$ - ����ɫ		$HIY$ - ��ɫ
$BLU$ - ����ɫ		$HIB$ - ��ɫ
$MAG$ - ǳ��ɫ		$HIM$ - �ۺ�ɫ
$CYN$ - ����ɫ		$HIC$ - ����ɫ
$WHT$ - ǳ��ɫ		$HIW$ - ��ɫ
$BLINK$ - �ַ���˸
����ϵͳ�Զ������ִ�β�˼�һ�� $NOR$��
�ִ���º�Ϊcancelʱ��ȡ���������ԣ����ֻ��ȡ��<�º�>��
By JackyBoy @ CCTX 98/12/12
HELP
	);
	return 1;
}
