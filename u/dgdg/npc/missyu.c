// missyu.c
// By haiyan

#include <ansi.h>
inherit NPC;

int over();
int do_end();
int do_stopcai();
void check_time();

int save()
{
        string file;
        file = "/data/npc/missdata";
        return save_object(file);
}

int restore()
{
        string file;
        file = "/data/npc/missdata.o";
        if (file_size(file) > 0)    return restore_object(file);
        else   return 0;
}

void create()
{
        set_name("��С��", ({ "miss yu", "miss", "yu" }));
        set("gender", "Ů��");
        set("age", 20);
        set("title", HIG "���ִ��" NOR);
        set("nickname", HIY "�ﱸ������" NOR);
        set("str", 25);
        set("con", 25);
        set("spi", 25);
        set("dex", 25);
        set("int", 25);
        set("per", 30);
        set("long", "����һ���ܾ����ܸɵ��ˡ�\n");
        set("combat_exp", 1000000);
        set("class", "fighter");
        set("attitude", "herosim");
        set("shop_id","beijing");

        set("giftyx", 300);
        set("giftwx", 300);

        set("inquiry", ([
                "��Ʊ" : "��Ʊʮ������һ�š�",
        ]));

        restore();

        if (clonep(this_object()))
        {
               set("chat_chance", 100);
               set("chat_msg", ({ (: check_time :) }));
               keep_heart_beat();
        }

        setup();
        carry_object("/clone/cloth/female3-cloth")->wear();
        carry_object("/clone/cloth/female-shoe")->wear();
}

void init()
{
        object ob = this_player();

        add_action("do_baoming", "baoming");

        if (ob && wiz_level(ob) > 3)
        {
                add_action("do_start", "start");
                add_action("do_chakan", "chakan");
                add_action("do_finish", "finish");
        }
}

void die()
{       
        return;
}

void unconcious()
{
        die();
}

int do_start()
{
        object me = this_player();
        int times;

        if (query("start_baoming"))
                return notify_fail(HIY "���������Ѿ������ˡ�\n" NOR);

        set("start_baoming", 1);
        set("y_start", 1);
        set("caipiao", 0);
        set("bm_time", time());
        set("c_time", time());
        times = (int)query("bisai_times") + 1;
        set("bisai_times", times);
        set("wizard", me->query("id"));
        save();
        tell_object(me, HIY "�������������ɹ������ڿ��ű�����\n" NOR);
        message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                "������Ϣ�����ĵ�" + chinese_number(times) + "�����ִ�ἴ���ٿ���" +
                "��·���ָ���ӻԾ�������������������\n" NOR,
                 all_interactive());
        return 1;
}

int do_end()
{
        int n = query("bisai_times");

        set("start_baoming", 0);
        set("caipiao", 1);
        set("cp_time", time());
        save();
        message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                "�����ĵ�" + chinese_number(n) + "�����ִ�ᱨ����" +
                "���������н����»��ʽ��ʼ���������������ݴ�ʧ��\n" NOR,
                 all_interactive());
        return 1;       
}

int do_stopcai()
{
        int n = query("bisai_times");

        set("caipiao_end", 1);
        set("caipiao", 0);
        delete("bm_time");
        delete("cp_time");
        delete("c_time");
        save();
        message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                "�����ĵ�" + chinese_number(n) + "�����ִ����ʽ�ٿ���\n" NOR,
                 all_interactive());
        return 1;
}

