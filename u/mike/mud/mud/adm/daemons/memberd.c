/********************************�л�Ӣ��ʷ��Ա����ϵͳ**********************************

 1��YH ��Աϵͳ�����ļ�����������/��ȡע���룬��Ա��ֵ����Ա����ϵͳ��壬��Ա
    �����Զ����ݵȡ�
 2������15λע���룬��Ч�ط�ֹ�½⣬��֤ϵͳ�İ�ȫ�ԺͿɿ��ԡ�
 3�����ö༶�ݴ��ʩ����ʷ��ֵ/�����¼��Ϣ��ǿ��Ч�Ľ��ͳ����ʺͱ�֤����
    �����ڲ�ѯ���޸ģ�ͬʱ���ⲻ��Ҫ����Ϣ��ʧ���������ݲ��ɸ�����ʷ��¼��
    Ϣ�жϺͲ�ѯ��
 4��������֤����ƣ���Ч�ط�ֹ�˷�admin����ʦͨ�������Ƿ��ֶλ�ȡ���޸����ݡ�
 5��Ϊʵ�����繺��/���縶���Զ����ṩ�����ƵĽӿڡ�

                                                        Create by yuchang for HERO JUN 2005
*****************************************************************************************/
// #pragma optimize
// #pragma save_binary

#include <ansi.h>
#include <localtime.h>

inherit F_DBASE;

#define SNF              "/data/member/membersn"
#define SNFHIS           "/data/member/membersnhistory"
#define SOURCE_DIR       "/data/member/"
#define DEST_DIR         "/backup/member/member"
#define MBACKUP_DIR      "/backup/member/"
#define DELAY_TIME       900
#define SAVE_DAYS        15
#define MLOG_PAY_DIR     "/data/member/mdata/log/log_pay/"
#define MLOG_BUY_DIR     "/data/member/mdata/log/log_buy/"
#define MDATA_DIR        "/data/member/mdata/data/"
#define GOODS_D          "/adm/daemons/goodsd"
#define SNLEN            13
#define SNFIR            "YH"
#define PER_MONTH_TIME   2678400
#define SNFFIR           "######�л���Աע����######"
#define SNFHISFIR        "#####�л�Ӣ�ۻ�Աע������ʷ�ļ�######"
#define PASSWD           "#####FORYHONLINEIS2003MADEBYRCWIZ#####"
#define VERSION          "V 1.00   "
#define PERCENT          3 / 100

public string bjtime(int seconds, int format);
public int get_end_time(string id);

void create()
{
        seteuid(getuid());
        set("channel_id", "��Աϵͳ");
        set("no_clean_up", 1);
        CHANNEL_D->do_channel(this_object(), "sys", "��Աϵͳ�Ѿ�������");
        remove_call_out("backup_data");
        call_out("backup_data", 10);
}

/************************��Ա��������***********************
  �������15��ĵ���
**********************************************************/
public void backup_data()
{
        mixed *file;
        int iCount = 0;
        string format_time;
        string *t;

        remove_call_out("backup_data");
        call_out("backup_data", DELAY_TIME);

        file = get_dir(MDATA_DIR, -1);
        if (! sizeof(file))return;

        format_time = bjtime(time(), 0);
        t = explode(format_time, ":");

        // һ��ֻ����һ��
        if (file_size(DEST_DIR + "-" + t[0] + "-" + t[1] + "-" + t[2]) != -1)
                return;

        // ����ʱ��ÿ������22:00 -- 0:00�䱸��
        if (t[3] != "22" && t[3] != "23")return;

        message_system(HIW "ϵͳ���ڶԻ�Ա�������б��ݣ����Ժ� ...\n" NOR);

        // ɾ������15��ĵ���
        file = get_dir(MBACKUP_DIR, -1);
        if (sizeof(file))
        {
                for (iCount = 0; iCount < sizeof(file); iCount ++)
                {
                        if (time() - file[iCount][2] >= SAVE_DAYS * 86400 )
                                "/cmds/wiz/rm"->rm_dir(MBACKUP_DIR + file[iCount][0]);
                }
        }

        // ���ݻ�Ա����
        "/cmds/wiz/cp"->copy_dir(SOURCE_DIR,
                                 DEST_DIR + "-" + t[0] +
                                 "-" + t[1] + "-" + t[2],
                                 0);

        message_system(HIW "ϵͳ������ϣ�\n" NOR);

        return;
}
/******************************************************
  �ӹ��ܵ��ã����ڶ�ȡע�����ע������ʷ�ļ�
******************************************************/
public mixed get_sn(int flag, string passwd)
{
      int nCount;
      string strtmpSn;
      string *sn, *snhistory;
      int lenth = SNLEN + 1;

      if (passwd != PASSWD)
           return "��Ч����֤�룡\n";

      nCount = 2;
      strtmpSn = "";

      sn = ({});
      snhistory = ({});

      if (flag) // ��ȡע����
      {
          while (strtmpSn = read_file(SNF, nCount, 1))
          {
               strtmpSn = strtmpSn[0..lenth];
               sn += ({ strtmpSn });
               strtmpSn = "";
               nCount ++;
          }

          sn[sizeof(sn) - 1] = "";
          sn -= ({ "" });

          return sn;
      }

      strtmpSn = "";
      while (strtmpSn = read_file(SNFHIS, nCount, 1))
      {
            strtmpSn = strtmpSn[0..lenth];
            snhistory += ({ strtmpSn });
            strtmpSn = "";
            nCount ++;
      }

      snhistory[sizeof(snhistory) - 1] = "";
      snhistory -= ({ "" });

      return snhistory;
}

