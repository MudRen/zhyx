// 拍卖师

#include <ansi.h>

inherit NPC;
inherit F_SAVE;

#define WIZLEVEL 4 // 能够启动和执行拍卖的巫师等级
#define DISTANCE 5 // 拍卖中间隔的时间（秒数）

string query_save_file();
int do_start(string arg);
int do_paimai(string arg);
int begin_paimai();
int stop_paimai();
int do_jupai(object buyer,string arg);
int go_jupai();
int do_qiao(object me);
int do_paimailist(object me);
int do_unwelcome(string arg);
int finish_paimai(object me);
void heart_beat();
object check_operator();
int do_autopaimai(object me);

int last_time;		//最后一次手工操作的时间
object operator;

void create()
{
        seteuid(getuid());
        restore();

        set_name("富甲天下", ({ "fujia tianxia", "fujia", "tianxia" }) );
        set("nickname", HIY+BLINK "天下第一富" NOR);
        set("channel_id","富甲天下");
        set("gender", "男性");
        set("age", 45);
        set("no_get", 1);
        set("long",
                "这是一位微胖魁梧的中年人，据传绝地末日的所有商业背后都有他的黑手操纵。\n");
        set("combat_exp",600000);
        set("shen", 0);
        set("attitude", "friendly");

        set("apply/attack", 100);
        set("apply/defense", 100);

        set("max_qi", 800);
        set("qi", 800);
        set("max_jing", 800);
        set("jing", 800);
        set("max_jingli", 800);
        set("jingli",800);
        set("max_neili", 8000);
        set("neili",8000);
        
        set_skill("force", 300);
        set_skill("unarmed", 300);
        set_skill("sword",300);
        set_skill("parry",300);
        set_skill("dodge", 300);

        setup();

        carry_object("/clone/cloth/cloth")->wear();
}


void init()
{
        ::init();
        if (wiz_level(this_player()) >= WIZLEVEL)
        {
                add_action("do_paimai", "paimai");
                add_action("do_start","start");
                add_action("do_qiao","qiao");
                add_action("do_unwelcome","unwelcome");
                add_action("finish_paimai","finish");
                add_action("do_autopaimai","autopaimai");
        }

        add_action("do_paimailist", "paimailist");
        add_action("do_jupai", "jupai");
}

// 存盘文档
string query_save_file()
{
        return "/data/npc/fujiatianxia";
}

