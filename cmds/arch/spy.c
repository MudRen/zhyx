// spy.c
// by ReyGod  in  12/16/1996  in BUPT

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{	
	object ob;
	mapping mine;
	string line;
	int basic_data;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

	if (! arg)
		ob = me;
	else
        {
		ob = present(arg, environment(me));
		if (! ob) ob = find_player(arg);
		if (! ob) ob = find_living(arg);
		if (! ob) return notify_fail("��Ҫ�쿴˭��״̬��\n");
	}
	
	mine = ob->query_entire_dbase();
	line = sprintf("\n-------��������-------\n");
	line += sprintf(" ������[%s]  ���ԣ�[%s]  ���ǣ�[%s]  ����[%s]  ��ò��[%s]  \n ��Ե��[%s]  ������[%s]  ԪӤ��[%s]  ���أ�[%s]  ת����[%s]\n", 
			sprintf("%3d",mine["str"]),
			sprintf("%3d",mine["int"]),
			sprintf("%3d",mine["con"]),
			sprintf("%3d",mine["dex"]),
			sprintf("%3d",mine["per"]),
			sprintf("%3d",mine["kar"]),
			sprintf("%3d",mine["breakup"]),
			sprintf("%3d",mine["animaout"]),
			sprintf("%3d",mine["death"]),
			sprintf("%3d",mine["reborn"]),);

	line += sprintf("-------��������-------\n");
	line += sprintf(" ������[%s]  ���ԣ�[%s]  ���ǣ�[%s]  ����[%s]  ��ò��[%s]\n\n", 
			sprintf("%3d",ob->query_str()),
			sprintf("%3d",ob->query_int()),
			sprintf("%3d",ob->query_con()),
			sprintf("%3d",ob->query_dex()),
			sprintf("%3d",ob->query_per()));
	line += sprintf(HIC"-------ħ������������ǣ�%s\n\n"NOR, sprintf("%3d",ob->query("con_improve_time")));

	basic_data = mine["str"] + mine["int"] + mine["con"] + mine["dex"];
	if (ob->query("reborn"))
	{
	if (basic_data > (166 + (int)ob->query("con_improve_time")))
 	        line += sprintf(HIY "���������쳣, %3d - 86 = %3d\n\n" NOR, basic_data, (basic_data - 126));
	}else
	{
	if (basic_data > (126 + (int)ob->query("con_improve_time")))
 	        line += sprintf(HIY "���������쳣, %3d - 86 = %3d\n\n" NOR, basic_data, (basic_data - 86));
	}

	write(line);
	return 1;
}
