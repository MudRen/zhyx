
/********************************************************************************
             The Voting System For Yhonline(HERO) By Rcwiz On 1 June 2003

This System can gain the result that players decided.
All Public functions in this file ard called by command which defined in 
"/cmds/std/poll.c" and the result of the Voting will be loged in the 
"/log/voting/log", so you can view the history of voting using command "poll history"

*********************************************************************************/

#pragma optimize
#pragma save_binary

inherit F_DBASE;

#include <ansi.h>

mapping voting = ([]);

public int query_now_voting_class(string now);
public mixed query_now_voting_target();
public int show_voting(object me, string para);
public int start_voting(object me, string target, string kind);
public int end_voting(object me);
public int shot_target(object me, string kind);
private string show_process(int i);

#define LOG_FILE "/log/voting/log"

void create()
{
        seteuid(getuid());
        set("no_clean_up", 1);
}

public int start_voting(object me, string target, string kind)
{
        string* kinds;

        int i;

        if (wiz_level(me) < 4)
        {
              write("��û���㹻Ȩ�޷���ͶƱ��\n");
              return 0;
        }

        if (sizeof(voting))
        {
              write(HIC "Ŀǰ���ڽ���ͶƱ��������ȡ����ǰͶƱ���ܿ�ʼ�µ�ͶƱ��\n");
              return 0;
        }

        kinds = explode(kind, ":");
        if (sizeof(kinds) <= 1)
        {
              write("�����Ļ������粻ͶƱ��\n");
              return 0;
        }

        write(HIW "����" + HIR + target + HIW + "����ͶƱ��"
              "ͶƱ����Ϊ��\n" NOR);

        voting = ([
                    "name"     :  me->name(),
                    "id"       :  me->query("id"),
                    "time"     :  time(),
                    "target"   :  target,
                    "kind"     :  kind,
                    "ips"      :  ({}),
                    "user_list":  ({}),
                 ]);

        for (i = 0; i < sizeof(kinds); i ++)
        {
              write(HIR "\t\t\t" + kinds[i] + "\n" NOR);
              voting += ([ kinds[i] : "init" ]);
        }

	message("vision", HIW "��ϵͳ��ʾ�������µ�ͶƱ���ݣ����� " HIY 
                "poll now" HIW " �鿴��\n" NOR, all_interactive());

        return 1;
}

public int end_voting(object me)
{
        string str;
        string* kinds;
        int i;

        if (wiz_level(me) < 4)
        {
              write("��û���㹻Ȩ�޽���ͶƱ��\n");
              return 0;
        }

        if (sizeof(voting))
        {
              write("OK\n");
              message("vision", HIW "��ϵͳ��ʾ������ǰͶƱ " HIR + voting["target"] + 
                      HIW " �����ˣ��Ժ���ʹ�� " HIY "poll history" HIW 
                      " �鿴��\n" NOR, all_interactive());

              kinds = explode(voting["kind"], ":");
              str = "";
              for (i = 0; i < sizeof(kinds); i ++)
              {
                      str += kinds[i] + "  " + (string)(voting[kinds[i]] == "init" ? 
                                                0 : voting[kinds[i]]) + " Ʊ | ";                      
              }

              log_file("voting/log", sprintf(HIC "%-20s��    %-20s\n" NOR, voting["target"], str));
              voting = ([]);
              return 1;
        }

        else 
        {
              write("��ǰû��ͶƱ��\n");
              return 0;
        }
}

public int query_now_voting_class(string kind)
{
        if (sizeof(voting))
        {
             if (voting[kind] == "init" || voting[kind] > 0)
                     return 1;
 
             else return 0;
        }

        else return 0;
}

public mixed query_now_voting_target()
{
        if (! sizeof(voting) || ! stringp(voting["target"]))
              return 0;

        return voting["target"];
}

public int show_voting(object me, string para)
{
        string* kinds;
        int nCount, nKinds;
        string str;

        if (para == "history")
        {
             if (file_size(LOG_FILE) == -1)
             {
                     write("Ŀǰû����ʷͶƱ��¼��\n");
                     return 0;
             }
             nCount = 1;
             if (me->is_busy())
             {
                     write("����æ������˵�ɣ�\n");
                     return 0;
             }
             me->start_busy(2);

             write(NOR + WHT "\n------------------------------------------------------------"
                   "-------------\n" NOR);
             while (str = read_file(LOG_FILE, nCount, 1))
             {
                     write(str);
                     nCount ++;
             }
             write(NOR + WHT "\n------------------------------------------------------------"
                   "-------------\n" NOR);

             return 1;
        }

        if (sizeof(voting) <= 0)
        {
            write(HIG "��ǰû�н���ͶƱ��\n");

            return 0;
        }

        kinds = explode(voting["kind"], ":");
        if (me->is_busy())
        {
             write("����æ������˵�ɣ�\n");
             return 0;
        }
        me->start_busy(1);
        if (para == "now")
        {
             write(HIY "\n��ǰ�� " + HIR + voting["target"] + HIY + " ͶƱ������£�\n\n" NOR);
             for (nKinds = 0; nKinds < sizeof(kinds); nKinds ++)
             {
                     nCount = (voting[kinds[nKinds]] == "init" ? 0 : voting[kinds[nKinds]]);
                     write(sprintf(HIR "%-20s  %-20s  %-2d\n",  
                           kinds[nKinds], show_process(nCount),nCount));
             }
             write(HIG "\n��ʹ��" HIY + "poll shot<����>" + HIG "����ͶƱ��\n" NOR);
             return 1;
        }

}

public int shot_target(object me, string kind)
{       
        string *user_list, *ips, my_ip;

        if (wizardp(me) && wiz_level(me) < 5)
        {
               write("��ʦ����ͶƱŶ��\n");
               return 0;
        }

        if (me->is_busy())
        {
               write("����æ������˵�ɣ�\n");
               return 0;
        }

        if (! arrayp(user_list = voting["user_list"]))
               user_list = ({});


        if (! arrayp(ips = voting["ips"]))
               ips = ({});

        if (member_array(me->query("id"), user_list) != -1)
        {
               write("���Ѿ�Ͷ��Ʊ�ˣ�\n");
               me->start_busy(1);
               return 0;
        }

        // ��֤IP
        my_ip = query_ip_number(me);

        if (member_array(my_ip, ips) != -1)
        {
               write("������IP�Ѿ�Ͷ��Ʊ�ˣ�\n");
               me->start_busy(1);
               return 0;
        }

        if (voting[kind] == "init")
               voting[kind] = 1;

        else
               voting[kind] += 1;

        voting["user_list"] += ({ me->query("id") });
        voting["ips"] += ({ my_ip });

        write(HIG "��ͶƱϵͳ������ɹ�Ͷ�� " + HIR + kind + HIG " һƱ��\n" NOR);
        return 1;
}

private string show_process(int i)
{
       string s = "";
       int nCount;

       for (nCount = 0; nCount <= i; nCount ++)
               s += " ";
       
       return BBLU + s + NOR;
}