/******************************************************
  �ӹ��ܵ��ã����ڼ���Ƿ�Ϊ��Ա
******************************************************/
public int is_member(string id)
{
      if (file_size(MDATA_DIR + id) == -1)
              return 0;

      return 1;
}

/******************************************************
  �ӹ��ܺ��ⲿ���ã����ڼ���Ƿ�Ϊ��Ч��Ա
******************************************************/
public int is_valib_member(string id)
{
      int end_time;

      if (! is_member(id))return 0;

      end_time = get_end_time(id);
      if (end_time - time() > 0)return 1;

      return 0;

}

/******************************************************
  �ӹ��ܺ��ⲿ���ã�
  1�����format = 0�����ر���ʱ�� (��:��:��:ʱ:��:��)
  2�����format = 1�������磺 2003-6-23 18:34:23 ��ʽ
******************************************************/
public string bjtime(int seconds, int format)
{
     string result;
     mixed t;

     t = localtime(seconds);

     if (format)
     {
         result = sprintf("%d-%02d-%02d %02d:%02d:%02d",
                          t[LT_YEAR],
                          t[LT_MON] + 1,
                          t[LT_MDAY],
                          t[LT_HOUR],
                          t[LT_MIN],
                          t[LT_SEC]);

         return result;
     }

     result = sprintf("%d:%02d:%02d:%02d:%02d:%02d",
                      t[LT_YEAR],
                      t[LT_MON] + 1,
                      t[LT_MDAY],
                      t[LT_HOUR],
                      t[LT_MIN],
                      t[LT_SEC]);

     return result;
}

/******************************************************
  �ӹ��ܵ��ã����ػ�Ա��Чʱ��
******************************************************/
public int get_end_time(string id)
{
     int end_time;
     string strtmp;

     if (file_size(MDATA_DIR + id) == -1)
     {
          write("�޴˻�Ա���򵵰����𻵣�\n");
          return 0;
     }
     if(! strtmp = read_file(MDATA_DIR + id, 2, 1))
     {
          write("��Ա��������\n");
          return 0;
     }
     sscanf(strtmp, "%d", end_time);

     return end_time;
}

/******************************************************
  �ӹ��ܺ��ⲿ���ã����ػ�Ա���׻ƻ�������
******************************************************/
public int get_yhb(string id)
{
     int yhb;
     string strtmp;

     if (file_size(MDATA_DIR + "YHB" + id) == -1)
     {
          write("�޴˻�Ա���򵵰����𻵣�\n");
          return 0;
     }
     if(! strtmp = read_file(MDATA_DIR + "YHB" + id, 2, 1))
     {
          write("��Ա��������\n");
          return 0;
     }
     sscanf(strtmp, "%d", yhb);

     return yhb;
}

/******************************************************
  �ӹ��ܵ��ã�����Ա����Ϣ����
******************************************************/
public int new_msg(object me)
{
     int iNew, msg_all, i;

     msg_all = sizeof(me->query("message"));

     if (msg_all == 0)return 0;

     iNew = 0;
     for (i = 1; i <= msg_all; i ++)
          if (me->query("message/msg" + i + "/is_new"))iNew ++;

     return iNew;
}

