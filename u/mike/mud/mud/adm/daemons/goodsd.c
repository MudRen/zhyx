// �л�Ӣ���̵������ƷС�����ݿ�ϵͳ

#include <ansi.h>

#define MEMBER_D              "/adm/daemons/memberd"
#define MLOG_BUY_DIR          "/data/member/mdata/log/log_buy/"
#define PASSWD                "#####FORYHONLINEIS2003MADEBYRCWIZ#####"

mapping goods = ([
      "obint9"                : "���ͨ���ɵ�:10000:/clone/fam/gift/int3:object",
      "obcon9"                : "ϴ�������ɵ�:10000:/clone/fam/gift/con3:object",
      "obstr9"                : "�����Ԫ�ɵ�:10000:/clone/fam/gift/str3:object",
      "obdex9"                : "�����޼��ɵ�:10000:/clone/fam/gift/dex3:object",
      "obint10"               : "���ͨ���ɵ�����:20000:/clone/fam/gift/int4:object",
      "obcon10"               : "ϴ�������ɵ�����:20000:/clone/fam/gift/con4:object",
      "obstr10"               : "�����Ԫ�ɵ�����:20000:/clone/fam/gift/str4:object",
      "obdex10"               : "�����޼��ɵ�����:20000:/clone/fam/gift/dex4:object",
      
      "obcint"                : "���۵�:60000:/clone/fam/gift/cint:object",
      "obccon"                : "���ǵ�:60000:/clone/fam/gift/ccon:object",      
      "obcdex"                : "��ﵤ:60000:/clone/fam/gift/cdex:object",      
      "obcstr"                : "���鵤:60000:/clone/fam/gift/cstr:object",      
      
      "obzhenyu"              : "����������:100000:/clone/fam/max/zhenyu:object",
      "oblongjia"             : "�������׵�:60000:/clone/fam/max/longjia:object",
      "obxuanhuang"           : "�������䵤:60000:/clone/fam/max/xuanhuang:object",
      "obtsxuantie"           : "��ɽ����:60000:/clone/fam/item/xuantie:object",
      "obhytianjing"          : "����쾧:400000:/d/death/obj/tianjing:object",
      
      "yanlongjia"            : "�����}��:320000:/clone/fam/armor/yanlongjia:object",
      "zijiaojia"             : "�����ۼ�:350000:/clone/fam/armor/zijiaojia:object",
      "shenhujia"             : "��ս��:350000:/clone/fam/armor/shenhujia:object",
      "fenghuangpf"           : "�������:400000:/clone/fam/armor/fenghuangjia:object",
      "shhuwan"               : "�񻢻���:68000:/clone/fam/armor/baihuwrists:object",
      "shyaodai"              : "������:68000:/clone/fam/armor/baihuyaodai:object",
      "fhyaodai"              : "�������:68000:/clone/fam/armor/fenghuangyaodai:object",
      "fhtouguan"             : "���ͷ��:68000:/clone/fam/armor/fenghuanghead:object",
      "zjyaodai"              : "��������:68000:/clone/fam/armor/zijiaoyaodai:object",
      "zjtoulu"               : "����ͷ­:68000:/clone/fam/armor/zijiaohead:object",
      "ylyaodai"              : "��������:68000:/clone/fam/armor/yanlongyaodai:object",
      "ylshenguan"            : "�������:68000:/clone/fam/armor/yanlonghead:object",
      "qkwater"               : "Ǭ��ʥˮ:20000:/clone/fam/item/bless_water:object",      
      
      "accuracy"              : "��׼���:50000:/kungfu/special/accuracy:special",
      "agile"                 : "�������:50000:/kungfu/special/accuracy:special",
      "clever"                : "�츳��ӱ:50000:/kungfu/special/accuracy:special",
      "constitution"          : "��������:50000:/kungfu/special/constitution:special",
      "cunning"               : "��������:50000:/kungfu/special/cunning:special",
      "dexterity"             : "��������:50000:/kungfu/special/dexterity:special",
      "divine"                : "�ƾ�����:50000:/kungfu/special/divine:special",
      "energy"                : "���ǻ���:50000:/kungfu/special/energy:special",
      "greedy"                : "����ת��:50000:/kungfu/special/greedy:special",
      "hatred"                : "ɱ������:50000:/kungfu/special/hatred:special",
      "health"                : "����Ǭ��:50000:/kungfu/special/health:special",
      "herb"                  : "����֪ʶ:50000:/kungfu/special/herb:special",
      "intellect"             : "�����:50000:/kungfu/special/intellect:special",
      "ironskin"              : "ͭƤ����:50000:/kungfu/special/ironskin:special",
      "lucky"                 : "���Ǹ���:50000:/kungfu/special/lucky:special",
      "might"                 : "����ȭ:50000:/kungfu/special/might:special",
      "mystery"               : "���ƾ���:50000:/kungfu/special/mystery:special",
      "potential"             : "Ǭ������:50000:/kungfu/special/potential:special",
      "power"                 : "������:50000:/kungfu/special/power:special",
      "self"                  : "С������ת:50000:/kungfu/special/self:special",
      "strength"              : "����Ѫ��:50000:/kungfu/special/strength:special",
      "trick"                 : "����ƪ:50000:/kungfu/special/trick:special",
      "wrath"                 : "��ŭ֮��:50000:/kungfu/special/wrath:special",
      "youth"                 : "������פ:50000:/kungfu/special/youth:special",

      "water"                 : "ʥ��ɹ�:30000:int:story",
      "sun"                   : "�ճ�ɹ�:30000:str:story",
      "feng"                  : "����ɹ�:30000:dex:story",
      "lighting"              : "����ɹ�:30000:con:story",

      "manual1"               : "��ѡ�츳:200000:manual:byadmin&newid",
      "manual2"               : "��������ʱ�ڹ�����:400000:manual:byadmin",
      "manual3"               : "��ɷ����:2000000:manual:byadmin&newid",
      "manual4"               : "��������:2000000:manual:byadmin&newid",
      "manual5"               : "�ż�����:500000:manual:byadmin",
      "manual6"               : "ʮ������:2000000:manual:byadmin",
      "manual7"               : "�����:700000:manual:byadmin",      

]);