int do_start(string arg)
{
        object ob,me;
        int i;
        string *heidian_list,msg;
        mapping *all_heidian;
        mapping begin_heidian;
        mapping end_heidian;

        me = this_player();
        ob = this_object();

        if (ob->query("paimai_start") && !ob->query("paimai_end"))
                return notify_fail("现在正在拍卖中，无法重新开始。\n");

        if (!HEIDIAN_D->is_chushihua())
        {
                msg = "黑店尚未全部初始化，在进行拍卖之前，请首先进行所有黑店的初始化！\n";
                msg += "初始化黑店的指令：cshshop [黑店ID]，如果不使用参数，表示初始化所有黑店。\n";
                write(msg);
                return 1;
        } else
        {
                heidian_list = ({});
                begin_heidian = ([]);
                end_heidian = ([]);
                all_heidian = HEIDIAN_D->query_heidian();
                msg = HIC "成功初始化拍卖程序，待拍卖黑店列表： \n" NOR;
                msg += HIC "--------------------------------------\n" NOR;
                for (i = 0;i < sizeof(all_heidian);i++)
                {
                        heidian_list += ({ all_heidian[i]["id"] });
                        begin_heidian[all_heidian[i]["id"]] = all_heidian[i]["price"];
                        msg += sprintf(HIY "%s" HIW "\t%s\n" NOR,all_heidian[i]["id"],all_heidian[i]["price"]);
                }
                msg += HIC "--------------------------------------\n" NOR;
                msg += HIC "总共" + HIW + chinese_number(sizeof(all_heidian)) + HIC + "家黑店。\n";

                ob->delete("owner");
                ob->delete("heidian_list");
                ob->delete("begin_heidian");
                ob->delete("end_heidian");
                ob->delete("paimai_end");
                ob->delete("now_paimai");
                ob->delete("temp_owner");
                ob->delete("wait_jupai");
                ob->delete("on_jupai");
                ob->delete("can_finish");

                ob->set("paimai_start",1);
                ob->set("heidian_list",heidian_list);
                ob->set("begin_heidian",begin_heidian);
                ob->set("end_heidian",end_heidian);

                if (arg) {
                        CHANNEL_D->do_channel( ob, "sys", "黑店拍卖系统由" + me->name(1) + "成功启动，运行模式：自动。");
                        ob->set("operator","fujia tianxia");		//拍卖设置为自动运行
                        msg += HIR "您选择了通过自动运行的方式来启动拍卖进程。\n";
                        write(msg);
                        message_vision("$N乐呵呵的对大家说：“这次拍卖由我来主持，现在我们就开始吧！”\n",ob);
                        operator = ob;
                        ob->save();
                        call_out("do_paimai",0,"automatic");
                } else
                {
                        CHANNEL_D->do_channel( ob, "sys", "黑店拍卖系统由" + me->name(1) + "成功启动，运行模式：手工。");
                        ob->set("operator",me->query("id"));		//拍卖设置为手工运行
                        msg += HIR "您选择了通过手工方式操作拍卖进程，现在可以开始了。\n" NOR;
                        msg += HIR "拍卖指令：" + HIW + "paimai <黑店ID>" + HIR + "。\n" NOR;
                        msg += HIR "您可以使用：" + HIW + "autopaimai" + HIR + " 指令来将拍卖进程转成自动运行。\n" NOR;
                        write(msg);
                        message_vision("$N乐呵呵的对大家说：“这次拍卖由$n亲自主持！”\n",ob,me);
                        message_vision("$N将手中的锤子郑重的交给$n，然后退到一边。\n",ob,me);
                        operator = me;
                        last_time = time();		//记录该次操作时间
                        ob->set_heart_beat(1);		//启动手工拍卖守护进程
                        ob->save();
                }
        }
        return 1;
}

int do_paimai(string arg)
{
        object ob;
        string *heidian_list,now_heidian,msg,*heidian_key;
        mapping begin_heidian;
        int i;

        if (!query("paimai_start") || query("paimai_end"))
                return notify_fail("现在并没有在进行拍卖！\n");

        if (!arg)
                return notify_fail("指令格式：paimai <黑店ID>");

        if (query("now_paimai"))
                return notify_fail("现在正在进行" + query("now_paimai") + "黑店的拍卖，您别着急。\n");

        ob = this_object();
        heidian_list = query("heidian_list");
        begin_heidian = query("begin_heidian");

        if (ob != operator)		//非自动的
        {
                if (this_player() != operator)
                        return notify_fail("对不起，现在拍卖正在由" + operator->name(1) + "主持进行中。\n");

                if (sizeof(heidian_list) < 1)		//已经全部拍卖完毕了
                {
                        set("can_finish",1);
                        save();
                        return notify_fail("所有黑店都已经拍卖结束了，您现在应该结束(finish)拍卖了。\n");
                }

                if (!begin_heidian[arg])		//提交的参数错误，重新显示所有待拍卖黑店列表
                {
                        msg = HIR "对不起，您所提交的" + HIW + arg + HIR + "黑店并不存在。\n" NOR;
                        msg += HIC "待拍卖黑店列表： \n" NOR;
                        msg += HIC "--------------------------------------\n" NOR;
                        heidian_key = keys(begin_heidian);
                        for (i = 0;i < sizeof(heidian_key);i++)
                                msg += sprintf(HIY "%s" HIW "\t%s\n" NOR,heidian_key[i],begin_heidian[heidian_key[i]]);
                        msg += HIC "--------------------------------------\n" NOR;
                        msg += HIC "总共" + HIW + chinese_number(sizeof(heidian_key)) + HIC + "家黑店。\n";
                        msg += HIR "拍卖指令：" + HIW + "paimai <黑店ID>" + HIR + "。\n" NOR;
                        msg += HIR "您可以使用：" + HIW + "autopaimai" + HIR + " 指令来将拍卖进程转成自动运行。\n" NOR;
                        write(msg);
                        return 1;
                }
                now_heidian = arg;		//当前拍卖黑店
        } else	//自动拍卖
        {
                if (sizeof(heidian_list) < 1)	//全部黑店都已经拍卖完毕
                {
                        ob->set("can_finish",1);
                        ob->save();
                        call_out("finish_paimai",0);		//调用结束拍卖程序
                        return 1;
                }
                now_heidian = heidian_list[random(sizeof(heidian_list))];		//当前拍卖黑店
        }

        heidian_list -= ({ now_heidian });	//从待拍黑店中删除当前拍卖黑店
        ob->set("wait_jupai",1);
        ob->set("heidian_list",heidian_list);
        ob->delete("begin_heidian/" + now_heidian);
        ob->set("now_heidian",now_heidian);
        ob->set("now_price",(int)begin_heidian[now_heidian]);
        ob->save();

        CHANNEL_D->do_channel( ob, "sys", "现在开始拍卖" + now_heidian + "黑店。");
        message_vision("$N大声宣布：“现在拍卖" + HIW + now_heidian + NOR + "黑店！底价：" + HIW + begin_heidian[now_heidian] + NOR + "两黄金第一次！”\n",operator);
        message_vision("$N严肃的说：“现在请有意者举牌(" + HIW + "jupai" + NOR + "）！”\n",operator);

        if (ob == operator)			//自动拍卖
                call_out("begin_paimai",DISTANCE);
        else
                last_time = time();	//记录该次操作的时间

        return 1;
}

