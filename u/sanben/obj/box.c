//������
//Ϲ��������

#include <ansi.h>

inherit ITEM;

int do_cun(string arg, int all);

void create()
{
    set_name(YEL "���ô�����" NOR, ({"box"}));
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("unit", "��");
        set("long", WHT "���ǹ��ô����䣬���԰�һЩ��Ʒ���������档\n" NOR
                        HIY "ָ���ʽ����:\n"
                        "����������Ʒ cun all\n"
                        "������Ʒ cun <����> <��Ʒ����id>\n"
                        "ȡ����Ʒ qu <����> <��Ʒ���к�>\n"
                        "�����Ʒ check\n\n" NOR);
        set("value", 1);
        set("weight", 100);
        set("no_get", 1);
    }
    setup();
}

void init()
{
    add_action("cun_check", "cun");
    add_action("do_qu", "qu");
    add_action("do_check", "check");
}

int cun_check(string arg)
{
    object me, *inv;
    int num, i, amount;
    string itm;

    me = this_player();

    if (me->is_busy())
        return notify_fail("����æ�����ٴ涫���ɣ�\n");

    if (arg == "all")
    {
        inv = all_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
            amount = 0;

            if (inv[i]->query("base_unit"))
                amount = inv[i]->query_amount();
            else
                amount = 1;

            arg = amount + " " + inv[i]->query("id");
            do_cun(arg, 1);
        }

        tell_object(me, "������������ܴ�Ķ���������˴����䡣\n");

        message("vision", HIC + me->name() + HIC "�ó�һЩ��Ʒ�����˴�����"
                                                 "��\n" NOR,
                environment(me), ({me}));

        me->start_busy(2);
        return 1;
    }

    if (!arg || sscanf(arg, "%d %s", num, itm) != 2)
        return notify_fail("��Ҫ��ʲô��Ʒ����ʽΪcun <����> <��Ʒ����id>\n");

    do_cun(arg, 0);

    me->start_busy(2);

    return 1;
}

int do_cun(string arg, int all)
{
    object ob, me, *inv;
    int num, ttl_amt, i, cun_num, same;
    string itm, *deposit, cun_itm, bs_nm, unit, cun_unit,
        cun_name, cun_id;

    me = this_player();
    same = 0;

    sscanf(arg, "%d %s", num, itm);

    ob = present(itm, me);

    if (!ob)
    {
        write("������û�������Ʒѽ��\n");
        return 1;
    }

    if (ob->is_character())
    {
        if (!all)
            write("������Ҳ��棿��û�и��\n");
        return 1;
    }

    if (!ob->query("can_cun") && file_name(ob)[0..10] != "/clone/fam/" && file_name(ob)[0..13] != "/clone/tattoo/" && file_name(ob)[0..11] != "/clone/gift/" && file_name(ob)[0..15] != "/clone/medicine/" || ob->query("no_cun") || ob->is_container())
    {
        if (!all)
            write("�Բ���������Ʒ���ܴ�ţ�\n");
        return 1;
    }

    if (num < 1)
    {
        write("һ�����ٴ�һ����Ʒ��\n");
        return 1;
    }

    bs_nm = base_name(ob);
    inv = all_inventory(me);

    if (stringp(unit = ob->query("base_unit")))
        ttl_amt = ob->query_amount();

    else
    {
        for (i = 0; i < sizeof(inv); i++)
        {
            if (bs_nm == base_name(inv[i]))
                ttl_amt += 1;
        }
        unit = ob->query("unit");
    }

    if (num > ttl_amt)
    {
        write("������û��ô��" +
              ob->query("name") + NOR "��\n");
        return 1;
    }

    if (!all)
    {
        tell_object(me, "���ó�" + chinese_number(num) + unit +
                            ob->name() + "����˴����䡣\n");

        message("vision", HIC + me->name() + HIC "�ó�һЩ��Ʒ�����˴�����"
                                                 "��\n" NOR,
                environment(me), ({me}));
    }

    if (me->query("deposit"))
        deposit = me->query("deposit");
    else
        deposit = ({});

    for (i = 0; i < sizeof(deposit); i++)
    {
        sscanf(deposit[i], "%s:%d:%s:%s:%s",
               cun_itm, cun_num, cun_unit, cun_name, cun_id);
        if (cun_itm == bs_nm)
        {
            deposit[i] = cun_itm + ":" + (cun_num + num) + ":" + unit + ":" + ob->query("name") + ":" + ob->query("id");
            same = 1;
        }
    }

    if (same != 1)
        deposit += ({bs_nm + ":" + num + ":" + unit +
                     ":" + ob->query("name") + ":" + ob->query("id")});

    me->set("deposit", deposit);

    if (ob->query("base_unit"))
    {
        ob->add_amount(-num);
        if (ob->query_amount() < 1)
            destruct(ob);
    }
    else
    {
        for (i = 0; i < num; i++)
        {
            ob = present(itm, me);
            destruct(ob);
        }
    }
    return 1;
}

