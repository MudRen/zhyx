//������

#include <ansi.h>

inherit ITEM;
inherit F_SAVE;

nosave int load;
int do_cun(string arg, int all);

void create()
{

        set_name(HIY "������" NOR, ({ "locker" }));
        set_weight(1000);

        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", YEL "����������,֪��������˿��Դ�ȡ��Ʒ��\n"
                                "ʹ�÷�������: \n"
                                "    �������������:  type <����>\n"
                                "    ��������(��������):changeto <������>\n"
                                "    ������: lock\n"
                                "    ��ѯ��Ʒ���: check\n"
                                "    ��������������Ʒ:cun all\n"
                                "    ����ĳ����Ʒ: cun <����> <��Ʒid>\n"
                                "    ȡ��Ʒ: qu <����> <��Ʒ���>\n"NOR);

                set("value", 100);
                set("unit", "��");
                set("no_get", 1);

        }
        setup();
}

string long()
{
        object ob;
        string msg;

        msg = query("long");
        if (query("open"))
            msg += HIG "������Ŀǰ�ǿ��ŵġ�\n" NOR;
        else
            msg += HIR "������Ŀǰ�ǹ��ŵģ�������type�������롣\n\n" NOR;

        return msg;

}

void init()
{
        string owner;

        object env = environment(this_object());

        if (! load)
        {
                env = environment(this_object());
                if (stringp(owner = env->query("room_owner_id")))
                        set("owner", owner);

                restore();
                delete("open");
                load = 1;
        }


        add_action("do_type", "type");
        add_action("do_changeto", "changeto");
        add_action("do_lock", "lock");
        add_action("do_check", "check");
        add_action("cun_check", "cun");
        add_action("do_qu", "qu");
}

int do_type(string arg)
{
    if (!arg)
       return notify_fail("��Ҫ�����������ʲô?\n");

    if (! query("passwd"))
       return notify_fail("������δ��������!\n"
              "�����������changeto��������󷽿�ʹ��!\n");

    if (query("open"))
        return notify_fail("����������Ѿ��ǿ��ŵ���!\n");

    if (arg != query("passwd"))
      return notify_fail(HIR"�������!�㲻��ʹ���������!\n"NOR);

    set("open", 1);
    message_vision(HIC "ֻ��$N" HIC "���������ϰ��˼���,"
                   "���Ӿʹ��ˡ�\n"NOR, this_player());

    return 1;
}


int do_changeto(string arg)
{
    object me;
    me = this_player();

    if (query("owner") != me->query("id"))
       return notify_fail(HIR"ֻ�����������޸�����!\n"NOR);

    if ( !arg)
       return notify_fail("��Ҫ������ĳ�ʲô?\n");

    if (sizeof(arg) > 6 )
       return notify_fail("�Բ���,�������ֻ��������λ!\n"NOR);

    if (!me->query_temp("locker_change_pass")
        || me->query_temp("locker_change_pass") != arg)
    {
       write(HIY"�㽫�������������ĳ�"NOR HIG + arg +
             NOR HIY",\n���û��Ļ���������һ�Ρ�\n"NOR);
       me->set_temp("locker_change_pass", arg);
       return 1;
    }

    me->delete_temp("locker_change_pass");
    set("passwd", arg);
    write(HIG"�㽫�����������ĳ���" + arg + "��\n"NOR);
    save();

    return 1;
}

int do_lock(string arg)
{
    if (!query("open"))
    return notify_fail("�������Ѿ������ŵ��ˡ�\n"NOR);

    delete("open");
    message_vision(HIW "ֻ��$N" HIW "����һ��������������������"
                   "\n"NOR, this_player());
    save();
    return 1;
}

int do_check()
{
    int i, cun_num;
    object ob, me = this_player();

    string msg, cun_itm, *deposit = query("deposit"),
           cun_name, cun_unit, cun_id;

    if (!query("open"))
    {
        write(HIR"���������ڹ��ţ�û��������\n"
              "������type <����> �������ӣ�\n"NOR);
        return 1;
     }

    if (me->is_busy())
    {
        write("����æ�����ٲ鶫���ɣ�\n");
        return 1;
    }

    if (sizeof(deposit) == 0 )
    {
       tell_object(me, "������������ʲôҲû�棡\n");
       return 1;
    }

    msg = "�������������ŵ���Ʒ���£�\n";

    for (i = 0; i < sizeof(deposit); i++)
    {
        sscanf(deposit[i], "%s:%d:%s:%s:%s",
          cun_itm, cun_num, cun_unit, cun_name, cun_id);

        msg += HIY + (i+1) + "." + NOR + chinese_number(cun_num)
               + cun_unit + cun_name + "(" + cun_id + ")" + "\n";
    }

    me->start_more(msg);

    me->start_busy(2);

    write(HIW"������ϵĻ�����lock�ر������䣡\n"NOR);
    return 1;

}

int cun_check(string arg)
{
        object me, *inv;
        int num, i, amount;
        string itm;

        me = this_player();


         if (!query("open"))
        {
           write(HIR"���������ڹ��ţ�û��������\n"
              "������type <����> �������ӣ�\n"NOR);
           return 1;
        }


        if (me->is_busy())
            return notify_fail("����æ�����ٴ涫���ɣ�\n");

        if ( arg == "all" )
        {
           inv = all_inventory(me);
           for (i=0;i<sizeof(inv);i++)
           {
              amount = 0;

              if ( inv[i]->query("base_unit"))
                 amount = inv[i]->query_amount();
              else
                 amount = 1;

               arg = amount + " " + inv[i]->query("id");
               do_cun(arg, 1);
            }

            tell_object(me, "������������ܴ�Ķ���������������䡣\n");

            message("vision", HIC + me->name() + HIC "�ó�һЩ��Ʒ������������"
                                    "��\n" NOR, environment(me), ({me}));

            me->start_busy(2);
            save();
            write(HIW"������ϵĻ�����lock�ر������䣡\n"NOR);
            return 1;
         }

        if (!arg || sscanf(arg, "%d %s", num, itm) != 2)
            return notify_fail("��Ҫ��ʲô��Ʒ����ʽΪcun <����> <��Ʒ����id>\n");

         do_cun(arg, 0);

         me->start_busy(2);
         save();
         write(HIW"������ϵĻ�����lock�ر������䣡\n"NOR);

         return 1;

}

