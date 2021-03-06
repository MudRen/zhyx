//关帝庙 writed by yuchang

#include <ansi.h>
inherit ROOM;
#define MAX_EXP 20000000
#define MAX_SCO 200000
int check_name(string name,object me);
void create()
{
        set("short", "关帝庙");
        set("long", @LONG
    这里是扬州城内的关帝庙，时常有一些江湖豪客来此求签拜谒，
期盼能抽得一个好签，开创一世江湖霸业，庙的正中端座的是一尊关帝
像(xiang)，气宇昂然不凡，如果你想创建帮会的话，去求个签(qiuqian)
看看你的运气吧。
LONG);
        set("item_desc", ([
                "xiang" :
        "眼睛乱转什么，要求签就快点。\n"
        ]));
        set("exits",([ /* sizeof() == 1 */
                "east":"/d/city/wumiao",
        ]));

        set("no_fight",1);

        setup();
}

void init()
{
       add_action("do_qiuqian","qiuqian");
       add_action("do_kaibang","kaibang");
       if( time()-query("last_time")>600)
       delete("qiuqian"); 

}

int do_qiuqian()
{
       object me=this_player(),ob=this_object();

       if(!objectp(me) || !interactive(me) ) return 1;

       if(me->query("banghui"))
       {
          tell_object(me,"你已经是"+me->query("banghui/name")
                      +"的人了，难道想背叛原来的帮会？\n");
          return 1;
       }

       if(me->query("combat_exp") < MAX_EXP)
       {
          tell_object(me,RANK_D->query_respect(me)+"的实战经验还差"+
                      (string)(MAX_EXP-me->query("combat_exp"))
                      +"点，无法开帮立会。\n");
          return 1;
       }

       if(me->query("score") < MAX_SCO)
       {
          tell_object(me,RANK_D->query_respect(me)+"的综合评价还差"+
                      (string)(MAX_SCO-me->query("score"))
                      +"点，无法开帮立会。\n");
          return 1;
       }

       if(me->query("more_money") < 1)
       {
          tell_object(me,RANK_D->query_respect(me)+"，开帮立会需要一万两黄金，"
                      +"你帐目上的钱还不够。\n");
          return 1;
       }

       if( ob->query("qiuqian/"+me->query("id")) )
       return notify_fail("你已经求过签了，下次再来碰碰运气吧！\n");

       if( me->query_temp("qiuqian") )
       return notify_fail("你已经在求签了，耐心等你的签出来吧！\n");

       ob->set("qiuqian/"+me->query("id"),1);
       ob->set("last_time",time());
       message_vision("$N点起一柱香，口中喃喃默念道：弟子"+me->name()+
       "愿开帮立派，广济武林众生，求关帝爷\n赐个良辰吉日，以兴大业，"+
       "他日江湖一统，弟子必感恩戴德，重塑关帝爷金身！\n",me);

       me->set_temp("qiuqian",1);
       me->start_busy(10+random(2));
       call_out("qian_out",10,me);
       return 1;
}

void qian_out(object me)
{
      string msg;
      int time;
      string date;

      if(!objectp(me) || environment(me) != this_object() )
      return;

      me->delete_temp("qiuqian");

      msg = "“啪”的一声，一枚竹签掉$N你眼前！$N连忙将签拾"+
            "起一看，只见签上写道：\n";
      if( random(me->query("kar")) > random(30-me->query("kar")) )
      {
        time = ( uptime()+random(1000)+1000 )*365;
        date = CHINESE_D->chinese_date(time);
        me->set_temp("create_time",date);
        msg += HIY"\n        "+date+"\n"+NOR;
      } else
       msg +=  HIW"\n        "+"时运未济，不宜兴建\n"NOR;

      message_vision(msg,me);
      return;
}

int do_kaibang(string arg)
{
       object me=this_player(),lingpai;

       if(!objectp(me) || !interactive(me) ) return 1;

       if(! me->query_temp("create_time") )
       return notify_fail("你在这里做什么，连签都没求就要开帮啊？\n");

       if(me->query("more_money") < 1)
       {
          tell_object(me,RANK_D->query_respect(me)+"，开帮立会需要一万两黄金，"
                      +"你帐目上的钱还不够。\n");
          return 1;
       }

       if( me->query_temp("create_time") != NATURE_D->game_time() )
       return notify_fail("时辰未到呢，你着急什么呀？\n");

       if(!arg)
       return notify_fail("请用kaibang <帮会名> 创建帮会。\n");

       if(! check_name(arg,me)) return 1;

       me->delete_temp("create_time");

       lingpai=new(__DIR__"obj/lingpai");
       lingpai->create(arg);
       lingpai->set("bangzhu",me->query("name"));
       lingpai->set("bangzhu_id",me->query("id"));
       lingpai->set("player",([me->query("id"):me->query("name")]));
       lingpai->set("npc",([]));
       lingpai->set("area",([]));
       lingpai->set("money",0);
       lingpai->save();
       destruct(lingpai);
       me->add("more_money",-1);
       me->set("banghui/name",arg);
       me->set("banghui/rank","帮主");
       me->set("banghui/rank_lv",9);
       me->save();

       message("channel:rumor",HIC"\n【帮会传闻】"+me->query("name")+
               "成功创立「"+arg+"」，天下苍生福兮祸兮？！\n" NOR,users());

       return 1;
}

int check_name(string name,object me)
{
        int i;

        i = strlen(name);

        if(file_size("/data/guild/"+name+".o")!=-1)
        {
                tell_object(me,"非常抱歉，你起的帮会名早就有了。\n");
                return 0;
        }

        if( (strlen(name) < 4) || (strlen(name) > 8 ) )
        {
                tell_object(me,"帮会名称请定在二到四个字之间。\n");
                return 0;
        }
        while(i--)
        {
               if( name[i]<=' ' )
               {
                        tell_object(me,"对不起，你的帮会名中不能用控制字符。\n");
                        return 0;
               }
               if( i%2 == 0 && !is_chinese(name[i..<0]) )
               {
                        tell_object(me,"请用「中文」命名你的帮会。\n");
                        return 0;
               }
        }
        return 1;
}


