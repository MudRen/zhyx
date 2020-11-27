/***********************�л�����ϢСϵͳ***************
 ����������/���߷���Ϣ��ʮ�ַ���
                           Create by yuchang for zhyx
****************************************************/
// msg.c

inherit F_CLEAN_UP;
#include <ansi.h>
#include <localtime.h>

#define PLAYER_MAX_MSG          20
#define WIZ_MAX_MSG             30

int help(object me);

int send_msg(object me, string tar, string msg);
int read_msg(object me, mixed id);
int discard_msg(object me, string id);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object tar;
        string para, id;
        int i, num;;
        
        if (! arg)
              return help(me);
        
        if (sscanf(arg, "%s %s", para, id) != 2)
              return help(me);

        switch(para)
        {
              case "send":

                 tar = UPDATE_D->global_find_player(id);

                 if (! objectp(tar))
                          return notify_fail("û�������ҡ�\n");

                 UPDATE_D->global_destruct_player(tar, 1);
/*
                 if (! wizardp(me) 
                     && ! me->query("can_send_msg")
                     && id != "yuchang")
                          return notify_fail("ֻ�л�Ա���ܷ��Ͷ���Ϣ��\n");
*/

                 write(HIG "���������Ϣ���ݣ����Ȳ�����500�����֣���\n" NOR);

                 me->edit((: call_other, __FILE__, "done", me, id :), me);

                 break;
              
              case "read":

                 read_msg(me, id);

                 break;                  

              case "discard":
                 
                 discard_msg(me, id);

                 break;
 
              case "snoop":
        
                 //snoop_msg(me, id);

                 break;

              default:

                   write("ָ���ʽ : msg <send id | read ����Ϣ���> \n");
                  
                   break;
        }

        return 1;
}

void done(object me, string tar, string msg)
{

        if (! me || ! msg || msg == "")
                return;

        if (! wizardp(me) && time() - me->query_temp("last_send_msg") < 60)
        {
                tell_object(me, HIC "����һ������ֻ�ܷ���һ������Ϣ��\n" NOR);
                return;
        }

        me->set_temp("last_send_msg", time());

        if (! send_msg(me, tar, msg))
        {       
                tell_object(me, HIR "���л���ʹ�������Ͷ���Ϣʧ�ܡ�\n" NOR);
                return;
                
        } else
                tell_object(me, HIC "���л���ʹ������Ķ���Ϣ�Ѿ��ɹ����ͣ�\n" NOR);

        return;

}

int send_msg(object me, string tar, string msg)
{
         int num_tail, msg_all, t;
         string tmp_num_tail;
         object ob, z_ob;
         mapping message;
         mixed lt;

         ob = UPDATE_D->global_find_player(tar);
         message = ob->query("message");
         msg_all = sizeof(message);
         
         if (! wizardp(ob) && msg_all >= PLAYER_MAX_MSG)
         {
               write("������Ҷ���Ϣ������\n");
               return 0;
         }

         if (wizardp(ob) && msg_all >= WIZ_MAX_MSG)
         {
               write("����ʦ����Ϣ������\n");
               return 0;
         }

         //if (! ob->query("evn/receive_msg")) --->��ֹ����

         // ��鳤��
         if (sizeof(msg) > 1000)
         {
              write("����Ϣ����������ܴ���1000���ֽڡ�\n");
              return 0;
         }
         write(sizeof(msg) + " bytes.\n");

         t = time();
         lt = localtime(t);

         msg_all += 1;
         ob->set("message/msg" + msg_all + "/is_new", 1);
         ob->set("message/msg" + msg_all + "/sender", me->name() + "(" + me->query("id") + ")");
         ob->set("message/msg" + msg_all + "/time", sprintf("%d-%02d-%02d %02d:%02d",
                                                    lt[LT_YEAR], 
                                                    lt[LT_MON] + 1,
                                                    lt[LT_MDAY],
                                                    lt[LT_HOUR],
                                                    lt[LT_MIN])
         );

         ob->set("message/msg" + msg_all + "/content", msg);
          
         ob->save();
         UPDATE_D->global_destruct_player(ob, 1);
         
         if (objectp(z_ob = find_player(tar)))
         {
                 tell_object(z_ob, HIC"�л���ʹ��ʾ�������µĶ���Ϣ�ˣ���鿴��\n"NOR);
                 tell_object(z_ob, BEEP);
         }
         
         return 1; 
}

