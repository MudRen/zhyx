// lottery.c
// By haiyan

inherit NPC;

#include <ansi.h>
#include <localtime.h>

#define  PRICE        100            //ÿע�۸�һ��������
#define  MAX_BONUS    5000000        //��ע��߽������ڱ���
#define  BUNE         70             //���𷵻���70%
#define  J_0          60             //�صȽ����ܽ����60%
#define  J_1          25             //һ�Ƚ����ܽ����25%
#define  J_2          10             //���Ƚ����ܽ����10%
#define  J_3          5              //���Ƚ����ܽ����5%
#define  TAX          1000000        //��ͽ�˰���
#define  TAX_RATE     10             //˰��10%

int ask_caipiao();
int ask_dui();
int golds(int x, int y);
void check_time();
void aim_bonus(object me, int math, int bon);

int save()
{
        string file;
        file = "/data/npc/lottery";
        return save_object(file);
}

int restore()
{
        string file;
        file = "/data/npc/lottery.o";
        if (file_size(file) > 0)    return restore_object(file);
        else   return 0;
}

void create()
{
        set_name(HIY "����" NOR, ({ "san ben", "san" , "ben" }));
        set("nickname", MAG "�л�Ӣ�۸�����Ʊʹ��" NOR);
        set("title", HIG "һҹ����" NOR);
        set("gender", "����");
        set("shen_type", 1);
        set("per", 35);
        set("age", 100);
        set("combat_exp", 100000);
        set("attitude", "friendly");
        set("str", 30);
        set("max_qi", 300);
        set("max_jing", 300);
        set("neili", 300);
        set("max_neili", 300);
        set("jiali", random(10)+15);
        set_skill("unarmed", 30);
        set_skill("parry", 40);
        set_skill("dodge", 40);

        set("huaxia", 1);
        set("bonus", MAX_BONUS);

        restore();
        set("inquiry", ([
               "��Ʊ"  :   (: ask_caipiao :),
               "�ҽ�"  :   (: ask_dui :),
        ]));

        set("chat_chance", 30);
        set("chat_msg", ({
                (: check_time :),
        }));

        if (clonep(this_object()))   keep_heart_beat();

        setup();
        carry_object("/d/changan/npc/obj/choupao")->wear();
}

void init()
{
        add_action("do_checkcp", "checkcp");
        add_action("do_bonus", "bonuscp");
        add_action("do_checknum", "checknum");
}

void unconcious()   { return; }
void die()          { return; }

int do_bonus()
{
        object me = this_player();
        int i, nd = 0;
        string msg, su, *pr;
        mapping player_data;
        mixed *local;

        local = localtime(time());
        if (local[LT_WDAY] && !wizardp(me))
              return notify_fail("����˵���������ܶ�Ҫ��������ܹ�����\n");

        msg = sprintf("�����������ڽ����ܶ%s��\n",
                      MONEY_D->money_str(query("bonus") * 100));

        if (wizardp(me))
        {
              player_data = query("caipiao/player");
              if (! player_data)
                    su = "Ŀǰ��û����Ͷע��";
              else
              {
                    pr = keys(player_data);
                    for (i = 0; i < sizeof(pr); i++)
                         nd += sizeof(player_data[pr[i]]);

                    su = sprintf("Ŀǰ��%d�˹�Ͷ��%dע��", sizeof(pr), nd);
              }
              msg += sprintf("ӯ���ܶ�Ϊ%s��\n" + su + "\n",
                     MONEY_D->money_str(query("profit") * 100));
              if (query("finish"))
              msg += "���ڿ�������Ϊ" + query("finish/number") + "\n";
        }
        tell_object(me, msg);
        return 1;
}