int begin_paimai()
{
        string now_heidian;
        int now_price,m;
        object operator,ob;

        ob = this_object();

        m = ob->query("wait_jupai");

        if (!m) return 1;		//已经有人开始举牌

        now_heidian = query("now_heidian");
        now_price = query("now_price");

        m +=1;
        ob->set("wait_jupai",m);

        if (operator != ob)		//手工拍卖，检查执行的巫师是否还在，如果不在了，则拍卖进程转自动
                operator = check_operator();
                
        message_vision("$N大声宣布：“拍卖" + HIW + now_heidian + NOR + "黑店！底价：" + HIW + now_price + NOR + "两黄金第" + chinese_number(m) + "次！”\n",operator);
        message_vision("$N严肃的说：“现在请有意者举牌(" + HIW + "jupai" + NOR + "）！”\n",operator);

        if (operator == ob)		//自动拍卖
        {
                if (!(m==3))
                        call_out("begin_paimai",DISTANCE);
                else
                        call_out("stop_paimai",DISTANCE);
        } else			//手工拍卖 
                last_time = time();	//记录最后一次操作的时间     
}

int stop_paimai()
{
        string now_heidian,temp_owner,*owner,*heidian_list,msg,*heidian_key;
        mapping begin_heidian,end_heidian;
        object ob,the_owner;
        int i,now_price;

        ob = this_object();
        owner = query("owner");
        temp_owner = query("temp_owner");
        heidian_list = query("heidian_list");
        begin_heidian = query("begin_heidian");
        end_heidian = query("end_heidian");
        now_heidian = query("now_heidian");
        now_price = query("now_price");

        if (!mapp(end_heidian) || sizeof(end_heidian) < 1) end_heidian = ([]);

        if (operator != ob)		//手工拍卖，检查执行的巫师是否还在，如果不在了，则拍卖进程转自动
                operator = check_operator();

        if (query("wait_jupai"))
        {
                message_vision("$N举起手中的小木棰用力的一敲，只听得“当～～”一声巨响。\n",operator);
                message_vision("$N大声宣布：“" + HIW + now_heidian + NOR + "黑店的所有权拍卖流标了。\n",operator);
                end_heidian[now_heidian] = 0;
                ob->delete("wait_jupai");
                ob->delete("now_heidian");
                ob->set("end_heidian",end_heidian);
                ob->save();
                if (operator == ob)	//自动拍卖
                {
                        if (sizeof(heidian_list) < 1)		//所有黑店拍卖结束
                        {
                                set("can_finish",1);
                                save();
                                call_out("finish_paimai",0);
                                return 1;
                        }
                        call_out("do_paimai",1,"automatic");
                }
                else
                {
                        if (sizeof(heidian_list) < 1)		//所有黑店拍卖结束
                        {
                                set("can_finish",1);
                                save();
                                tell_object(operator,"所有黑店都已经拍卖结束了，您现在应该结束(finish)拍卖了。\n");
                                return 1;
                        }
                        msg += HIC "待拍卖黑店列表： \n" NOR;
                        msg += HIC "--------------------------------------\n" NOR;
                        heidian_key = keys(begin_heidian);
                        for (i = 0;i < sizeof(heidian_key);i++)
                                msg += sprintf(HIY "%s" HIW "\t%s\n" NOR,heidian_key[i],begin_heidian[heidian_key[i]]);
                        msg += HIC "--------------------------------------\n" NOR;
                        msg += HIC "总共" + HIW + chinese_number(sizeof(heidian_key)) + HIC + "家黑店。\n";
                        msg += HIR "拍卖指令：" + HIW + "paimai <黑店ID>" + HIR + "。\n" NOR;
                        msg += HIR "您可以使用：" + HIW + "autopaimai" + HIR + " 指令来将拍卖进程转成自动运行。\n" NOR;
                        tell_object(operator,msg);
                        last_time = time();	//记录该次操作时间
                }
                return 1;
        }
        else            
        {
                //首先检查当前竞投黑店的玩家是否在线，或者是否在投标后赶回钱庄取走了存款
                //如果该玩家数据异常，则该黑店重新归入待拍黑店数组，并且取消该玩家的拍卖资格

                the_owner = find_player(temp_owner);
                if (!objectp(the_owner) || the_owner->query("balance") < now_price * 10000)
                {
                        do_unwelcome(temp_owner + " 1");		//取消该玩家的拍卖资格
                        begin_heidian[now_heidian] = 2000;
                        ob->set("begin_heidian",begin_heidian);

                        message_vision("$N大声宣布：“由于" + temp_owner + "数据异常，取消该玩家的拍卖资格！" + HIW + now_heidian + NOR + "黑店重新归入待拍卖列表！”\n",operator);
                        CHANNEL_D->do_channel( ob, "sys", "由于" + temp_owner + "数据异常，取消该玩家的拍卖资格！" + now_heidian + "黑店重新归入待拍卖列表！");
                } else
                {
                        the_owner->add("balance",-now_price);
                        the_owner->save();
                        owner += ({ temp_owner });
                        ob->set("owner",owner);
                        end_heidian[now_heidian] = now_price;
                        ob->set("end_heidian",end_heidian);
                        HEIDIAN_D->setowner(operator,now_heidian,temp_owner);
                        message_vision("$N举起手中的小木棰用力的一敲，只听得“当～～”一声巨响。\n",operator);
                        message_vision("$N大声宣布：“成交！" + temp_owner + "获得了" + HIW + now_heidian + NOR + "黑店的所有权！最终出价：" + HIW + now_price + NOR + "两黄金！”\n",operator);
                        CHANNEL_D->do_channel( ob, "sys", "成交！" + temp_owner + "获得了" + now_heidian + "黑店的所有权！最终出价：" + now_price + "两黄金！");
                        tell_object(the_owner,HIR "恭喜恭喜！您以" + now_price + "两黄金的价格最终获得" + now_heidian + "黑店的所有权！\n" NOR);
                }        
                ob->delete("on_jupai");
                ob->delete("now_heidian");
                ob->delete("now_price");
                ob->delete("temp_owner");
                ob->save();

                if (operator == ob)		//自动拍卖
                {
                        if (sizeof(heidian_list) < 1)		//所有黑店拍卖结束
                        {
                                set("can_finish",1);
                                save();    
                                call_out("finish_paimai",0);
                                return 1;
                        }
                        call_out("do_paimai",1,"automatic");
                } else
                        if (sizeof(heidian_list) < 1)		//所有黑店拍卖结束
                        {
                                set("can_finish",1);
                                save();
                                tell_object(operator,"所有黑店都已经拍卖结束了，您现在应该结束(finish)拍卖了。\n");
                                return 1;
                        }
                        msg += HIC "待拍卖黑店列表： \n" NOR;
                        msg += HIC "--------------------------------------\n" NOR;
                        heidian_key = keys(begin_heidian);
                        for (i = 0;i < sizeof(heidian_key);i++)
                                msg += sprintf(HIY "%s" HIW "\t%s\n" NOR,heidian_key[i],begin_heidian[heidian_key[i]]);
                        msg += HIC "--------------------------------------\n" NOR;
                        msg += HIC "总共" + HIW + chinese_number(sizeof(heidian_key)) + HIC + "家黑店。\n" NOR;
                        msg += HIR "拍卖指令：" + HIW + "paimai <黑店ID>" + HIR + "。\n" NOR;
                        msg += HIR "您可以使用：" + HIW + "autopaimai" + HIR + " 指令来将拍卖进程转成自动运行。\n" NOR;
                        tell_object(operator,msg);
                        last_time = time();	//记录该次操作时间
                }
                return 1;
        }
}

