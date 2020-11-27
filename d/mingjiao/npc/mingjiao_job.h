// Code of JHSH
// mingjiao job file

#include <ansi.h>
#define OBJ_PATH "/d/mingjiao/obj"
#define MINGJIAO "/d/mingjiao/"
#include "/d/mingjiao/obj/time_all.h"
#define BASE 80

string judge_jobmsg(object player,int flg)
{
	string s_msg,job_msg,job_flg;
	s_msg=player->query("mingjiao/job");
	
	switch (s_msg)
	{
		case "jin_caikuang":
			job_flg="�ɼ�����";break;

		case "huo_zaoqiang":
			job_flg="�����ǹ";break;

		case "shui_tiaoshui":
			job_flg="��ˮ";break;

		case "mu_kanshu":
			job_flg="����";	break;

		case "tu_didao":
			job_flg="�ڵص�"; break;

//		default:
//			job_msg="��λ"+RANK_D->query_respect(player)+"���ں���û����������";
//			return job_msg;
//			write("judge_jobmsg reached default! please report.\n");
	}
	
	if(flg)
	return job_flg;

	job_msg="��λ"+RANK_D->query_respect(player)+"���ڲ���"+job_flg+"�𣿵������������ȡ��������ɡ�";
	return job_msg;
}

int cut_abandon_jl(string job_kind)
{
	int old_cc,cut_cc;
	old_cc=this_player()->query("mingjiao/cc");
	
	switch (job_kind)
	{
		case "�ɼ�����":
			cut_cc=BASE+random(BASE*2)/2; break;
		case "�����ǹ":
			cut_cc=BASE+random(BASE*3)/2; break;
		case "��ˮ":
			cut_cc=BASE+random(BASE*3)/2; break;
		case "����":
			cut_cc=BASE+random(BASE*2)/2; break;
		case "�ڵص�":
			cut_cc=BASE+random(BASE*2)/2; break;
	}

	this_player()->add("mingjiao/cc",-cut_cc);
	tell_object(this_player(),RED"��������ҳ϶��½���"+cut_cc+"�㡣\n"NOR);

	this_player()->delete("mingjiao/job");

	return 1;
}




string ask_abandon()
{
	object player;
	string job_flg, id, name;
	player=this_player();
	
	if(!player->query("mingjiao/job"))
		return "��λ"+RANK_D->query_respect(player)+"���ں���û����������";

	job_flg=judge_jobmsg(player,1);

	switch (job_flg)
	{
		case "�ɼ�����":
			id = "zhuang zheng"; name = "ׯ�"; break;
		case "�����ǹ":
			id = "xin ran"; name = "��Ȼ"; break;
		case "��ˮ":
			id = "tang yang"; name = "����"; break;
		case "����":
			id = "wen cangsong"; name = "�Ų���"; break;
		case "�ڵص�":
			player->delete_temp("didao_done");
			id = "yan yuan"; name = "��ԫ"; break;
	}

	if(this_object()->query("id")==id && this_object()->query("name")==name)
	{
		if(cut_abandon_jl(job_flg))
			return "�������������鶼�첻�ã�������ι���ҹ���ʥ��̡�";				
		else				
			return "���¾�������������ɡ�";
	}
	else
		return "��Ȼ��λ"+RANK_D->query_respect(player)+"�����"+job_flg+"��������ȥ��"+name+"����˵һ����";

	return "ask_abandon() has error!";
}



void reward(object me, string job_flg)
{
	int old_cc,add_cc,max_pot,old_pot,add_exp,add_pot;

	if (!me) return;

	old_cc=me->query("mingjiao/cc");
	old_pot=me->query("potential");

	switch(job_flg)
	{
		case "�ɼ�����":
			add_cc=BASE+random(BASE*2)/2;		// BASE = 100
			add_exp=BASE+random(add_cc);
			add_pot=add_exp/3+random(add_exp/4);
			break;
		case "�����ǹ":
			add_cc=BASE+random(BASE*3)/2;
			add_exp=BASE+random(add_cc);
			add_pot=add_exp/3+random(add_exp/4);
			break;
		case "��ˮ":
			add_cc=BASE+random(BASE*3)/2;
			add_exp=BASE+random(add_cc);
			add_pot=add_exp/3+random(add_exp/4);
			break;
		case "����":
			add_cc=BASE+random(BASE*2)/2;
			add_exp=BASE+random(add_cc);
			add_pot=add_exp/3+random(add_exp/4);
			break;
		case "�ڵص�":
			add_cc=BASE+random(BASE*2)/2;
			add_exp=BASE+random(add_cc);
			add_pot=add_exp/3+random(add_exp/4);
			break;
	}			

	me->delete("mingjiao/job");

	me->add("mingjiao/cc",add_cc);
	me->add("combat_exp",add_exp);
	me->add("potential",add_pot);
	if (me->query("potential") > me->query_potential_limit() )
		me->set("potential",me->query_potential_limit() );
	tell_object(me,HIG"��ϲ����������ҳ϶�������"+add_cc+"�㡣\n"NOR);
	tell_object(me,HIG"��ľ���������"+add_exp+"�㡣\n"NOR);
	tell_object(me,HIG"���Ǳ��������"+(((me->query("potential")-old_pot) < 0 ) ? 0 : (me->query("potential")-old_pot))+"�㡣\n"NOR);

}