int do_checkcp(string arg)
{
        object me = this_player();
        string *num, msg;
        mapping player_data;
        int i, p, pages, a, b;

        player_data = query("caipiao/player");

        if (! player_data || member_array(me->query("id"), keys(player_data)) == -1)
              return notify_fail("�����㻹û��Ͷ��ע��\n");

        num = player_data[me->query("id")];

        if (! arg || ! sscanf(arg, "%d", pages))
        {
              if (sizeof(num) > 100)
              {
                    if (sizeof(num) % 100)
                            p = (sizeof(num) / 100) + 1;
                    else    p = sizeof(num) / 100;
                    tell_object(me, sprintf("��Ͷ��ע̫�࣬������ʾ%dҳ��" +
                                "��ʹ�� checkcp <ҳ��> ���鿴��\n", p));
                    return 1;
              }  else
              {
                    msg = "�㹲Ͷ��" + sprintf("�л�Ӣ�۲��ʵ�%s���н�������Ʊ%dע��" +
                          "�����ǣ�\n", chinese_number(query("huaxia")), sizeof(num));

                    a = 1;
                    b = sizeof(num);
              }
        }  else
        {
              if (sizeof(num) % 100)
                      p = (sizeof(num) / 100) + 1;
              else    p = sizeof(num) / 100;

              if (! pages || pages > p)
                    return notify_fail("ҳ�����\n");

              if (sizeof(num) <= 100)
                    return notify_fail("��ֻ��һҳ��ֱ��ʹ��checkcp�����ˡ�\n");

              msg = "�㹲Ͷ��" + sprintf("�л�Ӣ�۲��ʵ�%s���н�������Ʊ%dע��" +
                    "�����ǣ�(�� %d ҳ)\n", chinese_number(query("huaxia")),
                    sizeof(num), pages);
              a = (pages - 1) * 100 + 1;
              b = (pages - 1) * 100 + 100;
              if (b > sizeof(num))   b = sizeof(num);
        }

        for (i = a; i <= b; i++)
        {
                msg += num[i-1] + "     ";
                if (!(i%5))   msg += "\n";
        }
        me->start_more(msg);
        return 1;
}

int do_checknum()
{
        object me = this_player();
        mapping oldnum;
        string msg, tmp;
        int i;

        oldnum = query("oldnum");
        if (! oldnum)
        {
               tell_object(me, "�������������û�п������ء�\n");
               return 1;
        }

        msg = "�л�Ӣ�۲�����ʷ�������룺\n";
        for (i = 1; i <= sizeof(keys(oldnum)); i++)
        {
               tmp = sprintf("��%d��", i);
               msg += tmp + "��";
               msg += oldnum[tmp] + "    ";
               if (!(i%5))   msg += "\n";
        }
        me->start_more(msg);
        return 1;
}

int ask_caipiao()
{
        object ob;
        string cont;
        mixed *local;

        local = localtime(time());
        if (query("finish") && local[LT_WDAY])
        {
              add("huaxia", 1);
              delete("caipiao");
              delete("numed");
              delete("chat_time");
              delete("finish");
              delete("duied");
              delete("bonuses");
              save();
        }

        if (local[LT_WDAY])
        {
              ob = new("/clone/npc/obj/caipiao");
              cont = sprintf("�л�Ӣ�۲��ʵ�%s���н�������Ʊ", chinese_number(query("huaxia")));
              ob->set("caipiao/huaxia", cont);
              ob->move(this_player());
              message_vision("����˺��һ�Ų�Ʊ�ݸ�$N��\n", this_player());
              tell_object(this_player(), "��������Ц����ÿ�Ų�Ʊ����Ͷʮע��" +
                          "��ú��鷳�㽻�����ң��������ָ��Ϊcheckcp(���ı���Ͷע���)��bonuscp(���Ľ��ؽ���Ͷע���)��                           checknum(������ʷ��������)��ÿ��һ������Ϊ��עʱ�䣬����Ϊ����ʱ�䣬��ע������עһ���ƽ�(ֱ�Ӵ�
                           ���д���п۳�)����ע��߽��𱣵��������ƽ𣬡�\n");
        }  else
              tell_object(this_player(), "��������Ц�������Ǳ�Ǹ�������Ƕҽ�ʱ" +
                          "�䣬�����������ɡ�\n");
        return 1;
}