int do_finish()
{
        int n = query("bisai_times");
        int i, yx = 0, wx = 0;
        int *win, sp, x, y, r;
        object ob;
        mapping caipiao, winner;
        string *player;
        string *cpwxwin = ({}), *cpyxwin = ({});
        string *par, msg = "";

        if (! query("y_start"))
               return notify_fail(HIY "��������̲�û��������\n" NOR);

        if (query("wizard") != this_player()->query("id"))
               return notify_fail(HIY "ֻ�������ֱ��������ʦ���ܽ�����\n" NOR);

        winner = this_player()->query("winner");
        if (! mapp(winner))
              return notify_fail(HIY "�㻹û���������ݣ����ܽ�����\n" NOR);

        tell_object(this_player(), HIY "��" + chinese_number(n) +
                    "���������������\n" NOR);

        caipiao = query("xuancp");
        if (! mapp(caipiao))
        {
              tell_object(this_player(), HIY "û���˲μӾ��»��\n" NOR);
              message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                      "�����������û���˲μӲ�Ʊ���»��\n" NOR,
                      all_interactive());

              over();
              return 1;
        }

        player = keys(caipiao);
        win = keys(winner);
        par = values(winner);

        for (x = 0; x < sizeof(win); x++)
        {
             for (y = x + 1; y < sizeof(win); y++)
             {
                  if (win[x] > win[y])
                  {
                        r = win[x];
                        win[x] = win[y];
                        win[y] = r;
                  }
             }
        }

        for (i = 0; i < sizeof(player); i++)
        {
            if (caipiao[player[i]][0] == "����")
            {
                 yx ++;
                 if (caipiao[player[i]][1] == winner[win[0]] &&
                     caipiao[player[i]][2] == winner[win[1]] &&
                     caipiao[player[i]][3] == winner[win[2]] &&
                     caipiao[player[i]][4] == winner[win[3]] &&
                     caipiao[player[i]][5] == winner[win[4]])
                     cpyxwin += ({ player[i] });
            } else
            {
                 wx ++;
                 if (member_array(caipiao[player[i]][1], par) != -1 &&
                     member_array(caipiao[player[i]][2], par) != -1 &&
                     member_array(caipiao[player[i]][3], par) != -1 &&
                     member_array(caipiao[player[i]][4], par) != -1 &&
                     member_array(caipiao[player[i]][5], par) != -1)
                     cpwxwin += ({ player[i] });
            }
        }

        message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                "�����ĵ�" + chinese_number(n) + "�����ִ�Ṳ�յ���Ч��Ʊ" +
                chinese_number(sizeof(player)) + "�š�\n" NOR, all_interactive());
        message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                "�����У������淨" + chinese_number(yx) + "�ţ������淨" +
                chinese_number(wx) + "�š�\n" NOR, all_interactive());

        if (sizeof(cpyxwin) == 0 && sizeof(cpwxwin) == 0)
        {
                message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                "�������Ʊ���������н������ؽ�" +
                chinese_number(query("giftyx") + query("giftwx")) +
                "���ƽ�������½졣\n" NOR, all_interactive());
                add("giftyx", 300);
                if (query("giftyx") > 2000)   set("giftyx", 2000);
                add("giftwx", 300);
                if (query("giftwx") > 2000)   set("giftwx", 2000);
                over();
                return 1;
        }

        if (sizeof(cpyxwin) == 0 && sizeof(cpwxwin) != 0)
        {
                message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                "�������淨�����н������ؽ�" + chinese_number(query("giftyx")) +
                "���ƽ�����½졣\n" NOR, all_interactive());
                add("giftyx", 300);
                if (query("giftyx") > 2000)   set("giftyx", 2000);

                sp = query("giftwx") / sizeof(cpwxwin);
                if (sp < 1)  sp = 1;

                message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                "�������淨����" + chinese_number(sizeof(cpwxwin)) +
                "���н�����ע����" + chinese_number(sp) + "���ƽ��Ѵ�" +
                "���н����ʺš�\n" NOR, all_interactive());

                for (i = 0; i < sizeof(cpwxwin); i++)
                {
                      ob = find_player(cpwxwin[i]);
                      if (objectp(ob))
                      {
                          ob->add("balance", sp * 10000);
                          command("tell " + ob->query("id") + " ��ϲ�н���" +
                                  "���Ľ���" + chinese_number(sp) + "���ƽ��Ѵ���"
                                  "�����ʺ��ˡ�");
                      }
                }
                over();
                return 1;
        }

        if (sizeof(cpyxwin) != 0 && sizeof(cpwxwin) == 0)
        {
                message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                "�������淨�����н������ؽ�" + chinese_number(query("giftwx")) +
                "���ƽ�����½졣\n" NOR, all_interactive());
                add("giftwx", 300);
                if (query("giftwx") > 2000)   set("giftwx", 2000);

                sp = query("giftyx") / sizeof(cpyxwin);
                if (sp < 1)  sp = 1;

                for (i = 0; i < sizeof(cpyxwin); i++)
                {
                      ob = find_player(cpyxwin[i]);
                      if (objectp(ob))
                      {
                           ob->add("balance", sp * 10000);
                           command("tell " + ob->query("id") + " ��ϲ�н���" +
                                   "���Ľ���" + chinese_number(sp) + "���ƽ�" +
                                   "�Ѵ��������ʺ��ˡ�");
                           msg += ob->query("name")+"("+ob->query("id")+")"+",";
                      }  else   msg += cpyxwin[i] + ",";
                }

                message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                        "�������淨�н���������" + msg[0..strlen(msg)-2] + "��\n" NOR,
                        all_interactive());
                message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                        "����ע����" + chinese_number(sp) + "���ƽ��Ѵ����н���" +
                        "�ʺţ���ϲ��\n" NOR, all_interactive());
                over();
                return 1;
        }

        sp = query("giftwx") / sizeof(cpwxwin);
        if (sp < 1)  sp = 1;

        message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                "�������淨����" + chinese_number(sizeof(cpwxwin)) +
                "���н�����ע����" + chinese_number(sp) + "���ƽ��Ѵ�" +
                "���н����ʺš�\n" NOR, all_interactive());

        for (i = 0; i < sizeof(cpwxwin); i++)
        {
              ob = find_player(cpwxwin[i]);
              if (objectp(ob))
              {
                   ob->add("balance", sp * 10000);
                   command("tell " + ob->query("id") + " ��ϲ�н���" +
                           "���Ľ���" + chinese_number(sp) + "���ƽ�" +
                           "�Ѵ��������ʺ��ˡ�");
              }
        }

        sp = query("giftyx") / sizeof(cpyxwin);
        if (sp < 1)  sp = 1;

        for (i = 0; i < sizeof(cpyxwin); i++)
        {
              ob = find_player(cpyxwin[i]);
              if (objectp(ob))
              {
                    ob->add("balance", sp * 10000);
                    command("tell " + ob->query("id") + " ��ϲ�н���" +
                            "���Ľ���" + chinese_number(sp) + "���ƽ�" +
                            "�Ѵ��������ʺ��ˡ�");
                    msg += ob->query("name")+"("+ob->query("id")+")"+",";
              }  else   msg += cpyxwin[i] + ",";
        }

        message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                "�������淨�н���������" + msg[0..strlen(msg)-2] + "��\n" NOR,
                all_interactive());
        message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                "����ע����" + chinese_number(sp) + "���ƽ��Ѵ����н���" +
                "�ʺţ���ϲ��\n" NOR, all_interactive());
        over();
        return 1;
}