int do_jupai(object buyer,string arg)
{
        object ob;
        string now_heidian,temp_owner;
        int money,now_price;

        ob = this_object();
        if(!query("paimai_start"))
                return notify_fail("现在拍卖还没有开始，你急个啥，不规矩点，小心取消给取消拍卖资格！\n");

        if (operator != ob)		//手工拍卖，检查执行的巫师是否还在，如果不在了，则拍卖进程转自动
                operator = check_operator();

        if(!query("now_heidian"))
                return notify_fail(operator->name(1) + "还没有宣布要拍卖哪家黑店，你急个啥？\n");

        if(member(buyer->query("id"),query("owner")))
                return notify_fail("你已经是拍到了你所要的黑店，心不要那么黑，把下面的机会留给别人吧！\n");

        if(member(buyer->query("id"),query("unwelcom")))
                return notify_fail("你已经给取消了拍卖资格，老老实实一边呆着吧。\n");

        if(buyer->query("id") == query("temp_owner"))
                return notify_fail("当前的价格本来就是你所竞投的啊，头昏了？\n");

        remove_call_out("begin_paimai");
        remove_call_out("go_jupai");
        now_heidian = query("now_heidian");
        now_price = query("now_price");
        temp_owner = buyer->query("id");

        if (!arg)
                money = 100;
        else
                if (!(sscanf(arg,"%d",money) == 1) || money < 100)
                        return notify_fail("指令格式：jupai [num]，num是所加的黄金，至少是100，如果不指定num，则表示加价100两黄金。\n");

        if (buyer->query("balance") < (money + now_price)*10000)
                return notify_fail("你帐户里的钱并不足" + (money+now_price) + "两黄金了。\n");

        now_price += money;
        
        ob->set("temp_owner",temp_owner);
        ob->set("on_jupai",1);
        ob->set("now_price",now_price);
        ob->delete("wait_jupai");
        ob->save();

        tell_object(buyer,"你举了举手中的牌子，示意加价" + chinese_number(money) + "两黄金。\n");
        message_vision("$N大声宣布：“" + temp_owner + "出价" + HIW + now_price + NOR + "两黄金购入" + HIW + now_heidian + NOR + "黑店第一次！”\n",operator);

        if (operator == ob)		//自动拍卖
                call_out("go_jupai",DISTANCE);
        else
                last_time = time();	//记录当前操作时间

        return 1;
}