int ask_dui()
{
        object me = this_player();
        int i, c0, c1, c2, c3;
        string *number, *duied, num;
        mapping player_data;

        if (! query("finish"))
        {
              message_vision("������$N˵�������ڲ��Ƕҽ�ʱ�䡣\n", me);
              return 1;
        }

        player_data = query("caipiao/player");
        if (! player_data)
        {
              message_vision("������$N˵������û��Ͷ��עѽ�������Ͷ��ע" +
                             "���ܾ����ˣ���ϧ��ϧ��\n", me);
              return 1;
        }

        duied = query("duied");
        number = player_data[me->query("id")];
        num = query("finish/number");

        if (! number)
        {
              message_vision("������$N˵������û��Ͷ��עѽ�������Ͷ��ע" +
                             "���ܾ����ˣ���ϧ��ϧ��\n", me);
              return 1;
        }

        if (duied && member_array(me->query("id"), duied) != -1)
        {
              message_vision("��������$N���˿����㲻�Ƕҹ�������" +
                             "�뷢����֮��ѽ��\n", me);
              return 1;
        }

        c0 = c1 = c2 = c3 = 0;
        for (i = 0; i < sizeof(number); i++)
        {
              if (number[i] == num)                c0 += 1;
              else
              if (number[i][0..3] == num[0..3])    c1 += 1;
              else
              if (number[i][0..2] == num[0..2] ||
                  number[i][1..3] == num[1..3])    c2 += 1;
              else
              if (number[i][0..1] == num[0..1] ||
                  number[i][1..2] == num[1..2] ||
                  number[i][2..3] == num[2..3])    c3 += 1;
        }

        if (c0)    aim_bonus(me, c0, 0);
        if (c1)    aim_bonus(me, c1, 1);
        if (c2)    aim_bonus(me, c2, 2);
        if (c3)    aim_bonus(me, c3, 3);

        if (c0 || c1 || c2 || c3)
        {
             if (! duied)    duied = ({});
             duied += ({ me->query("id") });
             set("duied", duied);
             save();
             tell_object(me, "�������㱧ȭ������ϲ��ϲ��ף���������д󽱡�\n");
        }  else
             tell_object(me, "��������˵������ϧ��ϧ��������û���н���" +
                             "����һ�����У�\n");
        return 1;
}

int accept_object(object me, object ob)
{
        mixed *local;
        int zhu;
        string *tz, qi;
        mapping player_data;

        if (ob->query("money_id"))
        {
              message_vision("������$NЦ�������ò��ã���ֻ��Ѳ�Ʊ��ø��ң�" +
                             "�һ��Ǯ�ϰ����ﻮ�ʵġ�\n", me);
              return 0;
        }

        if (! ob->query("lottery"))
        {
              message_vision("������$NЦ������ֻ����Ʊ���⣬����Ҫ���ֶ�����" +
                             "�㻹���պðɡ�\n", me);
              return 0;
        }

        local = localtime(time());
        qi = sprintf("�л�Ӣ�۲��ʵ�%s���н�������Ʊ", chinese_number(query("huaxia")));

        if (! query("caipiao") || query("caipiao/huaxia") != qi)
        {
              delete("caipiao");
              set("caipiao/huaxia", qi);
              save();
        }

        if (ob->query("caipiao/huaxia") != qi)
        {
              tell_object(me, "��������Ц�������Ų�Ʊ�Ѿ������ˡ�\n");
              destruct(ob);
              return 1;
        }

        if (local[LT_WDAY])
        {
              // ����һ�������������������Ĳ�Ʊ
              zhu = sizeof(ob->query("caipiao/numbers"));
              if (! zhu)
              {
                     message_vision("�������˿�$N�����Ĳ�Ʊ���������Ų�Ʊ" +
                                    "ʲôҲû��ѽ���㻹������ٸ��Ұɡ�\n", me);
                     return 0;
              }  else
              {
                     if (me->query("balance") < zhu * PRICE * 100)
                     {
                              tell_object(me, "��������˵������Ĵ����񲻹�ѽ��\n");
                              return 0;
                     }

                     tell_object(me, sprintf("��������Ц�������Ų�Ʊ�㹲Ͷ��%sע��" +
                                 "�踶%s���Ѵ���Ĵ���п۳��ˡ�\n", chinese_number(zhu),
                                 MONEY_D->money_str(zhu * PRICE * 100)));
                     me->add("balance", - zhu * PRICE * 100);
                     add("bonus", zhu * PRICE * BUNE / 100);
                     add("profit", zhu * PRICE * (100 - BUNE) / 100);

                     player_data = query("caipiao/player");
                     if (! player_data)     player_data = ([]);

                     if (member_array(me->query("id"), keys(player_data)) == -1)
                            tz = ({});
                     else
                            tz = player_data[me->query("id")];

                     if (sizeof(tz) < 14990)
                     {
                          tz += ob->query("caipiao/numbers");

                          player_data[me->query("id")] = tz;
                          set("caipiao/player", player_data);
                          save();
                     } else
                          tell_object(me, "�������ε�������ͷ����Ͷ��ע�Ѿ�̫" +
                                      "���ˣ�С���ޱ���ʵ�ڼǲ�����ô�ࡣ\n");
                     destruct(ob);
                     return 1;
              }
        }  else
        {
              // �������ǿ���ʱ��
              tell_object(me, "��������Ц����������ҡ���ҽ�ʱ�䣬�����Ų�Ʊ" +
                          "�Ѿ������ˣ�������������ðɡ�\n");
              destruct(ob);
              return 1;
        }
}