/******************** ����ע���� *******************************
����һ��15λ����ע�������ڻ�Ա��ֵ������ע����ǰ��ָ����������
count��ϵͳ������count����SNF�ļ���SNFHIS��ע���벻�ظ�������
δʹ�ù��ĵ�ע���룬Ȼ����д���ļ�SNF
****************************************************************/
public int make_sn(int snc, string passwd)
{
      string *sn, *snhistory, *makecodes;
      string strtmpSn;
      int nCount, i;

      // ע�����������
      string *codes = ({
               "A", "B", "C", "D", "E", "F", "G", "H", "I",
               "J", "K", "L", "M", "N", "O", "P", "Q", "R",
               "S", "T", "U", "V", "W", "X", "Y", "Z",
               "a", "b", "c", "d", "e", "f", "g", "h", "i",
               "j", "k", "l", "m", "n", "o", "p", "q", "r",
               "s", "t", "u", "v", "w", "x", "y", "z",
               "0", "1", "2", "3", "4", "5", "6", "7", "8",
               "9"
      });

      if (passwd != PASSWD)
      {
           write("��Ч����֤�룡\n");
           return 0;
      }
      if (snc == 0)return 0;

      if (file_size(SNF) == -1)
      {
            write("�ļ�" + SNF + "δ�ҵ���\n");
            return 0;
      }
      if (file_size(SNFHIS) == -1)
      {
            write("�ļ�" + SNFHIS + "δ�ҵ���\n");
            return 0;
      }

      // ��ȡע�������ʷע����
      sn = ({});
      snhistory = ({});
      sn = get_sn(1, PASSWD);
      snhistory = get_sn(0, PASSWD);

      // ��ʼ��
      strtmpSn = "";
      nCount = 0;
      makecodes = ({});

      while(1)
      {
            //��ʾ��������ȫ��ע����
            if (nCount >= snc)
            {
                  write("д�� " + nCount + " ��ע���룬�ɹ���\n");

                  if (nCount > 10)return 1;

                  for (i = 0; i < nCount; i ++)
                        write(HIW + makecodes[i] + "\n" NOR);

                  return 1;
            }

            // ����һ��ע����
            strtmpSn = SNFIR;
            for(i = 0; i < SNLEN; i ++)
            {
                  strtmpSn += codes[random(sizeof(codes))];
            }

            // ��֤ע���벻��SNF��SNFHIS�ظ�
            // ��ע�����ļ�����ʷע�����ļ���Ϊ�յ����
            if (! sizeof(sn) && ! sizeof(snhistory))
            {
                  // ������ע��������Ҳ������ͬ
                  if (! sizeof(makecodes))
                  {
                       if (! write_file(SNF, "\n" + strtmpSn, 0))
                       {
                            write("ע����д��ʧ�ܡ�\n");
                            return 0;
                       }
                       makecodes += ({ strtmpSn });
                       nCount ++;
                       continue;
                  }
                  else
                  {
                       if (member_array(strtmpSn, makecodes) != -1)
                       {
                            strtmpSn = "";
                            write("member_array(strtmpSn, makecodes\n");
                            continue;
                       }
                       if (! write_file(SNF, "\n" + strtmpSn, 0))
                       {
                            write("ע����д��ʧ�ܡ�\n");
                            return 0;
                       }
                       makecodes += ({ strtmpSn });
                       nCount ++;
                       continue;
                  }
            }
            else // ��������ע�����Ƿ���ע�������ʷע�����ظ�
            {
                  // ���ȼ��ע�����ļ�
                  if (sizeof(sn))
                  {
                       if (! sizeof(makecodes))
                       {
                            if (member_array(strtmpSn, sn) != -1)
                            {
                                  strtmpSn = "";
                                  continue;
                            }
                            if (! write_file(SNF, "\n" + strtmpSn, 0))
                            {
                                  write("ע����д��ʧ�ܡ�\n");
                                  return 0;
                            }
                            makecodes += ({ strtmpSn });
                            nCount ++;
                            continue;
                       }
                       else
                       {
                            if (member_array(strtmpSn, makecodes) != -1)
                            {
                                   strtmpSn = "";
                                   continue;
                            }
                            if (member_array(strtmpSn, sn) != -1)
                            {
                                  strtmpSn = "";
                                  continue;
                            }
                            if (! write_file(SNF, "\n" + strtmpSn, 0))
                            {
                                  write("ע����д��ʧ�ܡ�\n");
                                  return 0;
                            }
                            makecodes += ({ strtmpSn });
                            nCount ++;
                            continue;
                       }

                  }
                  if (sizeof(snhistory))
                  {
                       if (! sizeof(makecodes))
                       {
                            if (member_array(strtmpSn, snhistory) != -1)
                            {
                                  strtmpSn = "";
                                  continue;
                            }
                            if (! write_file(SNF, "\n" + strtmpSn, 0))
                            {
                                  write("ע����д��ʧ�ܡ�\n");
                                  return 0;
                            }
                            makecodes += ({ strtmpSn });
                            nCount ++;
                            continue;
                       }
                       else
                       {
                            if (member_array(strtmpSn, makecodes) != -1)
                            {
                                   strtmpSn = "";
                                   continue;
                            }
                            if (member_array(strtmpSn, snhistory) != -1)
                            {
                                  strtmpSn = "";
                                  continue;
                            }
                            if (! write_file(SNF, "\n" + strtmpSn, 0))
                            {
                                  write("ע����д��ʧ�ܡ�\n");
                                  return 0;
                            }
                            makecodes += ({ strtmpSn });
                            nCount ++;
                            continue;
                       }
                  }
            }
      }
}