int go_jupai()
{
        object ob;
        int m,now_price;
        string now_heidian,temp_owner;
        
        ob = this_object();
        m = query("on_jupai");
        now_heidian = query("now_heidian");
        now_price = query("now_price");
        temp_owner = query("temp_owner");

        m+=1;
        ob->set("on_jupai",m);
        ob->save();

        if (operator != ob)		//手工拍卖，检查执行的巫师是否还在，如果不在了，则拍卖进程转自动
                operator = check_operator();

        message_vision("$N大声宣布：“" + temp_owner + "出价" + HIW + now_price + NOR + "两黄金购入" + HIW + now_heidian + NOR + "黑店第" + chinese_number(m) + "次！”\n",operator);

        if (operator == ob)		//自动拍卖
        {
                if (!(m==3))
                        call_out("go_jupai",DISTANCE);
                else
                        call_out("stop_paimai",DISTANCE);
        } else			//手工拍卖 
                last_time = time();	//记录最后一次操作的时间     

        return 1;
}

int do_qiao(object me)
{
        object ob;
        int m;
        ob = this_object;

        if (!query("paimai_start"))
                return notify_fail("现在拍卖进程还没有启动，您可以使用start指令来启动拍卖进程。\n");

        if (operator != ob)		//手工拍卖，检查执行的巫师是否还在，如果不在了，则拍卖进程转自动
                operator = check_operator();

        if (operator != me)
                return notify_fail("现在拍卖进程正由" + operator->name(1) + "主持中，您不需要干什么，喝杯水，抽支烟，休息休息。\n");

        //已经宣布所拍黑店，等待举牌中
        if (m = query("wait_jupai"))
        {
                if (!(m == 3))
                        call_out("begin_paimai",0);
                else
                        call_out("stop_paimai",0);
        } else if (m = query("on_jupai"))
        {
                if (!(m == 3))
                        call_out("go_jupai",0);
                else
                        call_out("stop_paimai",0);
        } else return notify_fail("您还宣布接下来拍卖哪个黑店。\n");
        return 1;
}

