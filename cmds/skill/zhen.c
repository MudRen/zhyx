// zhen.c
// by Find.

#undef TEST

/*
zhen ji ����
zhen yq ����
zhen in ����
zhen huan ������
zhen san ��ɢ��
zhen talk ��˵��
zhen check �����쿴��Ա��״̬
*/

inherit F_CLEAN_UP;
private void select_array(string arg,object me,string *ski);
private void build_up(object me,string fn);

nomask int main(object me, string arg)
{
	string usr,*ski,*z_ski = ({});
	int i,n;

#ifdef TEST
	if(!wizardp(me))
		return notify_fail("�����ڼ�ֻ����ʦ��ʹ���󷨡�\n");
#endif

	if(!stringp(arg) || arg =="")
	{
		if(!me->in_array())
			return notify_fail("��Ŀǰû�м����κ��󷨡�\n");
	// �ȼ� 15 ��
	// ��Ԯ��ʱ�������ȼ��ߡ��󷨹���Ч����
		else
		{
			object *memb;
			string out;
			object w;
	
			if( (w = me->query_array_master()) == me)
				out = sprintf("��Ŀǰ�������֡�%s��\n",me->query_array_name());
			else
				out = sprintf("��Ŀǰ����%s���ֵġ�%s����\n",w->name(),me->query_array_name());
	
			memb = me->query_array_member() - ({ me,0 });
	
			if(!sizeof(memb))
				out += "������û��������Ա��\n";
			else
			{
				out += "��Ա�У�\n";
				foreach(object cy in memb)
					out += sprintf("\t%s\n",cy->name());
				out += sprintf("\t%s\n",me->name());
			}

			out += sprintf("��%s��%s��\n",
			me->query_array_name(),
			me->query_array_status()?
				sprintf("���ڷ�������\n�󷨵ȼ�Ϊ��%d",me->query_array_level()):
				"��������û�з��ӳ���");
			write(out);
			return 1;
		}
	}

	if(arg[0..4] == "check")
	{
		object who;

		if(!me->in_array())
			return notify_fail("��Ŀǰû�м����κ��󷨡�\n");

		if(!me->is_array_master())
			return notify_fail("ֻ���������ܲ鿴��Ա��״̬��\n");

		if( !sscanf(arg,"check %s",usr)
		|| !objectp(who = present(usr,environment(me)))
		|| !userp(who) )
			return notify_fail("��Ҫ�鿴�ĸ���Ա��״̬��\n");
		if(!me->is_array_member(who))
			return notify_fail(sprintf("%s���ǡ�%s���ĳ�Ա��\n",
				who->name(),me->query_array_name() ));

		write(sprintf("��%s��%s%s��\n\t��ǰʹ���书Ϊ��%s\n\t��%s���ĵȼ�Ϊ��%d\n\t��%s���ȼ�Ϊ��%d\n",
			who->query_array_name(),
			who == me?"����":"��Ա",
			who->name(),
			to_chinese(who->query_current_skill()),
			who->query_array_name(),
			who->query_skill((who->query_array_fn())->query_array_id(),1),
			to_chinese((who->query_array_fn())->query_array_skill()),
			who->query_skill((who->query_array_fn())->query_array_skill(),1)
			));

		return 1;
	}

	if(arg == "ji")	// ����
	{
		string out;

		if(me->is_fighting())
			return notify_fail("�����ں��˴�ܣ��˲������������顣\n");

		if(me->in_team())
			return notify_fail("�����ڶ����У��޷���֯�󷨡�\n");

		if(me->in_array()) // xx�����xx
		{
			if(me->query_array_master() == me)
				return notify_fail(sprintf("�������������֡�%s����\n",
				me->query_array_name()));
			else
				return notify_fail(sprintf("���Ѿ���%s����ġ�%s���ĳ�Ա�ˡ�\n",
					me->query_array_master()->name(),
					me->query_array_name()));
		}

		if(!(ski = me->query_skills_name()) || !(n = sizeof(ski)))
			return notify_fail("��ʲô�󷨶����ᡣ\n");
		
		for(i=0;i<n;i++)
		{
			string s;
			if(stringp(s=SKILL_D(ski[i])) && s->is_array_skill())
				z_ski += ({ s });
		}
		
		if(!n = sizeof(z_ski))
			return notify_fail("��ʲô�󷨶����ᡣ\n");
		if(n == 1)
		{
			build_up(me,z_ski[0]);
			return 1;
		}
		
		out = "��Ŀǰ���յ����У�\n";
		for(i=0;i<n;i++)
			out += sprintf("\t%d. ��%s��\n",(i+1),z_ski[i]->query_name());
		out += "��ѡ����Ҫ�齨���󷨣�(q�˳�)";
		write(out);
		input_to((: select_array :),me,z_ski);
		return 1;
	}

	if(arg == "san")
		return me->release_array(0);

	if(arg[0..1] == "yq")
	{
		object who;

		if(!me->in_array())
			return notify_fail("��Ŀǰû�м����κ��󷨡�\n");

		if(!me->is_array_master())
			return notify_fail("ֻ���������������������\n");

		if(me->is_fighting())
			return notify_fail("�����ں��˴�ܣ��˲������������顣\n");

		if( !sscanf(arg,"yq %s",usr)
		|| !objectp(who = present(usr,environment(me)))
		|| !userp(who)
		|| (who == me) )
			return notify_fail("��Ҫ����˭����\n");

		if(me->is_array_member(who))	// already in
			return notify_fail(sprintf("%s�Ѿ��������ֵġ�%s�����ˡ�\n",
				who->name(),me->query_array_name()));

#ifdef TEST
		if(userp(who) && !wizardp(who))
			return notify_fail("�����ڼ���ֻ��������ʦ����\n");
#else
		if(wizardp(who))
			return notify_fail("�㲻��������ʦ����\n");
#endif

		if(who->in_team())
			return notify_fail("�Է����������Ķ����У��޷���������󷨡�\n");

		if(!me->can_become_member(who))
			return 0;

		tell_object(who,sprintf("%s���������%s���ֵġ�%s����\n",
			me->name(),
			gender_pronoun(me->query("gender")),
			me->query_array_name() ));

		tell_object(me,sprintf("������%s���������ֵġ�\n",
			who->name(),me->query_array_name()));

		who->set_temp("pending/team",me);
		return 1;
	}

	if(arg == "in")
	{
		object who = me->query_temp("pending/team");

		if(!objectp(who))
			return notify_fail("�㲢û�б��κ�����������󷨡�\n");

		if(me->in_team())
			return notify_fail("�����ڶ����У��޷������������󷨡�\n");

		if(environment(who) != environment(me))
			return notify_fail(sprintf("%s�Ѿ����ˡ�\n",who->name()));

		if(me->in_array())
		{
			if(me->query_array_master() == me)
				return notify_fail(sprintf("���������֡�%s��,�޷������������󷨡�\n",
					me->query_array_name()));
			else
				return notify_fail(sprintf("������%s���ֵġ�%s����,�޷������������󷨡�\n",
					me->query_array_master()->name(),
					me->query_array_name()));
		}

		if(!who->add_array_member(me))
			return 0;

		tell_object(me,sprintf("��Ӧ������%s���ֵġ�%s����\n",
			who->name(),who->query_array_name() ));
		return 1;
	}

	if(arg[0..3] == "talk")
	{
		string msg;
		object *memb;

		if(!me->in_array())
			return notify_fail("��û�����κ���֮�С�\n");

		if(sizeof(memb = me->query_array_member()) < 2)
			return notify_fail(sprintf("��%s����Ŀǰ��û��������Ա��\n",
				me->query_array_name()));

		if(!sscanf(arg,"talk %s",msg))
			msg = "������\n";

		if(msg[<1] != '\n')
			msg += "\n";

		message("tell_object",sprintf("��%s��%s(%s)��%s",
			me->query_array_name(),
			me->name(),
			capitalize(me->query("id")),
			msg ), memb);
		return 1;
	}
        write("�� help zhen ��ô�����ʹ�÷����İ�����\n");
        return 1;
}