int do_cun(string arg, int all)
{
        object ob, me, *inv;
        int num, ttl_amt, i, cun_num, same;
        string itm, *deposit, cun_itm, bs_nm, unit,
               cun_name, cun_id, cun_unit;

        me = this_player();
        same = 0;

        sscanf(arg, "%d %s", num, itm);

        ob = present(itm, me);

        if (!ob)
        {  write("������û�������Ʒѽ��\n"); return 1;}


        if (ob->is_character())
        { if ( ! all ) write("������Ҳ��棿��û�и��\n"); return 1;}


        if (! ob->query("can_cun") && file_name(ob)[0..10] != "/clone/fam/"
             && file_name(ob)[0..13] != "/clone/tattoo/"
             && file_name(ob)[0..11] != "/clone/gift/"
             && file_name(ob)[0..15] != "/clone/medicine/"
             || ob->query("no_cun") )
          {  if (! all) write("�Բ���������Ʒ���ܴ�ţ�\n"); return 1;}


          if (num < 1)
          {write("һ�����ٴ�һ����Ʒ��\n");return 1;}

         bs_nm = base_name(ob);
         inv = all_inventory(me);


          if (stringp( unit = ob->query("base_unit")))
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
         {   write("������û��ô��" +
                   ob->query("name") + NOR"��\n");
             return 1;
         }

        if ( ! all )
        {
           tell_object(me, "���ó�" + chinese_number(num) + unit +
                          ob->name() + "����˴����䡣\n");


           message("vision", HIC + me->name() + HIC "�ó�һЩ��Ʒ�����˴�����"
                                    "��\n" NOR, environment(me), ({me}));
         }


         if (query("deposit"))
            deposit = query("deposit");
         else deposit = ({});

         for (i=0;i<sizeof(deposit);i++)
         {
            sscanf(deposit[i], "%s:%d:%s:%s:%s", cun_itm, cun_num,
                     cun_unit, cun_name, cun_id);
            if (cun_itm == bs_nm)
            {
               deposit[i] = cun_itm + ":" + (cun_num + num) + ":" +
                unit + ":" + ob->query("name") + ":" + ob->query("id");
               same = 1;
            }
         }

         if (same != 1) deposit += ({ bs_nm + ":" + num + ":" + unit
                        + ":" + ob->query("name") + ":" + ob->query("id")});

         set("deposit", deposit);

         if (ob->query("base_unit"))
         {
            ob->add_amount(-num);
            if (ob->query_amount() < 1) destruct(ob);

         } else
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
               cun_unit, cun_name, cun_id;

        me = this_player();


        if (!query("open"))
        {
            write(HIR"���������ڹ��ţ�û��������\n"
              "������type <����> �������ӣ�\n"NOR);
            return 1;
         }


        if (!arg || sscanf(arg, "%d %d", num, itm) != 2)
            return notify_fail("��Ҫȡʲô��Ʒ����ʽΪqu <����> <��Ʒ���к�>\n");

        if (me->is_busy())
            return notify_fail("����æ������ȡ�����ɣ�\n");

        deposit = query("deposit");

        if ( sizeof(deposit) == 0 )
            return notify_fail("�����û�涫���������ȡʲôȡ��\n");

        if (num < 1)
             return notify_fail("һ������ȡһ����Ʒ��\n");


        if (num > 50)
             return notify_fail("һ�����ȡ��ʮ����Ʒ��\n");

        if ( itm < 1 || itm > sizeof(deposit))
            return notify_fail("��û�д������Ʒ!\n"
                               "��ע���ʽΪqu <����> <��Ʒ���к�>��\n"
                               "��ѯ�����Ʒ���к�������check\n");

       sscanf(deposit[(itm - 1)], "%s:%d:%s:%s:%s",
              cun_itm, cun_num, cun_unit, cun_name, cun_id);

       ob = new(cun_itm);

        if (me->query_encumbrance() + ob->query_weight() * num
            > me->query_max_encumbrance())
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
                 for( x = 0; x < num; x++)
                 {
                    ob = new(cun_itm);
                    ob->move(me, 1);
                 }

              }

              tell_object(me, "�����������ȡ��" + chinese_number(num) + unit +
                          ob->name() + "��\n");


              message("vision", HIC + me->name() + HIC "��������������Щ��������"
                                    "��\n" NOR, environment(me), ({me}));

              if (num == cun_num) deposit -= ({ cun_itm + ":" + cun_num +
                  ":" + cun_unit + ":" + cun_name + ":" + cun_id });
                 else
              deposit[(itm-1)] = cun_itm + ":" + (cun_num - num) + ":"
                   + cun_unit + ":" + cun_name + ":" + cun_id;

              set("deposit", deposit);

              me->start_busy(2);
              save();
              write(HIW"������ϵĻ�����lock�ر������䣡\n"NOR);
              return 1;
}

int remove()
{
        save();
}

public void mud_shutdown()
{
        save();
}

string query_save_file()
{
        string id;

        if (! stringp(id = query("owner")) ) return 0;
        return DATA_DIR + "room/" + id + "/" + "locker";
}