void check_time()
{
        mixed *local;
        string qi, msg;

        qi = sprintf("�л�Ӣ�۲��ʵ�%s���н�������Ʊ", chinese_number(query("huaxia")));
        local = localtime(time());

        if (query("busy"))    return;

        if (! local[LT_WDAY] && local[LT_HOUR] >= 12 &&
              local[LT_HOUR] < 22 && !query("numed"))
        {
              set("numed", 1);
              set("busy", 1);
              save();
              call_out("lottery_zero", 1);
        }

        if (! local[LT_WDAY] && local[LT_HOUR] >= 22 && query("finish"))
        {
              add("huaxia", 1);
              delete("caipiao");
              delete("numed");
              delete("chat_time");
              delete("finish");
              delete("duied");
              delete("bonuses");
              save();
              return;
        }

        if (! local[LT_WDAY] && local[LT_HOUR] >= 12 && query("finish"))
        {
              if (time() - query("chat_time") > 1200)
              {
                      message("vision", HIY "���л�Ӣ�۲��ʡ�" + this_object()->name() +
                              "��" + qi + "���������Ѿ��������н�����Ϊ��" +
                              query("finish/number") + "\n" NOR, all_interactive());

                      if (query("finish/zero"))
                              msg = sprintf("���л�Ӣ�۲��ʡ�" + this_object()->name() +
                                    "�������صȽ��� %d ע��", query("finish/zero"));
                      else
                              msg = "���л�Ӣ�۲��ʡ�" + this_object()->name() +
                                      "�������صȽ������У�";

                      if (query("finish/one"))
                              msg += sprintf("һ�Ƚ��� %d ע��", query("finish/one"));
                      else
                              msg += "һ�Ƚ������У�";

                      if (query("finish/two"))
                              msg += sprintf("���Ƚ��� %d ע��", query("finish/two"));
                      else
                              msg += "���Ƚ������У�";

                      if (query("finish/three"))
                              msg += sprintf("���Ƚ��� %d ע��\n", query("finish/three"));
                      else
                              msg += "���Ƚ������С�\n";

                      message("vision", HIY + msg + NOR, all_interactive());

                      set("chat_time", time());
                      save();
                      return;
              }
        }
        return;
}

int lottery_zero()
{
        message_vision(HIY"\n������������������ʱ���ѵ������ڿ�ʼҡ����\n\n"NOR,
                       this_object());
        call_out("lottery_one", 10);
        return 1;
}

int lottery_one()
{
        int p;

        p = random(10);
        message_vision(HIY + sprintf("\n����������������һ���н������ǣ�%d \n\n" +
                       NOR, p), this_object());
        set("finish/number", sprintf("%d", p));
        save();
        call_out("lottery_two", 10);
        return 1;
}

