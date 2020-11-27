
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
          if (ob) return notify_fail("此人现在正在线上!\n");
                if (! ob)
                {
                        ob = new(LOGIN_OB);
                        ob->set("id", arg);
                        if (! ob->restore())
                        {
                                destruct(ob);
                                return notify_fail("没有这个玩家。\n");
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
                		        return notify_fail("这个人物缺少连接信息，请重新LOGIN。\n");
                                }
                                ob->set_temp("create_temp", 1);
                        }
                }

	        write("请输入(" + ob->query("id") + ")的新管理密码：");
        	input_to("get_new_ad_pass", 1, ob);
                return 1;
        }

	ob = me->query_temp("link_ob");
	if (! ob)
		return notify_fail("你的人物缺少连接信息，请重新LOGIN。\n");

	while (ob && ob->is_character()) ob = ob->query_temp("link_ob");

	write("为了安全起见，请先输入您管理密码：");
	input_to("get_old_pass", 1, ob);
	return 1;
}

private void get_old_pass(string pass, object ob)
{
	string old_pass;

        if (! objectp(ob))
        {
                write("无法找到连接对象，此次操作中止了。\n");
                return;
        }

	write("\n");
	old_pass = ob->query("ad_password");
	if (! stringp(old_pass) || crypt(pass, old_pass) != old_pass)
	{
		write(HIR "密码错误！请注意：你需要输入的是管理密码。\n" NOR);
		return;
	}
        write("请选择你下一步操作：\n"
              "1. 修改管理密码\n"
              "2. 修改普通密码\n"
              "3. 不修改。\n"
              "你选择(如果你不方便输入数字，可以输入select1、select2)：");
        
        input_to("select_fun", ob);
}

private void select_fun(string fun, object ob)
{
        if (! objectp(ob))
        {
                write("无法找到连接对象，此次操作中止了。\n");
                return;
        }

        switch (fun)
        {
        case "1":
        case "select1":
                write("请你输入新的管理密码：");
                input_to("get_new_ad_pass", 1, ob);
                return;

        case "2":
        case "select2":
                write("请你输入新的普通密码：");
                input_to("get_new_pass", 1, ob);
                return;

        case "":
        case "3":
                write("操作完毕。\n");
                return;

        default:
                write("没有这项功能。\n");
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
                write("无法找到连接对象，此次操作中止了。\n");
                return;
        }

        if (pass == "")
        {
                write("操作取消了。\n");
                return;
        }

        if (strlen(pass) < 3)
        {
                write("对不起，你的普通密码长度必须大于三位，请重新输入：");
                input_to("get_new_pass", 1, ob);
                return;
        }

        old_pass = ob->query("ad_password");
        if (stringp(old_pass) && crypt(pass, old_pass) == old_pass)
        {
                write(HIR "\n为了安全起见，普通密码和管理密码不能一样。\n\n" NOR);
                write("请重新输入你的普通密码：");
                input_to("get_new_pass", 1, ob);
                return;
        }

	write("\n请再输入一次新的普通密码：");
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
                write("无法找到连接对象，此次操作中止了。\n");
                return;
        }

	write("\n");
	if (crypt(pass, new_pass) != new_pass)
	{
		write("对不起，您两次输入的并不相同，请重新输入你的普通密码：");
                input_to("get_new_pass", 1, ob);
                return;
	}

	seteuid(getuid());
	if (! ob->set("password", new_pass))
	{
		write("普通密码变更失败！\n");
		return;
	}

	ob->save();
        me = this_player();
        write("普通密码变更成功。\n");
}

private void get_new_ad_pass(string pass, object ob)
{
        string old_pass;

        if (! objectp(ob))
        {
                write("无法找到连接对象，此次操作中止了。\n");
                return;
        }

        if (pass == "")
        {
                write("操作取消了。\n");
                return;
        }

        if (strlen(pass) < 5)
        {
                write(HIR "\n对不起，为了安全起见，你的普通密码长度必须大于五位。\n\n" NOR);
                write("请重新输入新的管理密码：");
                input_to("get_new_ad_pass", 1, ob);
                return;
        }

        old_pass = ob->query("password");
        if (stringp(old_pass) && crypt(pass, old_pass) == old_pass)
        {
                write(HIR "\n为了安全起见，管理密码和普通密码不能一样。\n\n" NOR);
                write("请重新输入你的管理密码：");
                input_to("get_new_ad_pass", 1, ob);
                return;
        }

	write("\n请再输入一次新的管理密码：");
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
                write("无法找到连接对象，此次操作中止了。\n");
                return;
        }

	write("\n");
	if (crypt(pass, new_pass) != new_pass)
	{
		write("对不起，您两次输入的并不相同，请重新输入你的管理密码：");
                input_to("get_new_ad_pass", 1, ob);
		return;
	}

	seteuid(getuid());
	if (! ob->set("ad_password", new_pass))
	{
		write("管理密码变更失败！\n");
		return;
	}

	ob->save();
        me = this_player();
             

        write("你成功的修改了用户(" + ob->query("id") + ")的管理密码。\n");

        if (ob->query_temp("create_temp"))
                destruct(ob);
}

