// newsd.c
// update by Lonely

#include <ansi.h>
#include <getconfig.h>

// #pragma optimize
// #pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

// ���һǧ������
#define MAX_NEWS_CAPACITY       1000

// ���ɸ������ȼ�
int     last_update_day = 0;
mapping family_priority = ([ ]);

void create()
{
        seteuid(getuid());
        restore();
        set_heart_beat(300);
}

// ����������ÿ�������������ɵĸ������ȼ�
void heart_beat()
{
        int time;
        string fam;

        if (time() / 86400 != last_update_day)
        {
                // �������ɸ�������˳������
                last_update_day = time() / 86400;

                if (! mapp(family_priority))
                        family_priority = ([ ]);

                foreach (fam in keys(FAMILY_D->query_family_fame()))
                        if (undefinedp(family_priority[fam]))
                                family_priority[fam] = 10;
                        else
                                family_priority[fam] += 10;

                save();
        }
}

mapping query_family_priority()
{
        return family_priority;
}

void remove()
{
        save();
}

void mud_shutdown()
{
        save();
}

// prompt user
void prompt_user(object me)
{
        int num;
        int total;
        mapping *notes;
        int last_read_time;

        last_read_time = me->query("last_read_news");
        if (! last_read_time)
        {
                tell_object(me, HIG "\n��ӭ������" + LOCAL_MUD_NAME() +
                                HIG "�������ʹ��" HIY " news " HIG
                                "������ķ�����������Ϣ��\n" NOR);
                me->set("last_read_news", time());
                return;
        }

        notes = query("notes");

        if (! pointerp(notes) || ! sizeof(notes))
                return;

        num = sizeof(notes);
        total = 0;
        while (num--)
                if (notes[num]["time"] > last_read_time)
                        total++;
                else
                        break;

        if (! total)
                tell_object(me, "\n��Ŀǰû��δ���Ķ��������š�\n");
        else
                tell_object(me, sprintf(WHT "\n��Ŀǰһ���� " HIY "%d" NOR
                                        WHT " �����Ż�û���Ķ�����ʹ�� "
                                        HIY "news" NOR WHT " �����Ķ���\n" NOR, total));

        tell_object(me, HIG "\n�����ʹ�� " NOR + HIY "wenxuan" NOR + HIG " ���������Ϸ������ѡ����\n\n" NOR);

        // ��ʼ��ʱ֪ͨ
        if (previous_object() == find_object(LOGIN_D))
                me->start_call_out(bind((: call_other, __FILE__, "auto_notice", me :), me), 10 + random(10));
}

// show all the news's title
// raw = 1: only show the non-read news
void show_news(object me, int raw)
{
        mapping *notes;
        int i, last_time_read;
        string msg;

        notes = query("notes");
        if (! pointerp(notes) || ! sizeof(notes))
        {
                tell_object(me, "Ŀǰû���κ����š�\n");
                return;
        }

        msg =HIY "Ŀǰ�ݺ������е�������Ϣ���£�                          " BRED HIW " �ݺ�������ʦ�� \n" NOR
             BBLU HIW "-------------------------------------------------------------------------------\n" NOR;
        last_time_read = me->query("last_read_news");
        i = sizeof(notes);
        while (i--)
        {
                if (raw && (notes[i]["time"] <= last_time_read))
                        break;

                msg += sprintf(WHT "%s[%3d]" NOR " %-" + (40 + color_len(notes[i]["title"])) +
                               "s %s (%s)\n",
                               (notes[i]["time"] > last_time_read ? BLINK HIR : ""),
                               i + 1, notes[i]["title"],
                               notes[i]["author"], ctime(notes[i]["time"])[0..15]);
        }

        if (i == sizeof(notes) - 1)
        {
                tell_object(me, "Ŀǰû���κ�δ���������š�\n");
                return;
        }

        msg +=BBLU HIW "-------------------------------------------------------------------------------\n" NOR;

        me->start_more(msg);
}