private string get_types(string types)
{
      switch(types)
      {
           case "object"             :    return HIC "��Ʒ" NOR;
           case "special"            :    return HIG "���⼼��" NOR;
           case "story"              :    return HIM "����" NOR;
           case "byadmin"            :    return HIR "��" NOR;
           case "newid"              :    return HIY "��" NOR;
           case "byadmin&newid"      :    return HIR "��" HIY "��" NOR;
           default                   :    return HIR "δ֪" NOR;
      }
}

private void log_buyinfo(string id, string which, int value, object me)
{
      int flag;
      string strvalue;

      if (file_size(MLOG_BUY_DIR + id) == -1)
      {
          flag = 1;
      }
      else flag = 0;

      strvalue = sprintf("%d", value);

      write_file(MLOG_BUY_DIR + id, 
                 sprintf("%s(%s)��%s���� %s YHB������Ʒ %s 1��\n",
                 me->name(1), 
                 me->query("id"), 
                 MEMBER_D->bjtime(time(), 1),
                 strvalue,
                 which),
      flag);
      me->add("member/buy_times", 1);
      me->add("member/buy_value", value);
      me->set("member/last_buytime", time());
      me->set("member/last_buyob", which);
      me->set("member/last_buyvalue", strvalue);

      return;
}

/***************��ʾ������Ʒ����ϸ�嵥********************************
*********************************************************************/
public void show_goods()
{
      string strtmp;
      int i;
      string *all, *items;

      all = keys(goods);
      
      write(HIY "Ӣ���̵�Ŀǰ�������»��\n" NOR);
      write(sprintf(HIW "%-22s%-22s%-23s%s\n" NOR, 
            "��  ��", "��  ��", "��  ��( YHB)", "��  ��"));                                           
      write(HIG "-------------------------------------------------------------------------------\n\n" NOR);
      for (i = 0; i < sizeof(all); i ++)
      {
           strtmp = "";
           items = ({});
           
           strtmp = goods[all[i]];         
           items = explode(strtmp, ":");
           if (sizeof(items) != 4)
           {
               write("strtmp made items != 4 is : " + strtmp + "\n");
               return;
           }
           write(sprintf(HIW "%-22s%-22s%-37s%s\n" NOR, 
                   items[0], all[i], HIY + items[1] + HIW, get_types(items[3])));
      }
      
      write(HIG "\n��ʹ�� " + HIR + "member buy ��Ʒ���� " + HIG + "��������Ʒ��\n" NOR);
      write(HIG "�����������" HIR "��" HIG "��ǵķ����Ϊ���" HIW "ADMIN" HIG "��ϵ�ֶ�ʵ�֡�\n" NOR);
      write(HIG "�����������" HIY "��" HIG "��ǵķ����Ϊֻ����ID���š�\n" NOR);
      write(HIG "������Ʒ������˵����������μ��ļ� " HIR "help hero_shop" HIG " ��\n" NOR);
      write(HIG "�������Ķ��й�˵��������ǰ�뿼������� ���޲��ˡ���˻���\n" NOR);
      write(HIG "-------------------------------------------------------------------------------\n\n" NOR);
}