/************************��ȡһ��ע����***************************
 ��ע�����ļ��ж�ȡһ��ע����
*****************************************************************/
public string read_sn(string passwd)
{
      string str;
      int lenth;

      if (passwd != PASSWD)return "��Ч����֤�룡\n";

      lenth = SNLEN + 1;
      if (str = read_file(SNF, 2, 1))
      {
           str = str[0..lenth];

           if (str[0..0] == "#")
                  return HIR "��ȡע����ʧ�ܣ�������ע���������꣬����ע�����ļ���\n" NOR;

           return str;
      }
      else
      {
           return HIR "��ȡע����ʧ�ܣ�������ע���������꣬����ע�����ļ���\n" NOR;
      }
}

/*******************ʹ��ע�����ֵ*********************************
 1��У��ע������Ч��
 2�������ֵ��¼
 3���޸Ļ�Ա����
 4����ע�����ļ���ɾ��ע���벢д�뵽ע������ʷ�ļ�

 ##�������������
   1����һ�γ�Ϊ��Ա
   2����Ա���ں��ֵ
   3����Աδ����ʱ������ֵ
*****************************************************************/
public int pay(object me, string str)
{
      string strtmpSn;
      string *sn, *snhistory;
      int end_time, tmp_end_time;
      int i;

      /*********************************************************
       У��������ļ��Ƿ����
      **********************************************************/
      if (file_size(SNF) == -1)
      {
           write("δ�ҵ�ע�����ļ��������Ʊ��ܺ�����ע���룬��������ADMIN��ϵ��\n");
           return 0;

      }
      if (file_size(SNFHIS) == -1)
      {
           write("δ�ҵ���ʷע�����ļ��������Ʊ��ܺ�����ע���룬��������ADMIN��ϵ��\n");
           return 0;
      }

      // У��ע����
      sn = get_sn(1, PASSWD);

      if (sizeof(str) != SNLEN + 2)
      {
            return 0;
      }
      if (member_array(str, sn) == -1)
      {
            return 0;
      }

      // �����ֵ��¼
      if (file_size(MLOG_PAY_DIR + me->query("id")) == -1)
      {
           write_file(MLOG_PAY_DIR + me->query("id"),
                      sprintf("%s(%s)��%s׼���ó�ֵ�� %s ���г�ֵ��\n",
                              me->name(1),
                              me->query("id"),
                              bjtime(time(), 1),
                              str),
                     1);
      }
      else
      {
          write_file(MLOG_PAY_DIR + me->query("id"),
                     sprintf("%s(%s)��%s׼���ó�ֵ�� %s ���г�ֵ��\n",
                             me->name(1),
                             me->query("id"),
                             bjtime(time(), 1),
                             str),
                     0);
      }

      // ɾ��ע���벢д��ע������ʷ�ļ�
      // ��ע�����ļ���ɾ����ע����
      sn -= ({ str });
      if (! write_file(SNF, SNFFIR, 1))
      {
          write("���´���ע�����ļ�ʱʧ�ܣ����뱾վADMIN��ϵ��\n");
          write_file(MLOG_PAY_DIR + me->query("id"),
                     sprintf("���˴γ�ֵ�����޷�����ע�����ļ���ʧ�ܣ�\n",
                     me->name(1),
                     me->query("id"),
                     bjtime(time(), 1),
                     str),
          0);
          return 0;
      }
      for (i = 0; i < sizeof(sn); i ++)
      {
          if (sizeof(sn[i]) != SNLEN + 2)continue;

          if (! write_file(SNF, "\n" + sn[i], 0))
          {
               write("д��ע���뵵��ʧ�ܣ����뱾վADMIN��ϵ��\n");
               write_file(MLOG_PAY_DIR + me->query("id"),
                          sprintf("���˴γ�ֵ����д��ע���뵵�������ʧ�ܣ�\n",
                          me->name(1),
                          me->query("id"),
                          bjtime(time(), 1),
                          str),
               0);
               return 0;
          }
      }

      // д��ע���뵽��ʷע�����ļ�β
      if (! write_file(SNFHIS, "\n" + str, 0))
      {
          write("д��ע���뵽ע������ʷ�ļ�ʱʧ�ܣ����뱾վADMIN��ϵ��\n");
          write_file(MLOG_PAY_DIR + me->query("id"),
                     sprintf("���˴γ�ֵ����д��ע���뵽��ʷע�����ļ������ʧ�ܣ�\n",
                     me->name(1),
                     me->query("id"),
                     bjtime(time(), 1),
                     str),
          0);
          return 0;
      }

      // �޸Ļ�Ա����

      // ��һ�γ�Ϊ��
      if (! is_member(me->query("id")))
      {
            end_time = time() + PER_MONTH_TIME;
            strtmpSn = "";
            strtmpSn = sprintf("%d", end_time);
            if (! write_file(MDATA_DIR + me->query("id"), strtmpSn, 1))
            {
                    write("д�뵵��ʧ�ܣ����뱾վADMIN��ϵ��\n");

                    write_file(MLOG_PAY_DIR + me->query("id"),
                               sprintf("���˴γ�ֵ����д�뵵�������ʧ�ܣ�\n",
                               me->name(1),
                               me->query("id"),
                               bjtime(time(), 1),
                               str),
                    0);

                    return 0;
            }
            write(HIG "��ֵ�ɹ���\n" NOR);
            write(HIG "��ϲ����Ϊ��Ա�����Ļ�Ա���޻�ʣ�� 31 �죡\n");
            write(HIW "���Ļ�Ա����ʱ��Ϊ " + bjtime(end_time, 1) + " ��\n" NOR);
            me->set("member/join_time", time());
            me->add("member/pay_times", 1);
            me->set("member/buy_times", 0);
            me->set("member/last_paytime", time());

            write_file(MLOG_PAY_DIR + me->query("id"),
                       sprintf("���˴γ�ֵ�ɹ���\n",
                       me->name(1),
                       me->query("id"),
                       bjtime(time(), 1),
                       str),
            0);

            // Ϊ�佨���׻ƻ��Ҵ���ļ�
            write_file(MDATA_DIR + "YHB" + me->query("id"), "0", 1);

            call_out("show_member_info", 1, me->query("id"), "info", me);
            return 1;
      }

      // ���ڳ�ֵ
      if (is_member(me->query("id")) && ! is_valib_member(me->query("id")))
      {
            end_time = time() + PER_MONTH_TIME;
            strtmpSn = "";
            strtmpSn = sprintf("%d", end_time);
            if (! write_file(MDATA_DIR + me->query("id"), strtmpSn, 1))
            {
                    write("д�뵵��ʧ�ܣ����뱾վADMIN��ϵ��\n");

                    write_file(MLOG_PAY_DIR + me->query("id"),
                               sprintf("���˴γ�ֵ����д�뵵�������ʧ�ܣ�\n",
                               me->name(1),
                               me->query("id"),
                               bjtime(time(), 1),
                               str),
                    0);

                    return 0;
            }
            write(HIG "��ֵ�ɹ���\n" NOR);
            write(HIG "���Ļ�Ա���޻�ʣ�� 31 �죡\n");
            write(HIW "���Ļ�Ա����ʱ��Ϊ " + bjtime(end_time, 1) + " ��\n" NOR);
            me->add("member/pay_times", 1);
            me->set("member/last_paytime", time());

            write_file(MLOG_PAY_DIR + me->query("id"),
                       sprintf("���˴γ�ֵ�ɹ���\n",
                       me->name(1),
                       me->query("id"),
                       bjtime(time(), 1),
                       str),
            0);

            call_out("show_member_info", 1, me->query("id"), "info", me);
            return 1;
      }

      // δ���ڳ�ֵ
      if (file_size(MDATA_DIR + me->query("id")) == -1)
      {
            write("δ�ҵ����������뱾վADMIN��ϵ��\n");
            write_file(MLOG_PAY_DIR + me->query("id"),
                       sprintf("���˴γ�ֵ����δ�ҵ�������ʧ�ܣ�\n",
                       me->name(1),
                       me->query("id"),
                       bjtime(time(), 1),
                       str),
            0);
            return 0;
      }
      if (! strtmpSn = read_file(MDATA_DIR + me->query("id"), 2, 1))
      {
            write("��ȡ�����������뱾վADMIN��ϵ��\n");
            write_file(MLOG_PAY_DIR + me->query("id"),
                       sprintf("���˴γ�ֵ���ڶ�ȡ���������ʧ�ܣ�\n",
                       me->name(1),
                       me->query("id"),
                       bjtime(time(), 1),
                       str),
            0);
            return 0;
      }

      sscanf(strtmpSn, "%d", end_time);
      end_time += PER_MONTH_TIME;
      tmp_end_time = end_time;
      strtmpSn = "";
      strtmpSn = sprintf("%d", end_time);

      if (! write_file(MDATA_DIR + me->query("id"), strtmpSn, 1))
      {
            write("д�뵵���������뱾վADMIN��ϵ��\n");
            write_file(MLOG_PAY_DIR + me->query("id"),
                       sprintf("���˴γ�ֵ����д�뵵�������ʧ�ܣ�\n",
                       me->name(1),
                       me->query("id"),
                       bjtime(time(), 1),
                       str),
            0);
            return 0;
      }
      end_time -= time();
      end_time = (int)(end_time / 86400);
      me->add("member/pay_times", 1);
      write_file(MLOG_PAY_DIR + me->query("id"),
                 sprintf("���˴γ�ֵ�ɹ���\n",
                 me->name(1),
                 me->query("id"),
                 bjtime(time(), 1),
                 str),
      0);
      me->set("member/last_paytime", time());

      write(HIG "��ֵ�ɹ���\n" NOR);
      write(HIW "���Ļ�Ա���޻�ʣ�� " + end_time + " �졣\n" NOR);
      write(HIW "���Ļ�Ա����ʱ��Ϊ " + bjtime(tmp_end_time, 1) + " ��\n" NOR);
      call_out("show_member_info", 1, me->query("id"), "info", me);
      return 1;

}

