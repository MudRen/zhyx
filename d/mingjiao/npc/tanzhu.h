// tanzhu.h for join mingjiao 

#include "mingjiao.h"

int do_join(string arg)
{
	object me, ob, obj;
	mapping family;

	me = this_object () ;
	ob = this_player () ;

	if( !arg || arg!="mingjiao" )
		return notify_fail("��Ҫ����ʲô��֯��\n"); 
   	if( ob->query_temp("have_letter") || present("tuijian xin1", ob ))
   	{
                command("say �ð���");
                command("heihei "+ob->query("id") );
		return 1;
	}
   	if( !mapp(family = ob->query("family")) )
   	{
		message_vision("$N���ͷ����$n˵�����ã��㵽����ɽ�ܶ�ȥ�ҽ���ʹ������������̵ġ�\n",me,ob);
		message_vision("$N����$nһ���Ƽ��š�\n", me, ob);
		ob->set_temp("have_letter",1);
                obj=new("/d/mingjiao/obj/tuijianxin-1");
		obj->move(ob);
		return 1;	
	}
   	if( family["family_name"] != "����" )
	{
		message_vision("$Nҡҡͷ����$n˵�������Ѿ��������������ˣ����������ҹ���ʥ�̡�\n",me,ob);
		return 1;
	}
	else
		message_vision("$Nҡҡͷ����$n˵�������Ѿ��������̵����ˡ�\n",me,ob);
	return 1;
}