int lottery_two()
{
        int p, i, sp;
        int c0, c1, c2, c3;
        string *player_id, num;
        mapping player_data, oldnum;

        num = query("finish/number");
        p = random(10);

        if (strlen(num) < 4)
        {
              message_vision(HIY + sprintf("\n����������������%s���н������ǣ�%d \n\n" +
                             NOR, chinese_number(strlen(num) + 1), p), this_object());
              set("finish/number", sprintf(num + "%d", p));
              save();
              call_out("lottery_two", 10);
        }  else
        {
              message_vision(HIY + sprintf("\n���������������ر�����ǣ�%d \n\n" +
                             NOR, p), this_object());
              set("finish/number", sprintf(num + "%d", p));
              oldnum = query("oldnum");
              if (! oldnum)    oldnum = ([]);
              oldnum += ([ sprintf("��%d��", query("huaxia")) : query("finish/number") ]);
              set("oldnum", oldnum);
              save();

              //�����н�ע������ע����
              num = query("finish/number");
              player_data = query("caipiao/player");

              if (! player_data)
              {
                    delete("busy");
                    save();
                    return 1;
              }

              player_id = keys(player_data);
              c0 = c1 = c2 = c3 = 0;
              for (p = 0; p < sizeof(player_id); p++)
              {
                    for (i = 0; i < sizeof(player_data[player_id[p]]); i++)
                    {
                         if (player_data[player_id[p]][i] == num)              c0 += 1;
                         else
                         if (player_data[player_id[p]][i][0..3] == num[0..3])  c1 += 1;
                         else
                         if (player_data[player_id[p]][i][0..2] == num[0..2] ||
                             player_data[player_id[p]][i][1..3] == num[1..3])  c2 += 1;
                         else
                         if (player_data[player_id[p]][i][0..1] == num[0..1] ||
                             player_data[player_id[p]][i][1..2] == num[1..2] ||
                             player_data[player_id[p]][i][2..3] == num[2..3])  c3 += 1;
                    }
              }

              set("finish/zero", c0);
              set("finish/one", c1);
              set("finish/two", c2);
              set("finish/three", c3);

              sp = golds(c0, 0);
              set("bonuses/j_0", sp);

              sp = golds(c1, 1);
              set("bonuses/j_1", sp);

              sp = golds(c2, 2);
              set("bonuses/j_2", sp);

              sp = golds(c3, 3);
              set("bonuses/j_3", sp);
              delete("busy");
              save();
        }
        return 1;
}

void aim_bonus(object me, int math, int bon)
{
        int bonus, pz;
        string msg;

        switch (bon)
        {
              case 0:   pz = query("bonuses/j_0");  break;
              case 1:   pz = query("bonuses/j_1");  break;
              case 2:   pz = query("bonuses/j_2");  break;
              case 3:   pz = query("bonuses/j_3");  break;
        }

        if (! bon)      msg = "�صȽ�";
        else   msg = sprintf("%s�Ƚ�", chinese_number(bon));

        bonus = math * pz;
        me->add("balance", bonus * 100);
        tell_object(me, sprintf("��������˵������ϲ��ϲ��������%dע" + msg +
                    "��\n��Ľ���%s���Ѿ���������ʻ��ˡ�\n",
                    math, MONEY_D->money_str(bonus * 100)));
        message("vision", HIY "���л�Ӣ�۲��ʡ�" + this_object()->name() +
                "����ϲ" + me->query("name") + "Ͷ�б���" + msg + "��\n"NOR,
                all_interactive());
        add("bonus", -bonus);
        save();
        return;
}

int golds(int x, int y)
{
        int k;
        if (x)
        {
              switch (y)
              {
                    case 0:
                         k = (query("bonus") / 100 * J_0) / x;  break;
                    case 1:
                         k = (query("bonus") / 100 * J_1) / x;  break;
                    case 2:
                         k = (query("bonus") / 100 * J_2) / x;  break;
                    case 3:
                         k = (query("bonus") / 100 * J_3) / x;  break;
              }
              if (k > MAX_BONUS)   k = MAX_BONUS;
              if (k > TAX)         k = k / 100 * (100 - TAX_RATE);
              return k;
        }
        else  return 0;
}

