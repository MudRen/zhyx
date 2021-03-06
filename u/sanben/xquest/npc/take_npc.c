#include <ansi.h>
inherit NPC;


int do_leave();

void create()
{
        NPC_D->generate_cn_name(this_object());
        set("gender", "男性");
        set("age", 60 + random(20));

        set("attitude", "friendly");
        set("str", 35);
        set("int", 15);
        set("con", 19);
        set("dex", 17);

        set("chat_chance", 100);
        set("chat_msg", ({
                (: do_leave :),
        }));

        setup();
        set_heart_beat(5);
        if (clonep()) keep_heart_beat();

        set("check_time", time());
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
           object ob = this_object();

      if ( environment(ob)->query("short") == ob->query("dest"))
      {
           remove_call_out("arrive");
           call_out("arrive", 2, ob);
       }
 }

int do_leave()
{
        object npc,me;       

        npc = this_object();
        me = query("leader");

        if ( time() - query("check_time") > 800 || ! me) 
         {
            message("vision", CYN + npc->name() + "急急忙忙地离开了。\n"NOR,
                   environment(npc));
            destruct(npc);
            return 1;
         }
        
        if (! environment())
                return 0;
        if ( npc->query("arrived") == 1 )
                return 0;
        
        if ( random(10) == 1 && environment(me) == environment(npc) )
        {
            npc->start_busy(2);
            message_vision(HIG "$N气喘嘘嘘地对$n"
                           "说道：“$n走慢点啊，老汉我跟不上了！”\n"
                           "说完就一个劲儿地咳嗽起来，一屁股坐倒在路边。\n"NOR,
                           npc, me);
        }
       
        if ( time() - query("check_time") > 600  //超过时间
             || ! me || me->query("xquest/target_npc") != npc->name() )           
                                                         //没完成就去取消了      
        {

                  message("vision", HIY "走着走着，" + npc->name() + "突然剧烈"
                          "咳嗽起来，进而吐血不，\n随即凄惨地说道：“罢了，"
                          "罢了，看来我的大限已至。\n只是临死前未能了却最后一"
                          "桩心愿，实在死不瞑目呀！”\n"NOR,
                          environment(npc));

                  if ( me && environment(me) == environment(npc))
                  {
                          tell_object( me, RED"你心中一惊，暗道：“完了，这"
                          + npc->name() + "要是一死线索可就断了，"
                          "这可如何是好！”\n"NOR);
                  }


                  CHANNEL_D->do_channel(npc, "rumor",
                  "听说"NOR HIY + npc->name() + NOR HIM"因年事已高而撒手人寰。"
                  "死前未能如偿所愿，实属遗憾。\n") ;
                  npc->die();
                  return 0;

        }
        return 1;
}


void arrive(object ob)
{
     object me, pay;
     int div, add;

     remove_call_out("arrive");
     me = ob->query("leader");
     
     if ( environment(ob)->query("short") == ob->query("dest")
          && ob->query("arrived") == 0 )
      {   
          if ( ! me->is_busy() ) me->start_busy(3);
          message("vision", HIC +ob->name() + "说道：“啊！想不到二十年未至，"
                  "故地仍是这般风景。然则虽风景依旧，唯独尔人事全非也！\n"
                  "老汉我赴黄泉之前尚有幸能来此地一游，死也得瞑目了！多谢这位"
                  + RANK_D->query_respect(me) + "助老汉了此心愿。”\n"NOR,
                  environment(ob));
          ob->set("arrived",1);
          ob->set_leader(0);
          div = 1;     //设置送任务奖励计算的参数
          add = 80;
          message_vision(CYN "$N从怀里掏出一些白银交给$n，说道：“这点算是"
                               "这一路上的车马费。辛苦你了！”\n" NOR,
                               ob, me);

          pay = new("/clone/money/silver");
          pay->set_amount(10+random(10));
          pay->move(me, 1);

          call_other(XQUEST, "reward", me, div, add);  //呼叫奖励涵数
          remove_call_out("finish");
          call_out("finish", 5, ob);
      }
}

void finish(object ob)
{
        message("vision", HIR +ob->name() + "说道：“现在老汉我终于可以安心地"
                          "去了。”\n" NOR,
                          environment(ob));
        ob->die();
}


void unconcious()
{
        die();
}