int do_baoming(string arg)
{
        object me = this_player();
        int mca, mcb;
        string ipn, msg;
        mapping baoming_list;

        if ((int)me->query("combat_exp") < 500000)
             return notify_fail("��С�������һ�ۣ������������ӣ�ȥ�������������̨�¿������ˡ�\n");

        if (! query("start_baoming"))
        {
             if (query("caipiao"))
             {
                   command("say ��λ" + RANK_D->query_respect(me) +
                           "�������ˣ�����ʱ���ѹ����������Ų�Ʊ����ɡ�");
                   return 1;
             }
             if (query("caipiao_end"))
             {
                   command("say �������Ѿ���ʼ����ֻ�е��´������ˡ�");
                   return 1;
             }
             command("say ��λ" + RANK_D->query_respect(me) +
                     "���ż�ѽ����û�е����ִ���ٿ���ʱ���ء�");
             return 1;
        }

        if (! arg || sscanf(arg, "%d %d", mca, mcb) != 2)
        {
             msg = "ָ���ʽ��baoming <������������һ> <�����������ζ�>\n";
             msg += "˵����ÿ��ID���Բμ��������εĽ���\n���磺����μ�";
             msg += "��һ���͵������ı���������� baoming 1 3\n";
             me->start_more(msg);
             return 1;
        }

        if (mca < 1 || mca > 5 || mcb < 1 || mcb > 5)
        {
             command("? " + me->query("id"));
             command("say �㵽��Ҫ�μӵڼ����ı���ѽ��");
             return 1;
        }

        if (query("baoming") &&
            member_array(me->query("id"), keys(query("baoming"))) != -1)
        {
             command("say ��λ" + RANK_D->query_respect(me) +
                     "�����Ѿ��������ˣ���ȥ׼��׼���ɡ�");
             return 1;
        }

        ipn = query_ip_number(me);
        if (!query("baoming"))  baoming_list = ([]);
        else baoming_list = query("baoming");
        baoming_list += ([ me->query("id") : ({ mca, mcb, ipn }) ]);
        set("baoming", baoming_list);
        save();
        tell_object(me, HIY "�������μӵ�" + chinese_number(mca) +
                    "���͵�" + chinese_number(mcb) + "���ı�����ף��ɹ���\n"NOR);
        return 1;
}

