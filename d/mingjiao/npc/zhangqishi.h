// ZhangQiShi.h for fight and get letter from ZhangQiShi
#include "mingjiao.h"

void init()
{
	object me,ob;
	me = this_object () ;
	ob = this_player () ;

	::init();

	if (interactive(this_player()) && this_player()->query_temp("fighting"))
	{
		COMBAT_D->do_attack(this_object(), this_player(), query_temp("weapon") );
		this_player()->add_temp("beat_count", 1);
	}       
}

int accept_object(object ob, object obj)
{
	string name;
	string job_flg;
	object me = this_object();

	mapping ob_family  = ob->query("family");
	name = obj->query("id");	

	if ( name == "huo qiang" && me->query("id") == "xin ran")
	{
		job_flg = judge_jobmsg(ob,1);

		if ( job_flg !=  "�����ǹ" ) 
		{
			command("hmm "+ob->query("id"));
			command("say ����û����������������Ļ�ǹ�����ǹ����Σ�գ����������ˡ�");
			destruct(obj);
			return 1;
		}
		else
		{
			command("thumb "+ob->query("id"));
			command("say ��λ�ֵ�������!��ȥ�ú���Ϣ��Ϣ��");
			destruct(obj);
                        call_out("reward",0,ob,"�����ǹ"); 
			return 1;
		}
	}

	if ( ob->query_temp("have_letter") && present("tuijian xin3", ob) ) 
	{
		command("say �������������ҵ��Ƽ���ȥ����ɢ������ ?");
		return 0;
	}

	if((obj->query("id") == "tieyan ling")
        && ob_family["family_name"] == "����"
	&& ob_family["generation"] == me->query("family/generation") + 1
	&& !ob->query_temp("have_letter") ) 
	{
		ob->set_temp("fight_ok",1);
		command("say �ã���Ȼ�ѵõ�������ɣ����Ǿ�����֤һ���书��");
		remove_call_out("destroying");
		call_out("destroying", 1, me, obj);
		return 1;
	}

	if (obj->query("id") == "tuijian xin2" 
	&& ob->query_temp("have_letter") 
	&& ob_family["generation"] == me->query("family/generation") + 2)
	{
		ob->set_temp("apprentice_ok",1);
	        command("say �ã�" + ob->query("name") + "����Ը�����������");
		remove_call_out("destroying");
		call_out("destroying", 1, me, obj);
		return 1;
	}

       
        command("?");
        command("say �ⶫ�����ҿ�û��ʲ���á�");
	return 0;

}

void destroying(object me, object obj)
{
	destruct(obj);
	return;
}

int accept_fight(object ob)
{
	object me  = this_object();
	
	if ( !ob->query_temp("fight_ok") ) return 0;

	remove_call_out("checking");
	call_out("checking", 1, me, ob);

	ob->delete_temp("fight_ok");
	
	return 1;
}

int checking(object me, object ob)
{

	object obj;
	int my_max_qi, his_max_qi;

	my_max_qi  = me->query("max_qi");
	his_max_qi = ob->query("max_qi");

	if (me->is_fighting()) 
	{
		call_out("checking",2, me, ob);
                return 1;
	}

	if ( !present(ob, environment()) ) return 1; 

	if (( (int)me->query("qi")*100 / my_max_qi) <= 50 ) 
	{
                command("say ������ʤ����������������̵ļѵ��� ! ��ϲ���� !\n");
		message_vision("$N����$nһ���Ƽ��š�\n", me, ob);
		ob->set_temp("have_letter",1);
                obj=new("/d/mingjiao/obj/tuijianxin-3");
		obj->move(ob);
		return 1;
	}

	if (( (int)ob->query("qi")*100 / his_max_qi) < 50 ) 
	{
		command("say ����" + RANK_D->query_respect(ob) + 
                        "���ö����ϰ�������������������г���ͷ�� !\n");
		return 1;
	}

	return 1;  
}

void attempt_apprentice(object ob)
{
	object me;
	mapping ob_family;
	string qi,new_rank;

	me=this_object();

        if (! permit_recruit(ob) )
                return;

        if (!mapp(ob_family=ob->query("family"))||ob_family["family_name"]!="����")
	{
                command("say " + RANK_D->query_respect(ob) + "�뱾��������������֪�˾��Ǻ����⣿");
		return;
	}

	if (me->query("family/generation") >= ob->query("family/generation") )
	{
                command("say " + RANK_D->query_respect(ob) + "����������ҵ� !");
		return;
	}

        if (ob->query("family/generation") == me->query("family/generation") + 1 )
	{
		command("say " + ob->query("family/master_name") + "��ͽ�������ܵ���������ˣ������� !");
		command("recruit " + ob->query("id"));
		return;
	}

        if (ob->query("family/generation") == me->query("family/generation") + 2 )
	{
		if ( ob->query_temp("apprentice_ok") )
		{
			ob->delete_temp("have_letter");
			ob->delete_temp("apprentice_ok");
	
			command("say ������ !");
                        command("say �����ֵ�һ����֮�ţ����ǿ�ϲ�ɺ� !");
			command("recruit " + ob->query("id"));
		}
		else
		{
			command("say " + RANK_D->query_respect(ob) + "����û���Ƽ��ţ�����Խ����ʦ��");
			return;
		}
	}

	return;
}