int read_msg(object me, mixed id)
{
        int num, msg_all;
        int i, count;
        string tmp, tmp_num;
        
        if (stringp(id))sscanf(id, "%d", num);
        if (intp(id)) num = id;

        msg_all = sizeof(me->query("message"));
       
        if (me->is_busy() || me->is_fighting())
        {
              write("����æ������˵�ɣ�\n");
              return 1;
        }

        // ��ȡ���ж���Ϣ
        if (id == "all")
        {
              count = 0;
              for (i = 1; i <= sizeof(me->query("message")); i ++)
                        if (me->query("message/msg" + i + "/is_new"))
                                  count ++;
              if (count)write(HIY "\n���� " HIG + chinese_number(count) + HIY " ������Ϣ��"
                             "��ʹ�� " HIG "msg read new" HIY " ���Ķ���\n" NOR);
              else write(HIY "\n��û���յ�����Ϣ��\n" NOR);
              write(HIY "�ԡ�����������������������������������������������������������������������\n" NOR);
              if (msg_all == 0)
              {
                      write(HIG "�޶���Ϣ��\n" NOR);
                      write(HIY "�ԡ�����������������������������������������������������������������������\n" NOR);
                      return 1;
              }

              for (i = 1; i <= msg_all; i ++)
              {               
                      tmp = " ";
                      tmp += "��" + i + "��\t";
                      tmp += me->query("message/msg" + i + "/time") + "\t";
                      tmp += "By�� " + me->query("message/msg" + i + "/sender") + "\t";
                      if (me->query("message/msg" + i + "/is_new"))
                             write(BBLU + HIW + tmp + "\n" NOR);
                      else write(HIC + tmp + "\n" NOR);                    

              }
              write(HIY "�ԡ�����������������������������������������������������������������������\n" NOR);             
              return 1;

        } else 
        // ��ȡ�¶���Ϣ
        if (id == "new")
        {

              if (msg_all == 0)
              {
                      write(HIY "�ԡ�����������������������������������������������������������������������\n" NOR);
                      write("�޶���Ϣ��\n");
                      write(HIY "�ԡ�����������������������������������������������������������������������\n" NOR);
                      return 1;
              }

              for (i = 1; i <= msg_all; i ++)
              {               
                      if (me->query("message/msg" + i + "/is_new"))
                      {
                              read_msg(me, i);
                              break;         
                      }                      
              }
              
              if (i - 1 == msg_all)write("������Ϣ��\n");

              return 1;

        } else
        // ��ȡָ������Ϣ  
        if (num <= msg_all && num > 0)
        {          
              write(HIY "�ԡ�����������������������������������������������������������������������\n" NOR);   
              if (msg_all == 0)
              {
                      write("�޶���Ϣ��\n");
                      write(HIY "�ԡ�����������������������������������������������������������������������\n" NOR);
                      return 1;
              }
              
              write(NOR + WHT "\tBy��\t" + me->query("message/msg" + num + "/sender") + "\t" NOR);
              write(NOR + WHT + me->query("message/msg" + num + "/time") + "\n" NOR);
              write(NOR + WHT "��-----------------------------------------------------------------------��\n" NOR);
              tmp = NOR + WHT + me->query("message/msg" + num + "/content") + "\n\n" NOR;
              write("\t" + sort_msg(tmp));
              write(NOR + WHT "��----------------------THE END------------------------------------------��\n" NOR);
              write(HIY "�ԡ�����������������������������������������������������������������������\n" NOR);
              me->set("message/msg" + num + "/is_new", 0);
              return 1;
        }
        
        else 
              return help(me);

}

int discard_msg(object me, string id)
{
        int num, msg_all;
        int i;
        string *msgs;
        mapping mmsgs;
        
        sscanf(id, "%d", num);
        
        msg_all = sizeof(me->query("message"));       

        // ɾ�����ж���Ϣ
        if (id == "all")
        {
              if (msg_all == 0)
              {
                      write("�޶���Ϣ��\n");
                      return 1;
              }
        
              me->delete("message");
              write("OK.\n");
              return 1;
        } else         
        if (num <= msg_all && num > 0)
        {
              if (msg_all == 1)
              {
                  me->delete("message");
                  write("OK.\n");
                  return 1;
              }
              
              me->delete("message/msg" + num);
              
              // ɾ�����һ������Ҫ��������
              if (msg_all == num){write("OK.\n");return 1;}
              
              // ��������              
              msg_all = sizeof(me->query("message"));
              
              mmsgs = me->query("message");  
              msgs = keys(mmsgs);

              me->delete("message");
              for (i = 1; i <= sizeof(msgs); i ++)
              {
                     me->set("message/msg" + i + "/sender",
                             mmsgs[msgs[i - 1]]["sender"]);
                     me->set("message/msg" + i + "/time",
                             mmsgs[msgs[i - 1]]["time"]);
                     me->set("message/msg" + i + "/content",
                             mmsgs[msgs[i - 1]]["content"]);  
                     me->set("message/msg" + i + "/is_new",
                             mmsgs[msgs[i - 1]]["is_new"]);                                                                                              
                          
              }

              write("OK.\n");
              return 1;
        }
        
        else 
              return help(me);

}

int help(object me)
{
        write(@HELP
ָ���ʽ : 
           msg <send [id | -multiuser]>      ���Ͷ���Ϣ��ָ��/�����ҡ�
           msg <read [all | new | ���]>     ��ȡ����/��/ָ������Ϣ��
           msg <discard [all | ���]>        ɾ������/ָ������Ϣ��

���ָ����Է��ͻ������Ķ���Ϣ��
���͵Ķ���Ϣ��ʹ�����������Ҳ�����յ���

����msg read all�и�����ʾ��Ϊ����Ϣ��

HELP );
        return 1;
}


