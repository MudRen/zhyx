// banker.c ���м�
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
                write("���ڱ��̺�û�д�Ǯ��\n");
                return 1;
        }
        write(this_object()->query("name")+"���ĸ����㣺���ڱ��̺Ź�����" + 
              MONEY_D->money_str(total) + "��\n");
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
		return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

        if (this_object()->is_fighting())
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

        if (! arg || sscanf(arg, "%d %s to %s", amount, from, to) != 3)
        {
           	return notify_fail("�����ʽ��convert|duihuan <����> <���ҵ�λ> to <�»��ҵ�λ>\n");
        }

        from_ob = present(from + "_money", me);
        to_ob = present(to + "_money", me);

        if (! to_ob && file_size("/clone/money/" + to + ".c") < 0)
           	return notify_fail("����һ���ʲô��\n");

        if (! from_ob)
           	return notify_fail("������û�д�����Ǯ��\n");

	if (from_ob == to_ob)
		return notify_fail("����ë������\n");

        if (amount < 1)
           	return notify_fail("�����׬����\n");

        if ((int)from_ob->query_amount() < amount)
           	return notify_fail("�����" + from_ob->query("name") +
				   "������\n");

        bv1 = from_ob->query("base_value");
        if (! bv1)
           	return notify_fail("����������ֵǮ��\n");

        bv2 = to_ob ? to_ob->query("base_value")
		    : call_other("/clone/money/" + to, "query", "base_value");
        if (bv1 < bv2)  amount -= amount % (bv2 / bv1);
        if (amount == 0)
           	return notify_fail("��Щ" + from_ob->query("name") +
				   "��������\n ");

	if (bv1 > bv2 && bv1 / bv2 * amount > 10000)
		return notify_fail("Ŷ��...����һ���ӻ��ò�����ô��ɢǮ...\n");

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

        message_vision(sprintf("$N������ȡ��%s%s%s��������%s%s%s��\n",
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
		return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

        if (this_object()->is_fighting())
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

        if (! arg || sscanf(arg, "%d %s", amount, what) != 2)
                return notify_fail("�����ʽ��deposit:cun <����> <���ҵ�λ>\n");

        what_ob = present(what + "_money", me);
        if (! what_ob)
                return notify_fail("������û�д�����Ǯ��\n");

        if (amount < 1)
                return notify_fail("��������" + what_ob->query("name") +
				   "��\n");

        if ((int)what_ob->query_amount() < amount)
                return notify_fail("�����" + what_ob->query("name") +
				   "������\n");

        // deposit it
        me->start_busy(1);

        me->add("balance", what_ob->query("base_value") * amount);
        what_ob->add_amount(-amount);
        message_vision(sprintf("$N�ó�%s%s%s����������š�\n",
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
		return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

        if (this_object()->is_fighting())
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

        if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
                return notify_fail("�����ʽ��withdraw|qu <����> <���ҵ�λ>\n");

        if (amount < 1)
                return notify_fail("����ȡ������Ǯ��\n");

        if(amount >= 10000)
                return notify_fail("��ô�����Ŀ������û��ô����ɢ�ֽ�\n");

        if (file_size("/clone/money/" + what + ".c") < 0)
                return notify_fail("����ȡ��ʲôǮ��\n");

        what = "/clone/money/" + what;
        if ((v = amount * what->query("base_value")) > me->query("balance") ||
            v <= 0)
               return notify_fail("����Ǯ����ȡ��\n");

        me->start_busy(1);

        me->add("balance",  -v);
        MONEY_D->pay_player(me, v);

        message_vision(sprintf("$N��������ȡ��%s��\n", MONEY_D->money_str(v)), me);

        return 1;
}

int do_bcun(string arg)                                                      
{
        string what;
        int amount, money_limit;
        object what_ob, me;

        me = this_player();

        if (me->is_busy())
                return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

        if (this_object()->is_fighting())
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

        if (!me->query("party/party_name"))
                return notify_fail("�㻹û�м����κΰ��ɣ��������Ǯ����\n");

        if (! arg || sscanf(arg, "%d %s", amount, what) != 2)
                return notify_fail("�����ʽ��bcun <����> <���ҵ�λ>\n");

        what_ob = present(what + "_money", me);
        if (! what_ob)
                return notify_fail("������û�д�����Ǯ��\n");

        if (amount < 1)
                return notify_fail("��������" + what_ob->query("name") +
                                   "��\n");

        if ((int)what_ob->query_amount() < amount)
                return notify_fail("�����" + what_ob->query("name") +
                                   "������\n");

        // deposit it
        me->start_busy(3);

        BANG_D->cun_money_to_party(me, what_ob->query("base_value") * amount);
        what_ob->add_amount(-amount);
        message_vision(sprintf("$N�ó�%s%s%s����������š�\n",
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
                return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

        if (this_object()->is_fighting())
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

        if (!(me_right = (int)me->query("party/right")))
                return notify_fail("�㲢û�м����κΰ��ɣ�ȡʲô����Ī����͵Ǯ��\n");
                
        if (me_right != 1)
                return notify_fail("�㲻�ǰ�����û��Ȩ���Ӱ����ȡǮ�\n");

        if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
                return notify_fail("�����ʽ��bqu <����> <���ҵ�λ>\n");

        if (amount < 1)
                return notify_fail("����ȡ������Ǯ��\n");

        if(amount >= 10000)
                return notify_fail("��ô�����Ŀ������û��ô����ɢ�ֽ�\n");

        if (file_size("/clone/money/" + what + ".c") < 0)
                return notify_fail("����ȡ��ʲôǮ��\n");

        what = "/clone/money/" + what;
        all_count = BANG_D->check_party_money(me->query("party/party_name"));

        if ((v = amount * what->query("base_value")) > all_count || v <= 0)
               return notify_fail("����Ǯ����ȡ��\n");

        me->start_busy(2);

        BANG_D->qu_money_from_party(me, v);
        MONEY_D->pay_player(me, v);
        message_vision(sprintf("$N��������ȡ��%s��\n", MONEY_D->money_str(v)), me);

        str = "ȡ�" + me->name(1) + "��" + NATURE_D->game_time() + "ȡ�������" +
              MONEY_D->money_str(v) + "��\n";
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
                return notify_fail("�㻹û�м����κΰ�ᣬ��ʲô�ʻ���\n");

        if (me->query("party/right") > 2)
                return notify_fail("���ڰ���еĵ�λ̫�ͣ���Ȩ��ѯ�����ʻ���\n");

        if (! arg)
        {
                all_money = BANG_D->check_party_money(me->query("party/party_name"));
                if (all_money > 0)
                        str = sprintf("%sĿǰ���ﹲ���ʽ�%s��%s\n", HIY,
                                      MONEY_D->money_str(all_money), NOR);
                else    str = "����Ŀǰ��û�д�\n";
        }
        else if (arg == "detail")
        {
                member = BANG_D->query_members(me);
                ids = keys(member);
                str = HIY "\n�����Ա��������ϸ\n" NOR;
                str += "================================\n";
                for(i=0; i<sizeof(ids); i++)
                {
                        if (member[ids[i]][2] > 0)
                        {
                                tmp = member[ids[i]][1] + "(" + ids[i] + ")";
                                str += sprintf("%s%-20s %-40s%s\n", HIY, tmp,
                                "�����룺" + MONEY_D->money_str(member[ids[i]][2]), NOR);
                        }
                }
        } else
                str = "��Ҫ�鿴ʲô��\n";

        me->start_more(str);
        return 1;
}

