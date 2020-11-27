// MenZhu.h for fight and get letter from MenZhu
#include "mingjiao.h"

int accept_object(object ob, object obj)
{
	object me = this_object();

	mapping ob_family  = ob->query("family");

	if ( ob->query_temp("have_letter") && present("tuijian xin2", ob) ) 
	{
		command("say �������������ҵ��Ƽ���ȥ������ʹ���� ?");
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
		obj=new("/d/mingjiao/obj/tuijianxin-2");
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
	object me  = this_object();
	string mingjiao_party;

        if (! permit_recruit(ob) )
                return;

	mingjiao_party = ob->query("can_apprentice_menzhu");

        if (ob->query("family/family_name") && ob->query("family/family_name") != "����")
	{
                command("say " + RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
		return;
	}

	if (!mapp(ob->query("family")) && !stringp(mingjiao_party))
	{
                command("say " + RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
		return;
	}

	if (!mapp(ob->query("family")))
	{
		command("say ԭ���ǽ���ʹ�߽������İ�����ô��͸�����ѧ�㹦��ɣ�\n");
		command("hehe");
		command("recruit " + ob->query("id"));
		return;
	}		

	if (me->query("family/generation") >= ob->query("family/generation") )
	{
                command("say " + RANK_D->query_respect(ob) + "����������ҵ� !");
		return;
	}

        if ( ob->query("family/generation") == me->query("family/generation") + 1 )
	{
		command("say " + ob->query("family/master_name") + "��ͽ�������ܵ���������ˣ������� !");
		command("recruit " + ob->query("id"));
	}

	return;
}