int accept_object(object me, object ob)
{
        object piao;
        mapping cai, bm;
        string *xs;
        int i;

        if ( ob->query("money_id"))
        {
              if (query("caipiao"))
              {
                   if (ob->value() >= 1000 )
                   {
                         bm = query("baoming");
                         xs = keys(bm);
                         for (i = 0; i < sizeof(xs); i++)
                         {
                              if (bm[xs[i]][2] == query_ip_number(me))
                              {
                                   tell_object(me, "��С�����������IP" +
                                       "���˲μӱ������㲻�ܲ��뾺�¡�\n");
                                   return 0;
                              }
                         }
                         piao = new(__DIR__"obj/piao");
                         piao->set("baoming", query("baoming"));
                         piao->move(me);
                         message_vision("��С��˺��һ�Ų�Ʊ�ݸ�$N��\n", me);
                         destruct(ob);
                         return 1;
                   } else
                   {
                         command("say �Ÿ���ô��Ǯ����Ҳ̫�����˰ɡ�");
                         return 0;
                   }
              }

              if (query("start_baoming"))
              {
                   command("say �������ڱ����У��ȱ���������������Ʊ��");
                   return 0;
              }

              if (query("caipiao_end"))
              {
                   command("say �������Ѿ���ʼ�ˣ�����´ΰɡ�");
                   return 0;
              }

              command("say ���ڲ����۲�Ʊ���ȱ����Ὺʼ��������������ɡ�");
              return 0;
        }

        if ( (string)ob->query("id") == "cai piao")
        {
              if (! ob->query("done"))
              {
                    command("say ���Ų�ƱʲôҲû�������ٸ��Ұɡ�");
                    return 0;
              }

              if (query("caipiao_end"))
              {
                    command("say �������Ѿ���ʼ�������Ų�Ʊ�����ˡ�");
                    message_vision("$N�ӹ�$n�Ĳ�Ʊ����˺������Ƭ��\n", this_object(), me);
                    destruct(ob);
                    return 1;
              }

              if (! query("caipiao"))
              {
                    command("say �����Ų�Ʊ�Ѿ����������ˡ�");
                    message_vision("$N�ӹ�$n�Ĳ�Ʊ����˺������Ƭ��\n", this_object(), me);
                    destruct(ob);
                    return 1;
              }

              bm = query("baoming");
              xs = keys(bm);
              for (i = 0; i < sizeof(xs); i++)
              {
                   if (bm[xs[i]][2] == query_ip_number(me))
                   {
                        tell_object(me, "��С�����������IP" +
                                    "���˲μӱ������㲻�ܲ��뾺�¡�\n");
                        return 0;
                   }
              }

              if (!query("xuancp"))  cai = ([]);
              else
              {
                   cai = query("xuancp");
                   if (member_array(me->query("id"), keys(cai)) != -1)
                   {
                         tell_object(me, "���Ѿ�Ͷ��ע�ˡ�\n");
                         return 0;
                   }
              }
              cai += ob->query("array");
              set("xuancp", cai);
              save();
              destruct(ob);
              command("say ף����ˣ�");
              return 1;
        }
        return 0;
}

