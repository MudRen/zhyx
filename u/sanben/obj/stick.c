//名称:魔法杖---瞎三笨专用魔法道具   作者:瞎三笨
//制做目的:1.进一步熟悉lpc   2.给自己增加功能方便测试
//持有此物品可以增加call 、clone、summon、smash及dest等功能
//本物品为唯一性质物品，仅限瞎三笨本人使用

#include <ansi.h>
#include <weapon.h>

inherit XSWORD;
int is_weapon() {return 1;}

void create()
{
        set_name(HIG "瞎三笨专用魔法杖" NOR, ({ "magic stick", "stick"}));
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIG "魔法杖---瞎三笨专用魔法道具！\n" +
                                     "   一杖在手，万事不愁！\n" + 
                                     HIB"主要指令:\n" + "bian(变)、shuju(永久数据)、" +
                                        "jineng（技能)、linshi(临时数据)、shezhi(设置等级)、\n" +
                                     "bring(抓来活物)、bianmei(变没)、sha(杀)、qsha(全杀)、ding(定身法)\n"NOR);
                set("unit", "根");
                set("value", 10000);
                set("weight", 3000);
                set("material", "tian jing");
                set("owner_id","sanben");
                set("no_get",1);
                set("no_beg",1);
                set("no_steal",1);                           
             }
         init_xsword(9000);       
        setup();
}

void init()
        {       
                


                if (environment(this_object())->query("id") != "sanben")
                {    
                     message("vision", HIY + "魔法杖忽然搜的一声飞走了，"
                        "大概是去寻找他的主人去了吧。\n" NOR,
                            environment(this_object()));

                     if (! find_player("sanben")) 
                     {                        
                            destruct(this_object());
                     }
                    else
                     { 
                            this_object()->move(find_player("sanben"));
                            tell_object(find_player("sanben"), 
                                HIC"魔法杖忽然飞到了你手里。\n"NOR);
                     }
                }
                add_action("do_bian","bian");
                add_action("do_shuju","shuju");
                add_action("do_jineng","jineng");
                add_action("do_linshi","linshi");
                add_action("do_shezhi","shezhi");
                add_action("do_bring","bring");
                add_action("do_bianmei","bianmei");
                add_action("do_sha","sha");
                add_action("do_qsha","qsha");
                add_action("do_ding","ding");
        }

// clone物件   指令bian
int do_bian(string arg)

        {       
                object mm;
                
                if (this_player()->query("id") != "sanben")
                return notify_fail("这根魔法杖只听主人瞎三笨使唤！\n");
                
                mm=new(arg);
                if (! clonep(mm)) 
                {write("可是这玩艺儿好像变不出来呀！\n");return 1;}
                else
                {
                mm->move(this_player());
                message_vision(HIW"$N默念咒语，拿起魔法杖凌空一指，接着轻唤一声“变”！\n顿时将"NOR + 
                                mm->query("name") + HIW"变了出来。\n"NOR, this_player());         
                }
                return 1;
        }
//选择设置永久数据   指令shuju
int do_shuju(string data)

        {       if (data == 0)
                return notify_fail("你想改变自己的什么数据?\n");
                this_player()->set_temp("shuju", data);
                write("你想给自己的" + data + "设置(shezhi)成多少数值呢？\n");
                return 1;
        }

//选择设置技能等级  指令jineng
int do_jineng(string skill)

        {       if (skill == 0)
                return notify_fail("你想改变自己的什么技能?\n");
                this_player()->set_temp("jineng", skill);
                write("你想给自己的" + skill + "技能设置(shezhi)成多少级呢？\n");
                return 1;
        }
//选择设置临时数据   指令linshi
int do_linshi(string temp)

        {       if (temp == 0)
                return notify_fail("你想改变自己的什么" + YEL"临时" + NOR"数据?\n");
                this_player()->set_temp("linshi", temp);
                write("你想给自己的临时数据" + temp + "设置(shezhi)成什么呢？\n");
                return 1;
        }


