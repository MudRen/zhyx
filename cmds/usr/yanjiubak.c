
#include <getconfig.h>
#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;

        if (stringp(arg))
        {

                seteuid(getuid());
                ob = find_player(arg);
          if (ob) return notify_fail("����������������!\n");
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
                        {
                                ob = new(LOGIN_OB);
                                ob->set("id", arg);
                                if (! ob->restore())
                                {
                                        destruct(ob);
                		        return notify_fail("�������ȱ��������Ϣ��������LOGIN��\n");
                                }
                                ob->set_temp("create_temp", 1);
                        }
                }

	        write("������(" + ob->query("id") + ")���¹������룺");
        	input_to("get_new_ad_pass", 1, ob);
                return 1;
        }

	ob = me->query_temp("link_ob");
	if (! ob)
		return notify_fail("�������ȱ��������Ϣ��������LOGIN��\n");

	while (ob && ob->is_character()) ob = ob->query_temp("link_ob");

	write("Ϊ�˰�ȫ����������������������룺");
	input_to("get_old_pass", 1, ob);
	return 1;
}

private void get_old_pass(string pass, object ob)
{
	string old_pass;

        if (! objectp(ob))
        {
                write("�޷��ҵ����Ӷ��󣬴˴β�����ֹ�ˡ�\n");
                return;
        }

	write("\n");
	old_pass = ob->query("ad_password");
	if (! stringp(old_pass) || crypt(pass, old_pass) != old_pass)
	{
		write(HIR "���������ע�⣺����Ҫ������ǹ������롣\n" NOR);
		return;
	}
        write("��ѡ������һ��������\n"
              "1. �޸Ĺ�������\n"
              "2. �޸���ͨ����\n"
              "3. ���޸ġ�\n"
              "��ѡ��(����㲻�����������֣���������select1��select2)��");
        
        input_to("select_fun", ob);
}

private void select_fun(string fun, object ob)
{
        if (! objectp(ob))
        {
                write("�޷��ҵ����Ӷ��󣬴˴β�����ֹ�ˡ�\n");
                return;
        }

        switch (fun)
        {
        case "1":
        case "select1":
                write("���������µĹ������룺");
                input_to("get_new_ad_pass", 1, ob);
                return;

        case "2":
        case "select2":
                write("���������µ���ͨ���룺");
                input_to("get_new_pass", 1, ob);
                return;

        case "":
        case "3":
                write("������ϡ�\n");
                return;

        default:
                write("û������ܡ�\n");
                return;
        }
}

string trans_char(int c)
{
        return sprintf("%c ", c);
}

private void get_new_pass(string pass, object ob)
{
        string old_pass;

        if (! objectp(ob))
        {
                write("�޷��ҵ����Ӷ��󣬴˴β�����ֹ�ˡ�\n");
                return;
        }

        if (pass == "")
        {
                write("����ȡ���ˡ�\n");
                return;
        }

        if (strlen(pass) < 3)
        {
                write("�Բ��������ͨ���볤�ȱ��������λ�����������룺");
                input_to("get_new_pass", 1, ob);
                return;
        }

        old_pass = ob->query("ad_password");
        if (stringp(old_pass) && crypt(pass, old_pass) == old_pass)
        {
                write(HIR "\nΪ�˰�ȫ�������ͨ����͹������벻��һ����\n\n" NOR);
                write("���������������ͨ���룺");
                input_to("get_new_pass", 1, ob);
                return;
        }

	write("\n��������һ���µ���ͨ���룺");
	input_to("confirm_new_pass", 1, ob, crypt(pass, 0));
}

private void confirm_new_pass(string pass, object ob, string new_pass)
{
        object me;
        object body;
        string email;
        string msg;

        if (! objectp(ob))
        {
                write("�޷��ҵ����Ӷ��󣬴˴β�����ֹ�ˡ�\n");
                return;
        }

	write("\n");
	if (crypt(pass, new_pass) != new_pass)
	{
		write("�Բ�������������Ĳ�����ͬ�����������������ͨ���룺");
                input_to("get_new_pass", 1, ob);
                return;
	}

	seteuid(getuid());
	if (! ob->set("password", new_pass))
	{
		write("��ͨ������ʧ�ܣ�\n");
		return;
	}

	ob->save();
        me = this_player();
        write("��ͨ�������ɹ���\n");
}

private void get_new_ad_pass(string pass, object ob)
{
        string old_pass;

        if (! objectp(ob))
        {
                write("�޷��ҵ����Ӷ��󣬴˴β�����ֹ�ˡ�\n");
                return;
        }

        if (pass == "")
        {
                write("����ȡ���ˡ�\n");
                return;
        }

        if (strlen(pass) < 5)
        {
                write(HIR "\n�Բ���Ϊ�˰�ȫ����������ͨ���볤�ȱ��������λ��\n\n" NOR);
                write("�����������µĹ������룺");
                input_to("get_new_ad_pass", 1, ob);
                return;
        }

        old_pass = ob->query("password");
        if (stringp(old_pass) && crypt(pass, old_pass) == old_pass)
        {
                write(HIR "\nΪ�˰�ȫ����������������ͨ���벻��һ����\n\n" NOR);
                write("������������Ĺ������룺");
                input_to("get_new_ad_pass", 1, ob);
                return;
        }

	write("\n��������һ���µĹ������룺");
	input_to("confirm_new_ad_pass", 1, ob, crypt(pass, 0));
}

private void confirm_new_ad_pass(string pass, object ob, string new_pass)
{
        object me;
        object body;
        string email;
        string msg;

        if (! objectp(ob))
        {
                write("�޷��ҵ����Ӷ��󣬴˴β�����ֹ�ˡ�\n");
                return;
        }

	write("\n");
	if (crypt(pass, new_pass) != new_pass)
	{
		write("�Բ�������������Ĳ�����ͬ��������������Ĺ������룺");
                input_to("get_new_ad_pass", 1, ob);
		return;
	}

	seteuid(getuid());
	if (! ob->set("ad_password", new_pass))
	{
		write("����������ʧ�ܣ�\n");
		return;
	}

	ob->save();
        me = this_player();
             

        write("��ɹ����޸����û�(" + ob->query("id") + ")�Ĺ������롣\n");

        if (ob->query_temp("create_temp"))
                destruct(ob);
}