// This is the callback function to process the string returned from the
// editor defined in F_EDIT of player object.
void done_post(object me, mapping note, int n, string text)
{
        int i;
        int t;
        int pl;
        string sign;
        string pure;
        mapping *notes;

        if (! n) n = me->query("env/default_sign");
        if (! stringp(sign = me->query(sprintf("env/sign%d", n))))
        {
                // auto select the first none null sign
                for (i = 1; i <= 4; i++)
                {
                        sign = me->query(sprintf("env/sign%d", i));
                        if (stringp(sign)) break;
                }
        }

        if (stringp(sign))
        {
                sign = replace_string(sign, "\\n", "\n");
                sign = trans_color(sign, 1);
                pure = filter_color(sign);
                if (strlen(pure) >= 1 &&
                    pure[strlen(pure) - 1] != '\n')
                        sign += "\n";

                pure = filter_color(text);
                pl = strlen(pure);
                if (pl >= 1 && pure[pl - 1] != '\n')
                        text += "\n\n" + sign;
                else
                if (pl >= 2 && pure[pl - 2] != '\n')
                        text += "\n" + sign;
                else
                        text += sign;
        }

        text = color_filter(text) + NOR;

        note["msg"] = text;
        notes = query("notes");
        if (! pointerp(notes) || ! sizeof(notes))
                notes = ({ note });
        else
        {
                i = sizeof(notes) - 1;
                if (note["time"] <= notes[i]["time"])
                        note["time"] = notes[i]["time"] + 1;
                notes += ({ note });
        }

        // Truncate the notes if maximum capacity exceeded.
        if (sizeof(notes) > MAX_NEWS_CAPACITY)
                notes = notes[MAX_NEWS_CAPACITY / 4 .. MAX_NEWS_CAPACITY];

        set("notes", notes);
        tell_object(me, "���ŷ�����ϡ�\n");

        save();
        message("system", BLINK HIM "\n�����ž��顿�����������ţ���λ������� news �鿴��\n\n" NOR,
                users());
}

// post a news
void do_post(object me, string arg)
{
        int n;
        mapping note;

     /*   if (! VERSION_D->is_release_server())
        {
                tell_object(me, "ֻ���ڰ汾������վ����ܷ������š�\n");
                return;
        } */

        if (! wizardp(me) || ! interactive(me))
        {
                tell_object(me, "ֻ����ʦ���ܷ������š�\n");
                return;
        }

        if (! arg)
        {
                tell_object(me, "����������ָ��һ�����⡣\n");
                return;
        }

        if (sscanf(arg, "%s with %d", arg, n) != 2)
                n = 0;

        if (replace_string(arg, " ", "") == "")
                arg = "�ޱ���";
        else
                arg = color_filter(arg) + NOR;

        note = allocate_mapping(4);
        note["title"] = arg;
        note["author"] = me->name(1) + "-" + me->query("id");
        note["time"] = time();
        me->edit(bind((: call_other, __FILE__, "done_post", me, note, n :), me));
}

// read a news
void do_read(object me, string arg)
{
        int num;
        mapping *notes;
        int last_read_time;

        last_read_time = me->query("last_read_news");
        notes = query("notes");

        if (! pointerp(notes) || ! sizeof(notes))
        {
                tell_object(me, "Ŀǰû���κ����š�\n");
                return;
        }

        if (! arg)
        {
                tell_object(me, "�������һ�����ţ�\n");
                return;
        }

        if (arg == "new" || arg == "next")
        {
                if (! last_read_time)
                        num = 1;
                else
                        for (num = 1; num <= sizeof(notes); num++)
                                if (notes[num - 1]["time"] > last_read_time)
                                        break;
        } else
        if (! sscanf(arg, "%d", num))
        {
                tell_object(me, "��Ҫ���ڼ������ţ�\n");
                return;
        }

        if (num < 1 || num > sizeof(notes))
        {
                tell_object(me, "û���������š�\n");
                return;
        }
        num--;
        me->start_more(sprintf("[%d] %-" + (40 + color_len(notes[num]["title"])) +
                               "s %s (%s)\n----------------------------------------------------------------------\n",
                               num + 1, notes[num]["title"], notes[num]["author"],
                               ctime(notes[num]["time"])[0..9]) + notes[num]["msg"]);

        // Keep track which post we were reading last time.
        if (notes[num]["time"] > (int)last_read_time)
                me->set("last_read_news", notes[num]["time"]);
}

// discard a news
void do_discard(object me, string arg)
{
        mapping *notes;
        int num;
        string author, aid;

        if (! arg || sscanf(arg, "%d", num) != 1)
        {
                tell_object(me, "����ȥ����һ�����ţ�\n");
                return;
        }

        notes = query("notes");
        if (! arrayp(notes) || num < 1 || num > sizeof(notes))
        {
                tell_object(me, "û���������š�\n");
                return;
        }

        num--;

        if ((! stringp(author = notes[num]["author"]) ||
             sscanf(author, "%*s-%s", aid) != 2 ||
             aid != me->query("id")) &&
            (string)SECURITY_D->get_status(me) != "(admin)")
        {
                tell_object(me, "ֻ���������ȥ�����˷��������š�\n");
                return;
        }

        notes = notes[0..num - 1] + notes[num + 1..sizeof(notes) - 1];
        set("notes", notes);
        save();
        tell_object(me, "ɾ���� " + (num + 1) + " ������....Ok��\n");
}