/**************************������Ʒ********************
 1������Ƿ�Ϊ��Ч��Ա
 2����ѯ��Ʒ�����Ƿ����
 3����ѯYHB�Ƿ��㹻
 4������ɹ�
 5��д�빺���¼�ļ�
******************************************************/
public int buy_goods(string who, string which, object me)
{
     string *all, *items, *specials;
     string strtmp;
     int i, value, yhb;
     object buy_ob;
 
     if (! MEMBER_D->is_member(who))
     {
           write("�Բ���ֻ�л�Ա�������ܴ˷�����μ� " HIR "help member " NOR " ��\n");
           return 0;
     }
     
     if (! MEMBER_D->is_valib_member(who))
     {
           write("���Ļ�Ա��Ч���ѹ��� �뼰ʱ��ֵ��\n");
           return 0;
     }

     all = keys(goods);
     if (member_array(which, all) == -1)
     {
           write("�Բ���û����Ҫ�������Ʒ " + HIR + which + NOR + "�� ��ʹ��"
                 " member show goods ��ѯ��\n" NOR); 
           return 0;

     }

     strtmp = goods[which];
     items = explode(strtmp, ":");
     sscanf(items[1], "%d", value);

     if (items[2] == "manual")
     {
          write("�Բ��𣬸÷�������� admin �ֶ�ʵ�֣��뼰ʱ�� admin ��ϵ��\n");
          return 0;
     }
     if (MEMBER_D->get_yhb(who) < value)
     {
            write("�Բ��������л���������������\n");
            return 0;
     }
     
     switch(items[3])
     {
           case "object":
                buy_ob = new(items[2]);
                if (! objectp(buy_ob))
                {
                     write("������Ʒʧ�ܣ����뱾վADMIN��ϵ��\n");
                     return 0;
                }
                buy_ob->move(me);
                MEMBER_D->add_yhb(who, -1 * value, PASSWD);
                log_buyinfo(who, items[0], value, me);
                write(HIG "����ɹ��� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buy"
                      "info " HIG " ��ѯ�� \n" NOR);
                write(HIC "���ܹ������� " HIY + value + HIC + " YHB, ף�����ˣ�\n" NOR);
                return 1;

           case "story":
                // ���ȼ���Ƿ��й�����
                if (me->query("gift/" + which))
                {
                      write("���Ѿ��й��ù����ˣ�\n");
                      return 0;
                }
                me->add("gift/" + which, 1);
                me->add(items[2], 1);
                MEMBER_D->add_yhb(who, -1 * value, PASSWD);
                log_buyinfo(who, items[0], value, me);

                write(HIG + items[0] + " �� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buy"
                      "info " HIG " ��ѯ�� \n" NOR);
                write(HIC "���ܹ������� " HIY + value + HIC + " YHB, ף�����ˣ�\n" NOR);
                return 1;

           case "special":
                // ���ȼ���Ƿ��и�special
                // ͬʱ����ܹ���special���ܴ���7
                if (! me->query("special_skill"))specials = 0;
                else specials = keys(me->query("special_skill"));
                if (1) // ��������
                {
                      if (sizeof(specials) > 0)
                      {
                            if (member_array(which, specials) != -1)
                            {
                                 write("�Բ������Ѿ���������⼼���ˣ�\n");
                                 return 0;
                            }
                            if (sizeof(specials) >= 7)
                            {
                                 write("�Բ���һ���ʺ����ֻ��ӵ���߸����⼼�ܣ�\n");
                                 return 0;
                            }
                      }

                      me->set("special_skill/" + which, 1);
                      // ����Ѫ������1������
                      if (which == "strength")
                            me->add("str", 1);

                      // ���������1������
                      if (which == "intellect")
                            me->add("int", 1);

                      // ������������1�����
                      if (which == "constitution")
                            me->add("con", 1);

                      // ������������1����
                      if (which == "dexterity")
                            me->add("dex", 1);

                      MEMBER_D->add_yhb(who, -1 * value, PASSWD);
                      log_buyinfo(who, items[0], value, me);
                      write(HIG "����ɹ��� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buy"
                            "info " HIG " ��ѯ�� \n" NOR);
                      write(HIC "���ܹ������� " HIY + value + HIC + " YHB, ף�����ˣ�\n" NOR);
                      return 1;
                }
                else 
                {
                      write("��ʱֹͣ�������⼼�ܣ����½⣡\n");
                      return 0;
                }
          default:
                write("��Ч��Ʒ���࣡\n");
                return 0;               
     }
}

