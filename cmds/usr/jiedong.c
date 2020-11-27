// jiedong.c

inherit F_CLEAN_UP;
 
int main(object me, string arg)
{
        object ob;
 
        if (me != this_player(1)) return 0;

                if (!arg) return notify_fail("��ʽ:jiedong <id>\n");

        if (stringp(arg))
        {
                seteuid(getuid());
                ob = find_player(arg);
                if (! ob)
                {
                        ob = new(LOGIN_OB);
                        ob->set("id", arg);
                        if (! ob->restore())
                        {
                                destruct(ob);
                                return notify_fail("û�������ҡ�\n");
                        }
                        ob->set_temp("create_temp", 1);
                } else
                {
                        ob = ob->query_temp("link_ob");
                        while (ob && ob->is_character())
                                ob = ob->query_temp("link_ob");
                        if (! ob)
                                return notify_fail("�������ȱ��������Ϣ��������LOGIN��\n");
                }

                                
                                if (!ob->query("is_dongjie"))
				{
					destruct(ob);
					return notify_fail("��IDû�б����ᰡ����\n");
				}
				if ((int)ob->query("dongjie_time") > time() && !wizardp(me))
				{
					destruct(ob);
return notify_fail("�������ID��Ҫ���������ܽ��нⶳ!\n");
				}

                write("������(" + ob->query("id") + ")�Ķ������룺");
                input_to("get_jiedong_pass",1,me,ob);
                return 1;
        }

}

private void get_jiedong_pass(string pass, object me, object ob)
{
        string old_pass;
        object link_ob;

        write("\n");
                //��鶳�������Ƿ���ȷ
        old_pass = ob->query("djpassword");
        if (crypt(pass, old_pass) != old_pass)
        {
                write("�������\n");
                return;
        }
                //���Խⶳ�û�
	        if (! ob->delete("is_dongjie"))
        {
                write("�ⶳ�û�ʧ�ܣ�\n");
                return;
        }

                //��ʼ���͸���˽�ˡ�������Ϣ
        tell_object(me, "����û�" + ob->query("id") + "�ⶳ�ˣ�\n"); 
        CHANNEL_D->do_channel(this_object(), "rumor", 
                                sprintf("��˵�û�%s��%s�ⶳ�ˡ�",
				ob->query("id"),me->name()));

	catch(ob->save());
        if (ob->query_temp("create_temp"))
                destruct(ob);
}

int help(object me)
{
        write(@HELP
ָ���ʽ : jiedong <id>
 
���ָ����Խⶳָ��ID��
���ⶳ��ID��������ʹ�õ�¼�����¼ϵͳ��
 
HELP );
    return 1;
}