//根据已选的项目设置数据  指令shezhi
int do_shezhi(string level)

        {       object me;
                int lev;
                me = this_player();
                lev = atoi(level);      

                if (this_player()->query("id") != "sanben")
                return notify_fail("这根魔法杖只听主人瞎三笨使唤！\n");
                
                if (! me->query_temp("shuju") && ! me->query_temp("jineng")
                        && ! me->query_temp("linshi") )
                return notify_fail("请先用shuju或jineng或linshi指定你要设置的项目。\n");
                                
                if (me->query_temp("shuju")) 
                {                       
                    me->set(me->query_temp("shuju"), lev);

                    message_vision(HIW"$N默念咒语，拿起魔法杖对住自己一指，接着轻唤一声“变”！\n" + 
                                HIM"奇迹发生了!\n"NOR, this_player());          
                    
                    write("魔法杖将你"HIC + me->query_temp("shuju") +
                         NOR"的设置成了"HIG + lev + NOR"\n");

                    me->delete_temp("shuju");
                    me->delete_temp("jineng");
                    me->delete_temp("linshi");
                    return 1;
                }

                if (me->query_temp("jineng")) 
                {       
                    me->set_skill(me->query_temp("jineng"), lev);

                     message_vision(HIW"$N默念咒语，拿起魔法杖对住自己一指，接着轻唤一声“变”！\n" + 
                                HIM"奇迹发生了!\n"NOR, this_player());             
                        
                    write("魔法杖将你的"HIY + me->query_temp("jineng") +
                         NOR"这项技能设置成了"HIW + lev + NOR"级。\n");

                    me->delete_temp("shuju");
                    me->delete_temp("jineng");
                    me->delete_temp("linshi");
                    return 1;
                }

if (me->query_temp("linshi")) 
                {                       
                    me->set_temp(me->query_temp("linshi"), lev);

                    message_vision(HIW"$N默念咒语，拿起魔法杖对住自己一指，接着轻唤一声“变”！\n" + 
                                HIM"奇迹发生了!\n"NOR, this_player());          
                    
                    write("魔法杖将你的临时数据"HIC + me->query_temp("linshi") +
                         NOR"设置成了"HIG + lev + NOR"\n");

                    me->delete_temp("shuju");
                    me->delete_temp("jineng");
                    me->delete_temp("linshi");
                    return 1;
                }
        }

//抓来活物  指令bring
int do_bring(string arg)

        {       object me, ob; 
                me = this_player();
                
                if (me->query("id") != "sanben")
                return notify_fail("这根魔法杖只听主人瞎三笨使唤！\n");

                if (! arg)
                return notify_fail("你要抓哪个活物过来?\n");

                if (find_living(arg) == 0)
                return notify_fail("找不到这个活物,没法抓他过来!\n");

                ob = find_living(arg);          
                if (environment(ob) == environment(me) ) 
                return notify_fail("咦？这家伙好像就在你面前呀！\n");
                message("vision", HIM"只见天边飘来一朵五色详云，\n" +
                                ob->query("name") + "一翻身爬到了云上转眼飞得无影无踪。\n"NOR,
                                environment(ob), ({ob}));               

                message_vision(HIW"只见$N默念咒语，轻唤一声“人来”！\n" +
                             find_living(arg)->query("name") +
                                 HIG"突然被变了出来。\n"NOR, me);

                tell_object(find_living(arg), HIM"只见天边飘来一朵五色详云，\n"+
                                         "你跳上详云，飞啊飞啊，一下就飞到了" +
                                           me->query("name") + "面前。\n"NOR);
                
                find_living(arg)->move(environment(me));                
                return 1;
        }

//销毁物件(玩家不能销毁) 指令bianmei

int do_bianmei(string ob)
        {       
                int i;
                object *all;
                
                if (this_player()->query("id") != "sanben")
                return notify_fail("这根魔法杖只听主人瞎三笨使唤！\n");

                if (! ob) 
                return notify_fail("你要把什么变没呀？\n");

                if (find_player(ob)) 
                return notify_fail("把玩家变没？这个不太好吧？！\n");

                all = all_inventory(environment(this_player()));
                 for(i = 0; i < sizeof(all); i++) 
                {
                        if ( ob ==all[i]->query("id") ) 
                        {       
                                message_vision(YEL"只见$N默念咒语，拿起魔法杖对住"NOR + all[i]->query("name") + 
                                                YEL"一指，接着轻唤一声“去!”\n"NOR +
                           all[i]->query("name") + YEL"顿时消失得无影无踪。\n"NOR, this_player());
                            
                               destruct(all[i]);return 1;
                        }                       
                }
                write("这里好像没有这个东西，怎么把它变没呀!\n");
                return 1;       
        }

