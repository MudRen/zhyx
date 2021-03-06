// recall.c 唯一书籍收租金

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
        set("channel_id", "收租精灵");
        write("收租精灵已经启动。\n");
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
                         "身上的" + ob->name() + "被回收。");


             tell_object(where, BLINK HIR"\n因你银行帐户不足以支付租金，"
                              "系统将你身上的" + ob->name() +
                                NOR BLINK HIR"回收了!\n\n"NOR);
             destruct(ob);
             continue;
          }

          where->add("balance",-10000000);
          tell_object(where, BLINK HIY"\n系统从你银行帐户扣除1000gold租金!\n\n"NOR);
          CHANNEL_D->do_channel(this_object(),
                   "wiz", where->name() + "(" + where->query("id") + ")" +
                         "身上有" + ob->name() + "。");



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

             tell_object(where, BLINK HIR"\n因你银行帐户不足以支付租金，"
                              "系统将你身上的" + ob->name() +
                              NOR BLINK HIR"回收了!\n\n"NOR);
             CHANNEL_D->do_channel(this_object(),
                   "wiz", where->name() + "(" + where->query("id") + ")" +
                         "身上的" + ob->name() + "被回收。");
             destruct(ob);
             continue;
          }

          where->add("balance",-10000000);
          tell_object(where, BLINK HIY"\n系统从你银行帐户扣除1000gold租金!\n\n"NOR);
          CHANNEL_D->do_channel(this_object(),
                   "wiz", where->name() + "(" + where->query("id") + ")" +
                         "身上有" + ob->name() + "。");


     }

     message("vision", HIC"【系统消息】唯一书籍租金收取一次，"
              "现租金为每小时1000GOLD。\n"NOR, users());
     min = random(60);
     hr = hr + 1;
     if ( hr >23 ) hr = 0;

     CHANNEL_D->do_channel(this_object(),
                   "wiz", "下一次收取租金时间定在" + hr + "点" +
                    min + "分。");

}