/******************************************************
 ��Ա�������
 ������ʾ��Ա��Ϣ�������¼����ֵ��¼��
 �ɹ�����Ʒ����Ϣ��
******************************************************/
public void show_member_info(string id, string arg, object me)
{
      string strtmpSn;
      int i;
      float yhb_avg, hours;

      switch(arg)
      {
           // ��ֵ��¼
           case "payinfo":
                if (file_size(MLOG_PAY_DIR + id) == -1)
                {
                     write("��Ŀǰû�г�ֵ��¼��\n");
                     return;
                }
                write(BBLU + HIW "���ĳ�ֵ��¼���£�\n" NOR);
                i = 1;
                while(strtmpSn = read_file(MLOG_PAY_DIR + id, i, 1))
                {
                     write(BBLU + HIY + strtmpSn + NOR);
                     i ++;
                }
                break;
           // �����¼
           case "buyinfo":
                if (file_size(MLOG_BUY_DIR + id) == -1)
                {
                     write("��Ŀǰû�й����¼��\n");
                     return;
                }
                write(BBLU + HIW "���Ĺ����¼���£�\n" NOR);
                i = 1;
                while(strtmpSn = read_file(MLOG_BUY_DIR + id, i, 1))
                {
                     write(BBLU + HIY + strtmpSn + NOR);
                     i ++;
                }
                break;

           // ���
           case "info":
                write(BBLU + HIW "\t\t    �л�Ӣ��ʷ��Աϵͳ���\t\t  " + VERSION + "\n" NOR);
                write(HIW "��---------------------------------------------------------------��\n" NOR);
                write(HIY "WELCOME TO JOIN IN THE MEMBERS OF YHHERO AND HOPE YOU ALL GOES WELL.\n\n" NOR);
                write(sprintf(HIC "  ��Ա���ţ�%-25s��Чʱ�䣺%s\n" NOR,
                              id, bjtime(get_end_time(id), 1)));
                write(sprintf(HIC "  ���ʱ�䣺%-25s��ֵ������%d\n" NOR,
                              bjtime(me->query("member/join_time"), 1),
                              me->query("member/pay_times")));
                write(sprintf(HIC "  �����ۼƣ�%-25s���������%d\n" NOR,
                              me->query("member/buy_value") + " YHB",
                              me->query("member/buy_times")));
                write(sprintf(HIC "  ת���ۼƣ�%-25sת�ʴ�����%d\n" NOR,
                              me->query("member/virement_value") + " YHB",
                              me->query("member/virement_times")));
                write(sprintf(HIM "\n  �����һ�γ�ֵʱ����   %s\n" NOR,
                              bjtime(me->query("member/last_paytime"), 1)));
                write(sprintf(HIM "  �����һ�ι���ʱ����   %s\n" NOR,
                              me->query("member/last_buytime") ?
                              bjtime(me->query("member/last_buytime"), 1):"��������"));
                write(sprintf(HIM "  �����һ�ι�����Ʒ��   %s(%s YHB)\n" NOR,
                              stringp(me->query("member/last_buyob")) ?
                              me->query("member/last_buyob"):"��������",
                              stringp(me->query("member/last_buyvalue")) ?
                              me->query("member/last_buyvalue"):"0"));

                write(sprintf(HIY "\n  �׻ƻ��ң�%d YHB\n  �ۼ�׬ȡ��%d YHB\n" NOR,
                              get_yhb(id),
                              get_yhb(id) + me->query("member/buy_value") +
                              me->query("member/virement_value") +
                              me->query("member/virement_value") * PERCENT));

                // ������Ϊ1Сʱ
                hours = (time() - me->query("member/join_time")) / 3600;
                if (hours < 1)hours = 1;
                yhb_avg = (get_yhb(id) + me->query("member/buy_value") +
                          me->query("member/virement_value") +
                          me->query("member/virement_value") * PERCENT) / hours;
                yhb_avg = (float)(yhb_avg * 24.0);

                write(sprintf(HIY "  ƽ��������%.1f YHB / �� |  Ԥ�� %.1f YHB / ��\n" NOR,
                              yhb_avg, (float)(yhb_avg * 30)));

                write(sprintf(HIW "\n  �¶���Ϣ��%s\n" NOR,
                              new_msg(me) > 0 ?
                              new_msg(me) + " ��  ����ʹ�� msg read new ��ȡ"
                              : new_msg(me) + " ��  ����ʹ�� help msg �鿴����Ϣϵͳʹ�÷���"));

                write(HIG "\n  *��ʹ��" HIR " member show info " HIG "      ���л���Աϵͳ��塣\n" NOR);
                write(HIG "  *��ʹ��" HIR " member show payinfo " HIG "   �鿴��ʷ��ֵ��¼��\n" NOR);
                write(HIG "  *��ʹ��" HIR " member show buyinfo " HIG "   �鿴������Ʒ��¼��\n" NOR);
                write(HIG "  *��ʹ��" HIR " member show zhuaninfo " HIG " �鿴��ʷת�ʼ�¼��\n" NOR);
                write(HIG "  *��ʹ��" HIR " member show goods " HIG "     �鿴Ӣ���̵���۵���Ʒ��\n" NOR);
                write(HIG "  *��ʹ��" HIR " member pay ע���� " HIG "     ���ɻ�ѡ�\n" NOR);
                write(HIG "  *��ʹ��" HIR " member buy ��Ʒ���� " HIG "   ������Ʒ��\n" NOR);
                write(HIG "  *��ʹ��" HIR " member ?? " HIG "             �鿴memberָ���ʹ�÷�����\n\n" NOR);
                write(HIR "  *Ϊ�����������Ҫ����ʧ�������Ķ��л���Ա�ƶ��ļ� " HIY "help member\n\n" NOR);
                write(HIY "                (" HIR"Y��H" HIY ").YHHERO WIZARD GROUP http://yhhero."
                      "vicp.net\n" NOR);
                write(HIW "��---------------------------------------------------------------��\n" NOR);

                break;
           // ��Ʒ�嵥
           case "goods":
                GOODS_D->show_goods();
                break;

           // ת�ʼ�¼
           case "zhuaninfo":
                if (file_size(MLOG_PAY_DIR + "ZZYHB" + id) == -1)
                {
                     write("��Ŀǰû��ת�ʼ�¼��\n");
                     return;
                }
                write(BBLU + HIW "����ת�ʼ�¼���£�\n" NOR);
                i = 1;
                while(strtmpSn = read_file(MLOG_PAY_DIR + "ZZYHB" + id, i, 1))
                {
                     write(BBLU + HIY + strtmpSn + NOR);
                     i ++;
                }
                break;
           default:
                break;
      }

      return;
}
/**********************************************************
     ������ҵ�YHB
***********************************************************/
public int add_yhb(string id, int amount, string passwd)
{
      int yhb;
      string strtmp;

      if (passwd != PASSWD)
      {
           write("�Ƿ�����֤�룡\n");
           return 0;
      }

      if (file_size(MDATA_DIR + "YHB" + id) == -1)
      {
           write("δ�ҵ�ָ���ļ������뱾վADMIN��ϵ��\n");
           return 0;
      }

      yhb = get_yhb(id);

      yhb += amount;
      if (yhb <= 0)yhb = 0;

      strtmp = sprintf("%d", yhb);

      if (! write_file(MDATA_DIR + "YHB" + id, strtmp, 1))
      {
            write("д���ļ��������뱾վADMIN��ϵ��\n");
            return 0;
      }

      return 1;
}
/**********************ת��YHB**********************************
   ֻ��Ϊ��Ч��Ա��ת�ʣ�
   ÿ��ת�ʿ۳�ת�ʽ���3%
**********************************************************************/
public int virement_yhb(string me_id, string tar_id, int amount, object me)
{
      string strtmp;
      int yhb_me, yhb_tar, yhb_reduce_me;
      int flag = 0;

      // �ж�˫���Ƿ�Ϊ��Ч��Ա
      if (! is_valib_member(me_id))
      {
           write("���Ļ�Ա��Ч�����ѹ����뼰ʱ��ֵ��\n");
           return 0;
      }

      if (! is_valib_member(tar_id))
      {
           write("Ŀ�� " + tar_id + " Ϊ����Ч��Ա��\n");
           return 0;
      }

      if (file_size(MDATA_DIR + "YHB" + me_id) == -1)
      {
           write("���YHB�����������뱾վADMIN��ϵ��\n");
           return 0;
      }

      if (file_size(MDATA_DIR + "YHB" + tar_id) == -1)
      {
           write("Ŀ�� " + tar_id + " ��YHB�����������뱾վADMIN��ϵ��\n");
           return 0;
      }

      if (amount <= 100)
      {
           write("ת�ʽ��������100 YHB��\n");
           return 0;
      }

      yhb_me = get_yhb(me_id);
      yhb_reduce_me = amount * PERCENT;
      if (amount + yhb_reduce_me > yhb_me)
      {
          write("���YHB�������޷�֧��ת�ʷ��á�\n");
          return 0;
      }

      if (add_yhb(me_id, -1 * (amount + yhb_reduce_me), PASSWD))
      {
          if (add_yhb(tar_id, amount, PASSWD))
          {
                write(HIC "�ɹ��� " + amount + " YHB ת�� " + tar_id + " �ʻ���\n" NOR);
                write(HIC "���ܹ�֧�� " + yhb_reduce_me + " YHB ��ת�ʷ��ã�\n" NOR);
                write(HIC "����ת�ʼ�¼��д���ļ�����ʹ�� " HIR "member show zhuan"
                      "info " HIC "�鿴��\n");
                // д��ת�ʼ�¼
                if (file_size(MLOG_PAY_DIR + "ZZYHB" + me_id) == -1)flag = 1;
                else flag = 0;

                me->add("member/virement_value", amount);
                me->add("member/virement_times", 1);
                write_file(MLOG_PAY_DIR + "ZZYHB" + me_id,
                           sprintf("%s(%s) �� %s �� %d YHB ת�� %s �ʻ���\n",
                           me->name(1),
                           me_id,
                           bjtime(time(), 1),
                           amount,
                           tar_id,
                           flag));

                return 1;
          }

          return 0;
      }

      return 0;
}
/**********************ͳ�����еĻ�Ա**********************************
   ����1����ͳ�Ƶ�id����
   ����0�����ʾ
**********************************************************************/
public mixed show_all_members(int flag)
{
      mixed *file;
      string *members;
      int nCount, m = 0;
      string status;
      object ob;
      string name, join_time;

      file = get_dir(MLOG_PAY_DIR, -1);


      if (! sizeof(file))
      {
           if (flag)return ({});
           write(HIG "���޻�Ա��\n" NOR);
           return;
      }

      members = ({});
      for (nCount = 0; nCount < sizeof(file); nCount ++)
      {
             members += ({ file[nCount][0] });
      }

      if (flag)return members;

      write(HIM "�������л�Ӣ��ʷ�����л�Ա�б�\n" NOR);
      write(HIW "��-------------------------------------------------------------------��\n" NOR);

      write(sprintf(HIR "%-18s%-18s%-26s%-20s\n\n" NOR,
                    "��  ��", "��  ��", "���ʱ��", "״  ��"));

      for (nCount = 0; nCount < sizeof(members); nCount ++)
      {
             if (ob = find_player(members[nCount]))
             {
                  if (ob->query("doing"))status = HIY "�ƻ���" NOR;
                  else if (interactive(ob) && query_idle(ob) > 120)status = HIM "����" NOR;
                  else if (is_valib_member(members[nCount]))status = HIW "����" NOR;
                  else status = HIR "����" NOR;
                                name = ob->name(1);
                                join_time = bjtime(ob->query("member/join_time"), 1);
             }
             else
             {
                  if (is_valib_member(members[nCount]))status = NOR + WHT "����" NOR;
                  else status = HIR "����" NOR;
                                name = "������";
                                join_time = "������";
             }

             write(sprintf(HIG "%-18s%-18s%-26s%-20s\n" NOR,
                           name,
                           members[nCount],
                           join_time,
                           status));

             m ++; // ���˵�ת�ʼ�¼�ļ���ʵ�ʻ�Ա��

      }
      write(HIY "\n�ܹ��� " + m + " ��ע���Ա��\n" NOR);
      write(HIW "��-------------------------------------------------------------------��\n\n" NOR);
      return 1;
}

public int remove_member(string id)
{
      object ob;
      if (! is_member(id))
      {
           write("Ŀ��Ϊ�ǻ�Ա��\n");
           return 0;
      }

      rm(MDATA_DIR + id);
      rm(MDATA_DIR + "YHB" + id);
      rm(MLOG_PAY_DIR + id);
      rm(MLOG_PAY_DIR + "ZZYHB" + id);
      rm(MLOG_BUY_DIR + id);
      ob = UPDATE_D->global_find_player(id);
      if (! objectp(ob))
      {
            write("û�������ҡ�\n");
            return 0;
      }
      ob->delete("member");
      UPDATE_D->global_destruct_player(ob, 1);

      write("�ɹ�ɾ����Ա " + id + " ��\n");
      return 1;
}