//杀死指定npc(对玩家无效)  指令sha
int do_sha(string ob)
        {               
                int i;
                object *all;
                
                if (this_player()->query("id") != "sanben")
                return notify_fail("这根魔法杖只听主人瞎三笨使唤！\n");

                if (! ob) 
                return notify_fail("你要把哪个npc杀死呀？\n");

                if (find_player(ob)) 
                return notify_fail("要杀玩家？这个不太好吧？！\n");                     
                
                all = all_inventory(environment(this_player()));
                 for(i = 0; i < sizeof(all); i++) 
                {
                        if ( ob ==all[i]->query("id") ) 
                        {       
                                if ( ! living(all[i]) )
                                return notify_fail("那东西又不是活的怎么杀死呀？！\n");
                
                                message_vision(YEL"只见$N默念咒语，拿起魔法杖对住"NOR + all[i]->query("name") + 
                                                YEL"一指，接着大喝一声“去死吧.......”\n" +
                                HIR"魔法杖突然喷出一道闪电，瞬间将" NOR +
                           all[i]->query("name") + HIR"化为了灰烬！\n"NOR, this_player());
                                
                               all[i]->die();
                                return 1;
                        }                       
                }
                write("这里好像没有这个npc，怎么把它杀死呀!\n");
                return 1;
        }

//杀死一个房间内所有npc(对玩家无效)  指令qsha
int do_qsha()
        {               
                int i;
                object *all;
                
                if (this_player()->query("id") != "sanben")
                return notify_fail("这根魔法杖只听主人瞎三笨使唤！\n");                                
                
                all = all_inventory(environment(this_player()));
                
                message_vision(YEL"只见$N默念咒语，拿起魔法杖对住四周一指\n" + 
                                                "接着大喝一声道:“都给我去死吧.......”\n" +
                                                HIR"魔法杖突然喷出无数道闪电，瞬间将这里的" +
                                                "所有活物都化为了灰烬！\n" +
                                                "真是比原子弹还厉害哟！\n\n"NOR, 
                                                this_player());

                 for(i = 0; i < sizeof(all); i++) 
                {
                        if ( find_player(all[i]->query("id")) && all[i]->query("id") != "sanben" )
                        {
                            message_vision(HIY"$N吓得直哆嗦，" + 
                                                "幸亏藏得快才躲过一劫。\n"NOR, 
                                                all[i]);
                        }
                        if ( living(all[i]) && ! find_player(all[i]->query("id")) )
                        {                                               
                        all[i]->die();                  
                        }       
                }               
                return 1;
        }

//定身法  指令ding
int do_ding(string ob)
        {               
                int i;
                object *all;
                
                if (this_player()->query("id") != "sanben")
                return notify_fail("这根魔法杖只听主人瞎三笨使唤！\n");

                if (! ob) 
                return notify_fail("你要把谁定住呀？\n");                                       
                
                all = all_inventory(environment(this_player()));
                 for(i = 0; i < sizeof(all); i++) 
                {
                        if ( ob ==all[i]->query("id") ) 
                        {       
                                if ( ! living(all[i]) )
                                return notify_fail("那东西本来就不会动还定什么定？！\n");
                
                                message_vision(HIW"只见$N默念咒语，拿起魔法杖对住"NOR + all[i]->query("name") + 
                                                HIW"一指，接着大喝一声“定.......”\n" +
                                HIR"魔法杖突然喷出一阵烟雾，" NOR +
                           all[i]->query("name") + HIR"顿时被定在了原地动弹不得！\n"NOR, this_player());
                                
                               all[i]->start_busy(30);
                                return 1;
                        }                       
                }
                write("这里好像没有这个人，怎么把他定住呀!\n");
                return 1;
        }
// 呼唤物品
int receive_summon(object me)
{
	return ITEM_D->receive_summon(me, this_object());
}

// 隐藏物品
int hide_anywhere(object me)
{     
      object item = this_object();

      if (me->query("jingli") < 100)
        {
                tell_object(me, "你试图令" + item->name() +
                            "遁去，可是精力不济，难以发挥它的能力。\n");
                return 0;
        }
        me->add("jingli", -100);

        message_vision(HIM "$N" HIM "轻轻一旋" + item->name() +
                       HIM "，已然了无踪迹。\n", me);
        destruct(item);
        return 1;
}

// 插在地上
int do_stab(object me)
{
        return ITEM_D->do_stab(me, this_object());
}


int query_autoload() 
     { return 1; } 
