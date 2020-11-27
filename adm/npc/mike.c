//修改天赋和消除吃丹失败记录的NPC
//cracked by MIKE 2004.05.26
//last modified by MIKE 2004.06.19
#include <ansi.h>
#include <command.h>
inherit NPC;
string ask_zhongqiugift();
string ask_guoqinggift();

int do_addgift(string arg);
int ask_gift();
int do_add(string arg);
//int sub_gift();
//int do_subtract(string arg);
//int select_sp(string arg);

void create()
{
    set_name(HIC"小麦棵"NOR, ({"xiao maike" }));
        set("title", ""HIR"［"HIG"天神使者"HIW"］"NOR""HIY"天"HIM"赋"HIC"使"HIG"者"NOR"");   
    set("gender", "男性");
    set("age", 24);
    set("per", 70);
      set("str", 500000);
    set("int", 40);
    set("con", 40);
    set("dex", 40);
    set("qi",5000);
    set("jingli",5000);
    set("max_qi", 5000);
    set("max_jing", 5000);
    set("eff_jingli", 5000);
    set("jiali", 190);
    set("combat_exp", 5647645745754);
    set("shen", 25000);
   set("chat_chance", 10);
        set("chat_msg", ({
        "小麦棵幽幽唱道：“还记得年少时的梦吗\n",
        "小麦棵幽幽唱道：“像朵永远不调零的花\n",
        "小麦棵幽幽唱道：“陪我经过那风吹雨打\n",
        "小麦棵幽幽唱道：“看世事无常\n",
        "小麦棵幽幽唱道：“看沧桑变化\n",
        "小麦棵幽幽唱道：“那些为爱所付出的代价\n",
        "小麦棵幽幽唱道：“是永远都难忘的啊\n",
        "小麦棵幽幽唱道：“所有真心的痴心的话\n",
        "小麦棵幽幽唱道：“永在我心中虽然已没有他\n",
        "小麦棵幽幽唱道：“走吧走吧人总要学着自己长大\n",
        "小麦棵幽幽唱道：“走吧走吧人生难免经历苦痛挣扎\n",
        "小麦棵幽幽唱道：“走吧走吧为自己的心找一个家\n",
        "小麦棵幽幽唱道：“也曾伤心流泪\n",
        "小麦棵幽幽唱道：“也曾黯然心碎\n",
        "小麦棵幽幽唱道：“这是爱的代价\n",
        "小麦棵幽幽唱道：“也许我偶尔还是会想他\n",
        "小麦棵幽幽唱道：“偶尔难免会惦记着他\n",
        "小麦棵幽幽唱道：“就当他是个老朋友啊\n",
        "小麦棵幽幽唱道：“也让我心疼也让我牵挂\n",
        "小麦棵幽幽唱道：“只是我心中不再有火花\n",
        "小麦棵幽幽唱道：“让往事都随风去吧\n",
        "小麦棵幽幽唱道：“所有真心的痴心的话\n",
        "小麦棵幽幽唱道：“仍在我心中\n",
        "小麦棵幽幽唱道：“虽然已没有他\n",
        }));
        set("inquiry", ([
                "天赋": (: ask_gift :),        
                        "中秋快乐": (: ask_zhongqiugift :),
                        "国庆快乐": (: ask_guoqinggift :),

            //    "消除记录": (: sub_gift :),
                //      "special":(:select_sp:),
        ]));

    setup();
}
void init()
{object me;
::init();
        add_action("do_addgift","addgift");
        add_action("do_add", "add");
       // add_action("do_subtract", "subtract");
        if( interactive(me = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
}
void greeting(object ob)
{object me;
me=this_player();
 if (!ob || !present(ob, environment())) return;
            write(HBRED"请ask xiao maike about 天赋 来修改你的天赋吧！\n"NOR);
         //   write(HBRED"请ask xiao maike about 消除记录  来消除吃丹药失败记录吧！\n"NOR);
            return ;
}
/*
int accept_object(object me, object ob)
{
        
        if (ob->query("money_id") && ob->value() >= 1000000) //暂时钱定位为10 gold不排除会修改，请巫师酌情修改！
        {
                tell_object(me, HIW "请使用subtract 属性的英文ID（如输入：substract int）！。\n" NOR);
                me->set_temp("givemike",1);
                return 1;
        }

        switch (random(2))
        {
        case 0:
                command("say 钱的数目不够，既然你给我，我就收下了，谢谢嗷！");
                break;
        case 1:
                command("say 钱数目不够，既然给了，就没收了，哈哈！");
                break;
        }
                        if (! ob->is_character())
        {
                destruct(ob);
                return -1;
        }
        return 1;

        }
int sub_gift()
{
        object me;
        me=this_player();
        
                 command("tell " + me->query("id") +
                        " 你得先给钱呀，目前就收你100GOLD吧，不是很多吧！");
                return 1;
}
int do_subtract(string arg)
{               object me;
                me=this_player();
        if (!me->query_temp("givemike"))
        {
                command("say 你干什么，神经病 !");
                return 1;
        }

        if (! arg || ! stringp(arg))
        {
               command("shake " + me->query("id"));
               command("say 你得告诉我要消除哪个属性呀。" NOR);
                return 1;
        }     
        if (arg=="str")   
        {if(me->query("gift/str/fail")==0){
                command("tell " + me->query("id") +
                        " 你的膂力失败记录已经为零，还消个鸟呀，钱没收了\n");       
                me->set_temp("givemike",0);
                return 1;
                }
        me->add("gift/str/fail", -1);
command("tell " + me->query("id") +
                        " 你的膂力失败记录消除了一点\n");       
                me->set_temp("givemike",0);
                         return 1;}
         if (arg=="int")   
        {if(me->query("gift/int/fail")==0){
                command("tell " + me->query("id") +
                        " 你的悟性失败记录已经为零，还消个鸟呀，钱没收了\n");       
                me->set_temp("givemike",0);
                return 1;
                }
         me->add("gift/int/fail", -1);
command("tell " + me->query("id") +
                        " 你的悟性失败记录消除了一点\n");       
                me->set_temp("givemike",0);
                         return 1;}
if (arg=="con")   
        {if(me->query("gift/con/fail")==0){
                command("tell " + me->query("id") +
                        " 你的根骨失败记录已经为零，还消个鸟呀，钱没收了\n");       
                me->set_temp("givemike",0);
                return 1;
                }
me->add("gift/con/fail", -1);
command("tell " + me->query("id") +
                        " 你的根骨失败记录消除了一点\n");       
                        me->set_temp("givemike",0);
                         return 1;}
if (arg=="dex")   
        { if(me->query("gift/dex/fail")==0){
                command("tell " + me->query("id") +
                        " 你的身法失败记录已经为零，还消个鸟呀，钱没收了\n");       
                me->set_temp("givemike",0);
                return 1;
                }
me->add("gift/dex/fail", -1);

command("tell " + me->query("id") +
                        " 你的身法失败记录消除了一点\n");       
                        me->set_temp("givemike",0);
                         return 1;}

       return 1;
        }
        */
int ask_gift()
{
        object me;
        me=this_player();            
                 if (me->query("rmb")<2)
      {    command("tell " + me->query("id") +
                        " 你都修改过了，还来问，兽！！\n");   
      return 1;}  

        if (me->query("rmb")==20)
                me->add("rmb",-4);
        if (me->query("combat_exp") >= 0)
                        {command("tell " + me->query("id") +
                        " 你可以修改天赋了,格式为add str就可以每次加一点；各种属性英文ID如下，\n"
                          "膂力：【 " HIG "str" HIY " 】 "
                          "悟性：【 " HIG "int" HIY " 】 "
                          "根骨：【 " HIG "con" HIY " 】 "
                          "身法：【 " HIG "dex" HIY " 】\n");
                me->set_temp("modified", 1);
                return 1;
         }
                 command("tell " + me->query("id") +
                        " 你的经验不够呀，赶紧练吧！");
                return 1;
}
int do_add(string arg)
{               int x=0;

                object me;
                me=this_player();
                x=(me->query("rmb"));
      if (x<2)
      {    command("tell " + me->query("id") +
                        " 你可以使用的存款已经不够了\n");   
      return 1;}    



        if (!me->query_temp("modified"))
        {
                command("say 你说什么？");
                return 1;
        }

        if (! arg || ! stringp(arg))
        {
               command("shake " + me->query("id"));
               command("say 你得告诉我要加哪个属性呀。" NOR);
                return 1;
        }     
        if (arg=="str")   
        {me->add("str", 1);
command("tell " + me->query("id") +
                        " 你的膂力增加了一点\n");       
                        me->add("rmb", -2);
                         return 1;}
         if (arg=="int")   
        {me->add("int", 1);
command("tell " + me->query("id") +
                        " 你的悟性增加了一点\n");       
                        me->add("rmb", -2);
                         return 1;}
if (arg=="con")   
        {me->add("con", 1);
command("tell " + me->query("id") +
                        " 你的根骨增加了一点\n");       
                        me->add("rmb", -2);
                         return 1;}
if (arg=="dex")   
        {me->add("dex", 1);
command("tell " + me->query("id") +
                        " 你的身法增加了一点\n");       
                        me->add("rmb", -2);
                         return 1;}

       return 1;
        }


int accept_kill()
{
        command("say 呀！你想干什么？");
        return 1;
}

void unconcious()
{
        die();
}

void die()
{
        command("chat 不好了！出人命了！");
        message_vision("$N飞也似的逃走了。\n", this_object());
        destruct(this_object());
}
string ask_zhongqiugift()
{
        object me;
        object gift;
    me=this_player();
//               if (me->query("/txwd/gift/zhongqiu2004"))
//      {    command("tell " + me->query("id") +
 //                       " 中秋快乐！\n");   
 //     return 1;}  
              // 已经领取过礼物
        if (me->query("/txwd/gift/zhongqiu2004"))
                 return HIR "“中秋快乐！”\n" NOR;
        
        // 已经吃过礼物
        if (me->query("/txwd/gift/zhongqiu2004_eated"))
                 return HIR"“中秋快乐！”\n" NOR;

                        command("tell " + me->query("id") +
                        " 感谢您对“天下无敌”的支持，谢谢！\n");
        // 给予礼物
        message_vision(HIY "小麦棵笑嘻嘻地对$N说道：“中秋快乐！”\n" NOR, me);
        command("smile");
        command("say 恩，我给你一块月饼吃吧！");
        message_vision(HIY "小麦棵将月饼给了$N" HIY "\n", me);        
        tell_object(me, HIG "你得到了一块月饼。\n");
                                gift=new("/clone/gift/yuebing");
                                gift->move(me);
                me->set("/txwd/gift/zhongqiu2004", 1);
                return "再次感谢您的支持。";
}
string ask_guoqinggift()
{
        object me;
        object gift;
    me=this_player();
              // 已经问过了
        if (me->query("/txwd/gift/guoqing2004"))
                 return HIR "“国庆节快乐！”\n" NOR;
        

        // 给予礼物
        message_vision(HIY "小麦棵笑嘻嘻地对$N说道：“国庆节快乐！”\n" NOR, me);
        command("smile");
        command("say 恩，我给你4点属性吧！");
        command("tell " + me->query("id") +
                        " 你可以修改天赋了,格式为addgift str就可以每次加一点；各种属性英文ID如下，\n"
                          "膂力：【 " HIG "str" HIY " 】 "
                          "悟性：【 " HIG "int" HIY " 】 "
                          "根骨：【 " HIG "con" HIY " 】 "
                          "身法：【 " HIG "dex" HIY " 】\n");

                me->set("/txwd/gift/guoqing2004", 1);
                me->set_temp("guoqing",1);
                me->set("guoqingnumber",4);
                return "再次感谢您的支持。";
}
int do_addgift(string arg)
{
                object me;
                me=this_player();
      if (me->query("guoqingnumber")<=0)
      {    command("tell " + me->query("id") +
                        " 你可以使用的国庆点数已经不够了\n");   
      return 1;}    



        if (!me->query_temp("guoqing"))
        {
                command("say 你要干什么？");
                return 1;
        }

        if (! arg || ! stringp(arg))
        {
               command("shake " + me->query("id"));
               command("say 你得告诉我要加哪个属性呀。" NOR);
                return 1;
        }     
        if (arg=="str")   
        {me->add("str", 1);
command("tell " + me->query("id") +
                        " 你的膂力增加了一点\n");       
                        me->add("guoqingnumber", -1);
                         return 1;}
         if (arg=="int")   
        {me->add("int", 1);
command("tell " + me->query("id") +
                        " 你的悟性增加了一点\n");       
                        me->add("guoqingnumber", -1);
                         return 1;}
if (arg=="con")   
        {me->add("con", 1);
command("tell " + me->query("id") +
                        " 你的根骨增加了一点\n");       
                        me->add("guoqingnumber", -1);
                         return 1;}
if (arg=="dex")   
        {me->add("dex", 1);
command("tell " + me->query("id") +
                        " 你的身法增加了一点\n");       
                        me->add("guoqingnumber", -1);
                         return 1;}

       return 1;
        }