int do_paimailist(object me)
{
        int i;
        string msg,now_paimai,*heidian_list,*heidian_key;
        mapping begin_heidian,end_heidian;

        msg = "";
        now_paimai = query("now_paimai");
        begin_heidian = query("begin_heidian");
        end_heidian = query("end_heidian");

        if (query("paimai_start"))
                msg += HIC "现在正在拍卖之中。\n" NOR;
        else
                msg += HIC "现在并没有在拍卖黑店。\n" NOR;

        msg += HIC "--------------------------------------\n" NOR;

        if (now_paimai)
        {
                msg += sprintf(HIY"当前拍卖黑店："HIW"%s\t"NOR HIR"%s\n"NOR, now_heidian, now_price);
                msg += HIC "--------------------------------------\n" NOR;
        }

        is (mapp(begin_heidian) && sizeof(begin_heidian) > 0)
        {
                msg += HIY "待拍卖黑店列表： \n" NOR;
                heidian_key = keys(begin_heidian);
                for (i = 0;i < sizeof(heidian_key);i++)
                        msg += sprintf(HIW "%s" HIR "\t%s\n" NOR,heidian_key[i],begin_heidian[heidian_key[i]]);
                msg += HIC "--------------------------------------\n" NOR;
        }

        is (mapp(end_heidian) && sizeof(end_heidian) > 0)
        {
                msg += HIY "已被拍卖黑店列表： \n" NOR;
                heidian_key = keys(end_heidian);
                for (i = 0;i < sizeof(heidian_key);i++)
                        msg += sprintf(HIW "%s" HIR "\t%s\n" NOR,heidian_key[i],end_heidian[heidian_key[i]]);
                msg += HIC "--------------------------------------\n" NOR;
        }

        tell_object(me,msg);
        return 1;
}

int do_unwelcome(string arg)
{
        int i,m;
        string *unwelcome;
        unwelcome = query("unwelcome");
        if (!unwelcome || sizeof(unwelcome) < 1) unwelcome = ({});
        if (!arg)
        {
                if (sizeof(unwelcome) < 1)
                        return notify_fail("现在没有玩家给取消拍卖资格。\n");

                msg = HIC "给取消拍卖资格的玩家列表：\n"NOR;
                msg += HIC"------------------------------------\n"NOR;
                for (i = 0;i < sizeof(unwelcome);i++)
                        msg += HIY unwelcome[i] + "\n"NOR;
                msg += HIC"------------------------------------\n"NOR;
                msg += HIC"总共" + sizeof(unwelcome) + "位玩家给取消拍卖资格。\n"NOR;
                tell_object(me,msg);
                return 1;
        }

        if (sscanf(arg,"%s %d",arg,m) != 2) m = 1;

        if (m)
        {
                if (member(arg,unwelcome) == -1)
                {
                        unwelcome += ({ arg });
                        set("unwelcome",unwelcome);
                }
        }
        else
        {
                if (member(arg,unwelcome) != -1)
                {
                        unwelcome -= ({ arg });
                        set("unwelcome",unwelcome);
                }
        }
        save();
        return 1;
}