int do_qu(string arg)
{
    object ob, me;
    int num, i, cun_num, itm, x;
    string *deposit, cun_itm, unit,
        cun_name, cun_unit, cun_id;

    me = this_player();

    if (!arg || sscanf(arg, "%d %d", num, itm) != 2)
        return notify_fail("��Ҫȡʲô��Ʒ����ʽΪqu <����> <��Ʒ���к�>\n");

    if (me->is_busy())
        return notify_fail("����æ������ȡ�����ɣ�\n");

    deposit = me->query("deposit");

    if (sizeof(deposit) == 0)
        return notify_fail("�����û�涫���������ȡʲôȡ��\n");

    if (num < 1)
        return notify_fail("һ������ȡһ����Ʒ��\n");

    if (num > 50)
        return notify_fail("һ�����ȡ��ʮ����Ʒ��\n");

    if (itm < 1 || itm > sizeof(deposit))
        return notify_fail("��û�д������Ʒ!\n"
                           "��ע���ʽΪqu <����> <��Ʒ���к�>��\n"
                           "��ѯ�����Ʒ���к�������check\n");

    sscanf(deposit[(itm - 1)], "%s:%d:%s:%s:%s",
           cun_itm, cun_num, cun_unit, cun_name, cun_id);

    ob = new (cun_itm);

    if (me->query_encumbrance() + ob->query_weight() * num > me->query_max_encumbrance())
    {
        tell_object(me, "��ĸ��ز������޷�һ��ȡ����ô����Ʒ��\n");
        destruct(ob);
        return 1;
    }

    if (cun_num < num)
    {
        write("��û����ô��" + ob->query("name") + "��\n");
        destruct(ob);
        return 1;
    }

    if (ob->query("base_unit"))
    {
        unit = ob->query("base_unit");
        ob->set_amount(num);
        ob->move(me, 1);
    }
    else
    {
        unit = ob->query("unit");
        destruct(ob);
        for (x = 0; x < num; x++)
        {
            ob = new (cun_itm);
            ob->move(me, 1);
        }
    }

    tell_object(me, "��Ӵ�������ȡ��" + chinese_number(num) + unit +
                        ob->name() + "��\n");

    message("vision", HIC + me->name() + HIC "�Ӵ�����������Щ��������"
                                             "��\n" NOR,
            environment(me), ({me}));

    if (num == cun_num)
        deposit -= ({cun_itm + ":" + cun_num + ":" + cun_unit + ":" + cun_name + ":" + cun_id});
    else
        deposit[(itm - 1)] = cun_itm + ":" + (cun_num - num) + ":" + cun_unit + ":" + cun_name + ":" + cun_id;

    me->set("deposit", deposit);

    me->start_busy(2);

    return 1;
}

int do_check()
{
    int i, cun_num;
    object me = this_player();

    string msg, cun_itm, *deposit = me->query("deposit"),
                         cun_name, cun_unit, cun_id;

    if (me->is_busy())
    {
        write("����æ�����ٲ鶫���ɣ�\n");
        return 1;
    }

    if (sizeof(deposit) == 0)
    {
        tell_object(me, "���ڴ�������ʲôҲû�棡\n");
        return 1;
    }

    msg = "���ڴ��������ŵ���Ʒ���£�\n";

    for (i = 0; i < sizeof(deposit); i++)
    {
        sscanf(deposit[i], "%s:%d:%s:%s:%s",
               cun_itm, cun_num, cun_unit, cun_name, cun_id);

        msg += HIY + (i + 1) + "." + NOR + chinese_number(cun_num) + cun_unit + cun_name + "(" + cun_id + ")" + "\n";
    }

    me->start_more(msg);

    me->start_busy(2);
    return 1;
}
