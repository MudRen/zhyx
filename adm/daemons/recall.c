// recall.c Ψһ�鼮�����

#include <ansi.h>
#include <localtime.h>

inherit F_DBASE;

#define PATH     "/clone/lonely/book/"

nosave string *obs = ({
"/clone/book/lbook4",
"/clone/book/pixie_book",
"/clone/book/qiankun_book",
"/clone/book/yijinjing",
"/clone/book/daodejing-i",
"/clone/book/daodejing-ii",
"/clone/lonely/huangjinfu",
});


int min = 40;
int hr = localtime(time())[2];


void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "���⾫��");
        write("���⾫���Ѿ�������\n");
        set_heart_beat(60);
}


private void heart_beat()
{
     int* lt;
     lt = localtime(time());

     if ( hr == lt[2] && lt[1] == min)
     {
        remove_call_out("recall");
        call_out("recall", 1);
     }


}


void recall()
{
     int i;
     object ob, where;
     string *list = get_dir(PATH);

       for(i=0; i<sizeof(list); i++)
       {
             ob = find_object(PATH + list[i]);
         if ( ! ob ||
              base_name(ob) == "/clone/lonely/book/dugubook" ||
              base_name(ob) == "/clone/lonely/book/zhenjing" ||
              base_name(ob) == "/clone/lonely/book/zhongping" ||
              base_name(ob) == "/clone/lonely/book/zhaobook" ||
              base_name(ob) == "/clone/lonely/book/yaowang_book" ||
              base_name(ob) == "/clone/lonely/book/liumai-shenjian" )
              continue;

          where = environment(ob);
          if (! where ) continue;

          if (! where->is_player() )
          {  destruct(ob); continue;}

          if ( where->is_player() && where->query("balance") < 10000000)
          {
             CHANNEL_D->do_channel(this_object(),
                   "wiz", where->name() + "(" + where->query("id") + ")" +
                         "���ϵ�" + ob->name() + "�����ա�");


             tell_object(where, BLINK HIR"\n���������ʻ�������֧�����"
                              "ϵͳ�������ϵ�" + ob->name() +
                                NOR BLINK HIR"������!\n\n"NOR);
             destruct(ob);
             continue;
          }

          where->add("balance",-10000000);
          tell_object(where, BLINK HIY"\nϵͳ���������ʻ��۳�1000gold���!\n\n"NOR);
          CHANNEL_D->do_channel(this_object(),
                   "wiz", where->name() + "(" + where->query("id") + ")" +
                         "������" + ob->name() + "��");



       }

      for(i=0; i<sizeof(obs); i++)
      {
         ob = find_object(obs[i]);
         if (! ob) continue;

          where = environment(ob);
          if (! where ) continue;

          if (! where->is_player() )
          {  destruct(ob); continue;}

          if ( where->is_player() && where->query("balance") < 10000000)
          {

             tell_object(where, BLINK HIR"\n���������ʻ�������֧�����"
                              "ϵͳ�������ϵ�" + ob->name() +
                              NOR BLINK HIR"������!\n\n"NOR);
             CHANNEL_D->do_channel(this_object(),
                   "wiz", where->name() + "(" + where->query("id") + ")" +
                         "���ϵ�" + ob->name() + "�����ա�");
             destruct(ob);
             continue;
          }

          where->add("balance",-10000000);
          tell_object(where, BLINK HIY"\nϵͳ���������ʻ��۳�1000gold���!\n\n"NOR);
          CHANNEL_D->do_channel(this_object(),
                   "wiz", where->name() + "(" + where->query("id") + ")" +
                         "������" + ob->name() + "��");


     }

     message("vision", HIC"��ϵͳ��Ϣ��Ψһ�鼮�����ȡһ�Σ�"
              "�����ΪÿСʱ1000GOLD��\n"NOR, users());
     min = random(60);
     hr = hr + 1;
     if ( hr >23 ) hr = 0;

     CHANNEL_D->do_channel(this_object(),
                   "wiz", "��һ����ȡ���ʱ�䶨��" + hr + "��" +
                    min + "�֡�");

}