int do_chakan()
{
        mapping bm;
        string *rs, msg = "\n";
        int i, j;

        bm = query("baoming");
        if (! mapp(bm))
             return notify_fail(HIY "����û���˱�����\n" NOR);

        rs = keys(bm);
        for (i = 1; i <= 5; i++)
        {
             msg += "�μӵ�" + chinese_number(i) + "���������У�\n";
             for (j = 0; j < sizeof(rs); j++)
             {
                  if (bm[rs[j]][0] == i || bm[rs[j]][1] == i)
                       msg += rs[j] + " ";
             }
             msg += "\n\n";
        }
        this_player()->start_more(HIY + msg + NOR);
        return 1;
}

int over()
{
        int n = query("bisai_times");
        message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                "���½������淨���ؽ�Ϊ��" + chinese_number(query("giftyx")) +
                "���ƽ������淨���ؽ�Ϊ��" + chinese_number(query("giftwx")) +
                "���ƽ�\n" NOR, all_interactive());
        message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                "������ף�ػ��ĵ�" + chinese_number(n) + "�����ִ��Բ������"
                "��\n" NOR, all_interactive());
        set("caipiao", 0);
        set("y_start", 0);
        delete("xuancp");
        delete("winner");
        delete("baoming");
        delete("wizard");
        delete("caipiao_end");
        save();
        this_player()->delete("winner");
        return 1;
}

void check_time()
{
        int n, tm;

        n = query("bisai_times");
        if (query("c_time") && (time() - query("c_time") >= 300))
        {
              if (query("start_baoming"))
              {
                    if (query("bm_time") && (time() - query("bm_time") < 82800))
                    {
                        message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                        "�����ĵ�" + chinese_number(n) + "�����ִ�ἴ���ٿ���" +
                        "��·���ָ����ѿ�ʼӻԾ�������������������\n" NOR,
                        all_interactive());
                    }  else
                    if (query("bm_time") && (time() - query("bm_time") >= 82800) &&
                       (time() - query("bm_time") < 86400))
                    {
                        tm = 86400 - (time() - query("bm_time"));
                        if (tm >= 300)  tm /= 60;
                        else tm = 5;

                        message("vision", HIW "������ʢ�᡿" +
                                this_object()->name() + "�����" +
                                chinese_number(n) + "�����ִ�ᱨ" +
                                "������ʱ�仹ʣ" + chinese_number(tm) +
                                "���ӣ�\n" NOR, all_interactive());
                    }  else   do_end();

                    set("c_time", time());
                    save();
                    return;
              }

              if (query("caipiao"))
              {
                    if (query("cp_time") && (time() - query("cp_time") < 5400))
                    {
                        if (random(3) > 0)
                            message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                            "�����ĵ�" + chinese_number(n) + "�����ִ�ᱨ����" +
                            "���������н����»���ھ��У��������������ݴ�ʧ��\n" NOR,
                            all_interactive());
                        else
                            message("vision", HIW "������ʢ�᡿" + this_object()->name() +
                                    "���������ִ�ά�ؽ��Ϊ�������淨" +
                                    chinese_number(query("giftyx")) +
                                    "���ƽ������淨" + chinese_number(query("giftyx")) +
                                    "���ƽ�\n" NOR, all_interactive());
                    }  else
                    if (query("cp_time") && (time() - query("cp_time") >= 5400) &&
                       (time() - query("cp_time") < 7200))
                    {
                        tm = 7200 - (time() - query("cp_time"));
                        if (tm >= 300)   tm /= 60;
                        else  tm = 5;

                        message("vision", HIW "������ʢ�᡿" +
                                this_object()->name() + "������" +
                                chinese_number(tm) + "���ӣ���" +
                                chinese_number(n) + "�����ִ�Ὣ" +
                                "��ʽ�ٿ���\n" NOR, all_interactive());
                    }  else   do_stopcai();

                    set("c_time", time());
                    save();
                    return;
              }
        }
        return;
}

void reset()
{
        restore();
}