private void select_array(string arg,object me,string *ski)
{
	int n,size;

	if(!stringp(arg)
	|| (arg == "")
	|| !me
	|| !arrayp(ski)
	|| !(size = sizeof(ski)))
		return;

	if( (arg[0] == 'q')
	|| (arg[0] == 'Q') )
	{
		tell_object(me,"ok.\n");
		return;
	}

	if(!sscanf("%d",n))
	{
		tell_object(me,"\n��ѡ����Ҫ�齨���󷨣�(q�˳�)");
		input_to((: select_array :),me,ski);
		return;
	}

	n--;

	if( (n < 0) || (n >= size) )
	{
		tell_object(me,"\n��ѡ����Ҫ�齨���󷨣�(q�˳�)");
		input_to((: select_array :),me,ski);
		return;
	}

	build_up(me,ski[n]);
	return;
}

private void build_up(object me,string fn)
{
	if(!me
	|| !stringp(fn)
	|| (file_size(fn+".c") <= 0) )
		return;

	if(!fn->valid_build(me))
		return;

	if(!me->build_up_array(fn))
		return;

	message_vision(sprintf("$N��ʼ��֯��%s����\n",me->query_array_name()),me);
}

int help(object me)
{
   write( @HELP

�󷨲������ʹ�÷������£�

zhen ji
	��ʼ�齨һ����������󷨣������Ҫ�ǻ�
	����󷨣����Զ�����ѡ����Ҫ�齨���󷨡�
	��������Լ�дΪ�� zj

zhen yq <ID>
	������˼����㿪ʼ�齨���󷨣�<ID> ����
	Ҫ�����˵� ID����Ȼ����Ҫ������ת����
	�Ļ���������
	��������Լ�дΪ�� zyq <ID>

zhen in
	������ܵ��˱��˵����룬���Ը��Ļ�����
	�����������������Ρ�
	��������Լ�дΪ�� zin

zhen san
	��ɢĿǰ�������õ��󷨡���ɢ����ֻ������
	��������
	��������Լ�дΪ�� zs

zhen talk
	�Ѿ��齨���󷨳�Ա֮��������������Ի���
	��������Լ�дΪ�� zt

zhen check <ID>
	������������������鵱ǰ�󷨳�Ա��һЩ״
	̬���磺��Ա��ǰ��ʹ�õ��书�����󷨵ĵȼ���
	����Ҫ����书�ĵȼ�������<ID>ΪҪ����
	Ա�� ID��
	��������Լ�дΪ�� zck <ID>

zhen
	�����κβ����� zhen ���������ʾ�㵱ǰ����
	���ε�һЩ״̬���磺������˭��������Щ��Ա��
	�Ƿ�ʼ������������������ɵ��󷨵���Ч��
	���Ƕ��١�����

�����󷨵���ϸ�İ�����Ϣ�� help zhenfa �鿴��

HELP
   );
   return 1;
}
