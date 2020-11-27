// banker.c 银行家
// This is a inheritable object.
// Each dealer should support buy, sell, list, value 4 commands

#include <dbase.h>
#include <ansi.h>

int do_check()
{
        // here we use 3 units to display bank infos
        int total = (int)this_player()->query("balance");
        if (!total || total < 0)
        {
                this_player()->set("balance", 0);
                write("您在敝商号没有存钱。\n");
                return 1;
        }
        write(this_object()->query("name")+"悄悄告诉你：您在弊商号共存有" + 
              MONEY_D->money_str(total) + "。\n");
        return 1;                                                               
}

int do_convert(string arg)
{
        string from, to;
        int amount, bv1, bv2;
        object from_ob, to_ob;
        object me;

        me = this_player();                                                     

	if (me->is_busy())
		return notify_fail("你还是等有空了再说吧！\n");

        if (this_object()->is_fighting())
                return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

        if (! arg || sscanf(arg, "%d %s to %s", amount, from, to) != 3)
        {
           	return notify_fail("命令格式：convert|duihuan <数量> <货币单位> to <新货币单位>\n");
        }

        from_ob = present(from + "_money", me);
        to_ob = present(to + "_money", me);

        if (! to_ob && file_size("/clone/money/" + to + ".c") < 0)
           	return notify_fail("你想兑换成什么？\n");

        if (! from_ob)
           	return notify_fail("你身上没有带这种钱。\n");

	if (from_ob == to_ob)
		return notify_fail("你有毛病啊？\n");

        if (amount < 1)
           	return notify_fail("你想白赚啊？\n");

        if ((int)from_ob->query_amount() < amount)
           	return notify_fail("你带的" + from_ob->query("name") +
				   "不够。\n");

        bv1 = from_ob->query("base_value");
        if (! bv1)
           	return notify_fail("这样东西不值钱。\n");

        bv2 = to_ob ? to_ob->query("base_value")
		    : call_other("/clone/money/" + to, "query", "base_value");
        if (bv1 < bv2)  amount -= amount % (bv2 / bv1);
        if (amount == 0)
           	return notify_fail("这些" + from_ob->query("name") +
				   "不够换。\n ");

	if (bv1 > bv2 && bv1 / bv2 * amount > 10000)
		return notify_fail("哦呦...我这一下子还拿不出这么多散钱...\n");

        // allowed to convert now
        me->start_busy(1);

        from_ob->add_amount(-amount);

        if (! to_ob)
        {
                to_ob = new("/clone/money/" + to);
                to_ob->set_amount(amount * bv1 / bv2);
                to_ob->move(me, 1);
        }
        else
                to_ob->add_amount(amount * bv1 / bv2);

        message_vision(sprintf("$N从身上取出%s%s%s，换成了%s%s%s。\n",
        		       chinese_number(amount),
			       from_ob->query("base_unit"),
			       from_ob->query("name"),
        		       chinese_number(amount * bv1 / bv2),
			       to_ob->query("base_unit"),
        		       to_ob->query("name")), me);

        return 1;
}                                                                               

int do_deposit(string arg)                                                      
{
        string what;
        int amount, money_limit;
        object what_ob, me;

        me = this_player();

	if (me->is_busy())
		return notify_fail("你还是等有空了再说吧！\n");

        if (this_object()->is_fighting())
                return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

        if (! arg || sscanf(arg, "%d %s", amount, what) != 2)
                return notify_fail("命令格式：deposit:cun <数量> <货币单位>\n");

        what_ob = present(what + "_money", me);
        if (! what_ob)
                return notify_fail("你身上没有带这种钱。\n");

        if (amount < 1)
                return notify_fail("你想存多少" + what_ob->query("name") +
				   "？\n");

        if ((int)what_ob->query_amount() < amount)
                return notify_fail("你带的" + what_ob->query("name") +
				   "不够。\n");

        // deposit it
        me->start_busy(1);

        me->add("balance", what_ob->query("base_value") * amount);
        what_ob->add_amount(-amount);
        message_vision(sprintf("$N拿出%s%s%s，存进了银号。\n",
        chinese_number(amount), what_ob->query("base_unit"),
        what_ob->query("name")), me);

        return 1;
}

int do_withdraw(string arg)
{
        string what;
        int amount, money_limit;
        object what_ob, me;
        int v;

        me = this_player();

	if (me->is_busy())
		return notify_fail("你还是等有空了再说吧！\n");

        if (this_object()->is_fighting())
                return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

        if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
                return notify_fail("命令格式：withdraw|qu <数量> <货币单位>\n");

        if (amount < 1)
                return notify_fail("你想取出多少钱？\n");

        if(amount >= 10000)
                return notify_fail("这么大的数目。本店没这么多零散现金。\n");

        if (file_size("/clone/money/" + what + ".c") < 0)
                return notify_fail("你想取出什么钱？\n");

        what = "/clone/money/" + what;
        if ((v = amount * what->query("base_value")) > me->query("balance") ||
            v <= 0)
               return notify_fail("你存的钱不够取。\n");

        me->start_busy(1);

        me->add("balance",  -v);
        MONEY_D->pay_player(me, v);

        message_vision(sprintf("$N从银号里取出%s。\n", MONEY_D->money_str(v)), me);

        return 1;
}