// auto notice user
void auto_notice(object me)
{
        int num;
        mapping *notes;
        string msg;
        int last_read_time;

        if (! objectp(me))
                return;

        last_read_time = me->query("last_read_news");
        notes = query("notes");

        if (! pointerp(notes) || ! sizeof(notes))
                return;

        num = sizeof(notes) - 1;
        if (notes[num]["time"] <= last_read_time)
                return;

        // some news need read, start next call out
        me->start_call_out(bind((: call_other, __FILE__, "auto_notice", me :), me), 30 + random(30));

        if (! living(me) || me->query_temp("block_msg/all"))
                return;

        while (num-- > 0)
        {
                if (notes[num]["time"] <= last_read_time)
                {
                        num++;
                        break;
                }

                // contine to find next
        }

        if (num < 0) num = 0;

        switch (random(5))
        {
        case 0:
                msg = RED "һ������������ž�������������ǰ������"
                      "����һ���������õ�ֽͷ����������������\n" NOR;
                break;
        case 1:
                msg = BLU "����ͻȻ����һ���ѷ죬ð��һ������������"
                      "�ž��飬��������ੲ��ݵ�����������\n" NOR;
                break;
        case 2:
                msg = CYN "���Ȼ�������˺��㣬���ͷһ����ԭ��������"
                      "������ͷ�󺹵����˹�����\n" NOR;
                break;
        case 3:
                msg = YEL "��մ���һ����Ƿ����Ȼǰ��ð��һ������ɢ"
                      "ȥ�Ժ�ֻ��һ�����ž���������Ŀ����㣬���������дʡ�\n" NOR;
                break;
        default:
                msg = WHT "��ž����һ�������ž����Ǳ�������ˤ�ڵ��ϣ�"
                      "����æ��������\n" NOR;
                break;
        }

        msg += HIM "���ž����������������������Ϣ��\n" NOR;
        tell_object(me, msg);
        me->start_more(sprintf("[%d] %-" + (40 + color_len(notes[num]["title"])) +
                               "s %s (%s)\n----------------------------------------------------------------------\n",
                               num + 1, notes[num]["title"], notes[num]["author"],
                               ctime(notes[num]["time"])[0..9]) + notes[num]["msg"]);

        // Keep track which post we were reading last time.
        if (notes[num]["time"] > (int)last_read_time)
                me->set("last_read_news", notes[num]["time"]);
        tell_object(me, HIM "���ž���˵�����ʧ��һ������֮�С�\n" NOR);
}

void do_search(object me, string arg)
{
        mapping *notes;
        int i, last_time_read, find = 0;
        string msg, topic, note;

        notes = query("notes");
        if (! pointerp(notes) || ! sizeof(notes))
        {
                tell_object(me, "Ŀǰû���κ����š�\n");
                return;
        }

        if (! arg)
        {
                tell_object(me, "����������һ�����ţ�\n");
                return;
        }

        if (sscanf(arg, "%s %s", topic, arg) != 2)
        {
                tell_object(me, "��ֻ����������(title)������(author)������(document)��\n");
                return;
        } else
        {
                if (topic == "title") note = "����";
                else
                if (topic == "author") note = "����";
                else
                if (topic == "document") note = "����";
                else
                {
                        tell_object(me, "��ֻ����������(title)������(author)������(document)��\n");
                        return;
                }
        }

        last_time_read = me->query("last_read_news");
        i = sizeof(notes);

        msg = sprintf("���� " HIY "%s" NOR " ���� " HIY "%s" NOR " �õ����·����������ţ�\n"
                      WHT "-------------------------------------------------------------------------------\n" NOR,
                      arg, note);

        while (i--)
        {
                if (topic == "document")
                {
                        if (strsrch(notes[i]["msg"], arg) == -1)
                                continue;
                } else
                {
                        if (strsrch(notes[i][topic], arg) == -1)
                                continue;
                }

                msg += sprintf("%s[%3d]" NOR " %-" + (40 + color_len(notes[i]["title"])) +
                               "s %s (%s)\n",
                               (notes[i]["time"] > last_time_read ? HIY : ""),
                               i + 1, notes[i]["title"],
                               notes[i]["author"], ctime(notes[i]["time"])[0..15]);

                find = 1;
        }

        if (! find)
        {
                tell_object(me, "���� " HIY + arg + NOR " ���� " HIY + note + NOR " û���ҵ��������������š�\n");
                return;
        }

        msg += WHT "-------------------------------------------------------------------------------\n" NOR;

        me->start_more(msg);
}

string query_save_file() { return DATA_DIR "newsd"; }
