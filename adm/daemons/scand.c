// #pragma optimize
// #pragma save_binary

inherit F_DBASE;

#include <ansi.h>

#define POLL_D "/adm/daemons/polld"

void scan_msg();
void scan_voting();
void destruct_invalid_login();

void create()
{
        seteuid(ROOT_UID);
        set("name", HIR "�������ɨ�辫��" NOR);
        set("channel_id", "ɨ�辫��");
        CHANNEL_D->do_channel( this_object(), "sys", "�������ɨ�辫���Ѿ�������");
        call_out("scan_msg", 60);
        call_out("scan_voting", 60);
        call_out("destruct_invalid_login", 10);
}

void destruct_invalid_login()
{
        object *list;
        int number, i;

        remove_call_out("destruct_invalid_login");
        call_out("destruct_invalid_login", 900);

        list = children("/clone/user/login");
        number = sizeof(list);

        reset_eval_cost();

        if (number)
	{
              	for (i = 0; i < number; i++)
		{
                        if (objectp(list[i]))
                             if (! list[i]->query("id")
                                 || list[i]->query("id") == "a"
                                 || sizeof(list[i]->query("id")) < 3)destruct(list[i]);
               }
       }
       return;
}

void scan_voting()
{
        remove_call_out("scan_voting");
        call_out("scan_voting", 1800);
        if (! POLL_D->query_now_voting_target())
                return;

	message("vision", HIW "��ϵͳ��ʾ����Ŀǰ���ڶ� " HIR +
                          POLL_D->query_now_voting_target() + HIW
                        " ����ͶƱ������ " HIY "poll now" HIW " ��"
                        "����\n" NOR, all_interactive());

       return;
}
// ɨ����������Ƿ����µĶ���Ϣ
void scan_msg()
{
        int i, nMsg, msg_all;
        object *obs;

        call_out("scan_msg", 1500 + random(600));

        CHANNEL_D->do_channel( this_object(), "sys", "ɨ�辫������ɨ����Ҷ���Ϣ��");

        obs = filter_array(all_interactive(), (: ! $1->query("doing") :));

        for (i = 0; i < sizeof(obs); i ++)
        {
              if (! objectp(obs[i]))continue;

              msg_all = sizeof(obs[i]->query("message"));
              if (msg_all <= 0)continue;

              for (nMsg = 1; nMsg <= msg_all; nMsg ++)
              {
                     if (obs[i]->query("message/msg" + nMsg + "/is_new"))
                     {
                           tell_object(obs[i], HIG "�����µ���Ϣ����ע�����" HIY " msg read all " HIG "��\n" NOR);
                           tell_object(obs[i], BEEP);
                           break;
                     }
              }
       }
}