int do_bcun(string arg)                                                      
{
        string what;
        int amount, money_limit;
        object what_ob, me;

        me = this_player();

        if (me->is_busy())
                return notify_fail("你还是等有空了再说吧！\n");

        if (this_object()->is_fighting())
                return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

        if (!me->query("party/party_name"))
                return notify_fail("你还没有加入任何帮派，往哪里存钱啊？\n");

        if (! arg || sscanf(arg, "%d %s", amount, what) != 2)
                return notify_fail("命令格式：bcun <数量> <货币单位>\n");

        what_ob = present(what + "_money", me);
        if (! what_ob)
                return notify_fail("你身上没有带这种钱。\n");

        if (amount < 1)
                return notify_fail("你想存多少" + what_ob->query("name") +
                                   "？\n");

        if ((int)what_ob->query_amount() < amount)
                return notify_fail("你带的" + what_ob->query("name") +
                                   "不够。\n");

        // deposit it
        me->start_busy(3);

        BANG_D->cun_money_to_party(me, what_ob->query("base_value") * amount);
        what_ob->add_amount(-amount);
        message_vision(sprintf("$N拿出%s%s%s，存进了银号。\n",
        chinese_number(amount), what_ob->query("base_unit"),
        what_ob->query("name")), me);

        return 1;
}

int do_bqu(string arg)
{
        string what, str;
        int amount, money_limit;
        object what_ob, me;
        int v,me_right,all_count;

        me = this_player();

        if (me->is_busy())
                return notify_fail("你还是等有空了再说吧！\n");

        if (this_object()->is_fighting())
                return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

        if (!(me_right = (int)me->query("party/right")))
                return notify_fail("你并没有加入任何帮派，取什么啊？莫非想偷钱？\n");
                
        if (me_right != 1)
                return notify_fail("你不是帮主，没有权利从帮会提取钱款！\n");

        if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
                return notify_fail("命令格式：bqu <数量> <货币单位>\n");

        if (amount < 1)
                return notify_fail("你想取出多少钱？\n");

        if(amount >= 10000)
                return notify_fail("这么大的数目。本店没这么多零散现金。\n");

        if (file_size("/clone/money/" + what + ".c") < 0)
                return notify_fail("你想取出什么钱？\n");

        what = "/clone/money/" + what;
        all_count = BANG_D->check_party_money(me->query("party/party_name"));

        if ((v = amount * what->query("base_value")) > all_count || v <= 0)
               return notify_fail("你存的钱不够取。\n");

        me->start_busy(2);

        BANG_D->qu_money_from_party(me, v);
        MONEY_D->pay_player(me, v);
        message_vision(sprintf("$N从银号里取出%s。\n", MONEY_D->money_str(v)), me);

        str = "取款：" + me->name(1) + "于" + NATURE_D->game_time() + "取出帮会存款" +
              MONEY_D->money_str(v) + "。\n";
        BANG_D->party_save_record(me->query("party/party_name"), str);
        return 1;
}

int do_bcheck(string arg)
{
        object me;
        string str, *ids, tmp;
        int i, all_money;
        mapping member;

        me = this_player();
        if (! me->query("party/party_name"))
                return notify_fail("你还没有加入任何帮会，查什么帐户？\n");

        if (me->query("party/right") > 2)
                return notify_fail("你在帮会中的地位太低，无权查询本帮帐户！\n");

        if (! arg)
        {
                all_money = BANG_D->check_party_money(me->query("party/party_name"));
                if (all_money > 0)
                        str = sprintf("%s目前本帮共有资金：%s。%s\n", HIY,
                                      MONEY_D->money_str(all_money), NOR);
                else    str = "本帮目前还没有存款。\n";
        }
        else if (arg == "detail")
        {
                member = BANG_D->query_members(me);
                ids = keys(member);
                str = HIY "\n本帮成员向帮会存款明细\n" NOR;
                str += "================================\n";
                for(i=0; i<sizeof(ids); i++)
                {
                        if (member[ids[i]][2] > 0)
                        {
                                tmp = member[ids[i]][1] + "(" + ids[i] + ")";
                                str += sprintf("%s%-20s %-40s%s\n", HIY, tmp,
                                "共存入：" + MONEY_D->money_str(member[ids[i]][2]), NOR);
                        }
                }
        } else
                str = "你要查看什么？\n";

        me->start_more(str);
        return 1;
}