int finish_paimai(object me)
{
        if (!query("paimai_start"))
                return notify_fail("拍卖进程并没有启动，自动化个啥哦？\n");

        if (!query("can_finish"))
                return notify_fail("现在拍卖正在进行之中，无法中止。\n");

        if (operator != me)
                return notify_fail("现在是" + operator->name(1) + "主持黑店拍卖，您就别操心了。\n");

        ob->delete("can_finish");
        ob->delete("heidian_list");
        ob->delete("begin_heidian");
        ob->delete("heidian_start");
        ob->set("heidian_end",1);
        ob->delete("wait_jupai");
        ob->delete("on_jupai");
        ob->delete("now_heidian");
        ob->delete("now_price");
        ob->delete("temp_owner");
        ob->delete("owner");
        ob->save();
        message_vision("$N大声宣布：“本次黑店拍卖圆满结束！”\n",operator);

        if (operator == ob)
        {
                HEIDIAN_D->open_all(operator);
                message_vision("$N大声宣布：“所拍黑店现在已经全部开放！”\n",operator);
        } else tell_object(operator,"您现在可以用openshop指令开放黑店。\n");
        return 1;
}

//心跳线--用于检查启动拍卖进程的巫师是否状态正常
//如果状态不正常，则转为自动运行模式，并且关闭心跳线
void heart_beat()
{
        int m;
        object obj;
        string the_operator;

        if (!query("paimai_start") || operator == this_object())
        {
                set_heart_beat(0);
                return;
        }

        the_operator = query("operator");
        if (!the_operator)
        {
                set_heart_beat(0);
                return;
        }

        if (!(obj = find_player(the_operator)) || !living(obj) || environment(obj) != environment() || time() - last_time > 10)
        {
                operator = this_object();
                set_heart_beat(0);
                command("say 看来" + the_operator + "有点别的事情要忙，接下来的拍卖就由我来主持！");
                CHANNEL_D->do_channel( ob, "sys", "由于" + the_operator + "状态异常，现在拍卖进程转入自动模式！");
                set("operator","fujia tianxia");
                save();
                if (m = query("wait_jupai"))
                {
                        if (!(m == 3))
                               call_out("begin_paimai",DISTANCE);
                        else
                               call_out("stop_paimai",DISTANCE);
                } else if (m = query("on_jupai"))
                {
                        if (!(m == 3))
                                call_out("go_jupai",DISTANCE);
                        else
                                call_out("stop_paimai",DISTANCE);
                } else call_out("do_paimai",0,"automatic");
        }
        return;
}

object check_operator()
{
        object obj;
        string the_operator;

        the_operator = query("operator");

        if (!(obj = find_player(the_operator)) || !living(obj) || environment(obj) != environment() || time() - last_time > 10)
        {
                set("operator","fujia tianxia");
                save();
                return this_object();
        }
        return obj;
}

int do_autopaimai(object me)
{
        if (!query("paimai_start"))
                return notify_fail("拍卖进程并没有启动，自动化个啥哦？\n");

        if (operator != me)
                return notify_fail("现在拍卖又不是你老人家在主持，不用那么操心吧。\n");

        operator = this_object();
        set_heart_beat(0);
        command("say 看来" + me->name(1) + "有点别的事情要忙，接下来的拍卖就由我来主持！");
        CHANNEL_D->do_channel( ob, "sys", me->query("id") + "将拍卖进程转入自动模式！");
        set("operator","fujia tianxia");
        save();
        if (m = query("wait_jupai"))
        {
                if (!(m == 3))
                        call_out("begin_paimai",DISTANCE);
                else
                        call_out("stop_paimai",DISTANCE);
        } else if (m = query("on_jupai"))
        {
                if (!(m == 3))
                        call_out("go_jupai",DISTANCE);
                else
                        call_out("stop_paimai",DISTANCE);
        } else call_out("do_paimai",0,"automatic");
        return 1;
}