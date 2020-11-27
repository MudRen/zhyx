// 捆仙绳(纯粹捉弄wiz的工具)
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "捆仙绳" NOR, ({ "kunxian sheng", "rope" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "若被此绳捆住,任你是大罗金仙也无法脱离！\n" NOR);
                set("unit", "根");
                set("value", 10);
                set("no_sell",1);
                set("weight", 10);  
                set("no_drop", 1);                   
                set("no_put", 1);                                                        
             }
        setup();
}
void init()
{
        object me = this_player();
        object ob = this_object();

        if ( environment(ob)->query("id") == "xiner" )        
           add_action("do_kun","kun");        
        else if ( environment(ob)->is_player())          
        {    
     
        add_action("do_suicide", "suicide");
        add_action("do_drop", "drop");
        add_action("do_give", "give");
        add_action("do_give", "get");


        add_action("no_go", "rideto");
        add_action("no_go", "rideto1");
        add_action("no_go", "miss");
        add_action("no_go", "flyup");

        add_action("no_go", "trans");
        add_action("no_go", "recall");

        add_action("do_quit", "quit");
        add_action("do_quit", "exit");

        add_action("no_talk", "chat");
        add_action("no_talk", "chat*");
        add_action("no_talk", "sing");
        add_action("no_talk", "sing*");
        add_action("no_talk", "bill");
        add_action("no_talk", "shout");
        add_action("no_talk", "wiz");
        add_action("no_talk", "wiz*");
        add_action("no_talk", "es");
        add_action("no_talk", "es*");

        add_action("no_talk", "syschat");


        //wiz的法力也消失了，哈哈
        add_action("no_power", "home");
        add_action("no_power", "goto");
        add_action("no_power", "flyto");

        add_action("no_power", "more");
        add_action("no_power", "edit");
        add_action("no_power", "ls");
        add_action("no_power", "cd");
        add_action("no_power", "rm");
        add_action("no_power", "mv");
        add_action("no_power", "cp");

        add_action("no_power", "kickout");
        add_action("no_power", "purge");
        add_action("no_power", "summon");
        add_action("no_power", "promote");
        add_action("no_power", "throw");
        add_action("no_power", "dest");
        add_action("no_power", "auth");
        add_action("no_power", "free");
        add_action("no_power", "grant");
        add_action("no_power", "update");
        add_action("no_power", "data");
        add_action("no_power", "info");
        add_action("no_power", "call");
        add_action("no_power", "clone");
        add_action("no_power", "dual");
        add_action("no_power", "smash");
        add_action("no_power", "possess");
        add_action("no_power", "clear");
        add_action("no_power", "load");
        add_action("no_power", "fei");
        add_action("no_power", "whatcmds");
        add_action("no_power", "restore");
        add_action("no_power", "edit1");
        add_action("no_power", "rehash");
        add_action("no_power", "qiangpo");



        environment(ob)->start_busy(40);
  
        remove_call_out("busy");
        call_out("busy", 30, environment(ob));
       
      }
}


int no_talk()
{
        write(HIB"要想说话请用rumor频道,谢谢配合!\n"NOR);
        return 1;
}

int do_suicide()
{
        write(HIB"不要这么看不开嘛，何必自寻短剑呢！\n"NOR);
        return 1;
}

int do_give()
{
        write(HIG"你现在不能给东西！\n"NOR);
        return 1;
}

int do_drop()
{
        write(HIG"你现在不能乱仍东西！\n"NOR);
        return 1;
}

//想借助工具逃跑？

int no_go()
{
        write(YEL"你现在浑身动弹不得!\n"NOR);
        return 1;
}


int do_quit()
{
        write(HIR"你现在就是退出游戏下回连线进来还是在这里，"
              "所以还是别quit了吧！\n"NOR);
        return 1;
}

//巫师也跑不了！ 哈哈 (当然除了主人瞎三笨,keke)

int no_power()
{
        write(HIC"被捆仙绳捆住了就算是神仙也没法力了！你死定了，哈哈！\n"NOR);
        return 1;
}

int do_kun(string arg)
{
   object ob;

   if (! arg)
   {
      write("你要把谁捆住？\n");
      return 1;
   }

   ob = present(arg,environment(environment(this_object()) ));

   if (! ob)
   {
      write("这里没有这个人你怎么捆！\n");
      return 1;
   }
   if (! userp(ob))
   {
      write("捆仙绳只捆player！\n");
      return 1;
   }
   if ( ob->query("id") == this_player()->query("id"))
   {
      write("自己捆自己？你是不是脑子有水？！\n");
      return 1;
   }
   message_vision(HIY"只见$N扬起手中捆仙绳，大喝一声“疾！”。捆仙绳顿时将$n"
                     "捆了个严严实实。。。\n\n"NOR, this_player(),ob);
   this_object()->move(ob,1);
   return 1;

}

int busy(object victim)
{

   victim->start_busy(40);
  
   remove_call_out("busy");
   call_out("busy", 30, victim);

   tell_object(victim, HIR"\n你被捆仙绳给捆住了,"
                        "快想想办法怎么脱身吧!\n\n"NOR);

   return 1;

}


int query_autoload() 
{ return 1; }

