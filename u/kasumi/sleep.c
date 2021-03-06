// sleep.c

#include <ansi.h>
#include <command.h>

void wakeup(object me);

int main(object me, string arg)
{
        object obj, old_target;
        int i;
        object *inv;
        mapping fam;
        mapping cnd;
        string *kc;
        object where = environment(me);
        int qi, jing;
        object bag;

        seteuid(getuid());

        if ((! (fam = me->query("family")) || fam["family_name"] != "丐帮") &&
           ! (where->query("sleep_room"))
             && !objectp(bag = present("sleepbag", me))
           || (where->query("no_sleep_room")))
                return notify_fail("这里不是你能睡的地方！\n");

        if (me->is_busy())
                return notify_fail("你正忙着呢！\n");

        if( me->is_fighting() )
                return notify_fail("战斗中不能睡觉！\n");

        if (where->query("hotel") && !(me->query_temp("rent_paid")))
        {
                message_vision(CYN "店小二从门外对$N" CYN "大叫：把这里当"
                               "避难所啊？先到一楼付钱后再来睡！\n" NOR, me);
                return 1;
        }

        jing = (int) me->query("jing");
        qi   = (int) me->query("qi");
        if (jing < 0 || qi < 0)
                return notify_fail("你现在接近昏迷，睡不着觉。\n");
        cnd = me->query_condition();
        if (cnd && sizeof(cnd))
        {
                kc   = keys(cnd);
                for (i = 0; i < sizeof(kc); i++)
                {
                        if (CONDITION_D(kc[i])->min_qi_needed(me) > qi ||
                            CONDITION_D(kc[i])->min_jing_needed(me) > jing)
                        {
                                message("vision", me->name() + "看样子是想睡觉，"
                                        "可是辗转反侧，就是睡不着。\n",
                                        environment(me), me);
                                tell_object(me, "你想合上眼睛好好睡上一觉，可是" +
                                            to_chinese(kc[i]) + "不断折磨着你，"
                                            "让你辗转难眠。\n");
                                return 1;
                        }
                }
        }

        if (where->query("sleep_room"))
        {
                write("你往床上一躺，开始睡觉。\n");
                write("不一会儿，你就进入了梦乡。\n");
                me->set_temp("block_msg/all", 1);
                message_vision("$N一歪身，倒在床上，不一会"
                           "便鼾声大作，进入了梦乡。\n",me);
        } else
        {
                write("你往地下角落一躺，开始睡觉。\n");
                write("不一会儿，你就进入了梦乡。\n");
                me->set_temp("block_msg/all", 1);
                message_vision("$N往地下角落屈身一躺，不一"
                           "会便鼾声大作，做起梦来。\n",me);
        }

        me->set("no_get", 1);
        me->set("no_get_from", 1);

        me->set_temp("sleeped", 1);
        if (where->query("hotel"))
                me->delete_temp("rent_paid");

        me->disable_player(" <睡梦中>");
        me->start_call_out(bind((: call_other, __FILE__, "wakeup", me :), me),
                           2 + random(8));

        return 1;
}

void wakeup(object me)
{
        int i;
        object *ob, weapon1, weapon2, handing, env;
        mapping armors;
        string armor;
        if (! me || ! me->query_temp("sleeped"))
                return;
        if (living(me))
        {
                me->delete_temp("sleeped");
                return;
        }
        //因为与cmds里指令相同的add_action消失，所以新加       
        env = environment(me);               //睡觉的地方
        weapon1 = me->query_temp("weapon");  //第一把兵器
        weapon2 = me->query_temp("secondary_weapon");  //第二把兵器
        handing = me->query_temp("handing");    //手上hand的物件         

        armors = me->query_temp("armor");     //身上穿的armor
        if ( armors && sizeof(armors) > 0 )         
        {
             foreach (armor in keys(armors))
             me->set_temp("armor1/" + armor, armors[armor]);
        }       

        me->move(VOID_OB);       //本人移动到虚空里一下再回来
                                //保证环境里有的add_action再次生效
        me->enable_player();
        
        ob = all_inventory(me);         
        for(i=0; i<sizeof(ob); i++)   
           {  
              if ( ob->query("money_id") ) continue; //是钱的话滤过    
              ob[i]->move(VOID_OB);  //身上所有物件离开一下再回来
              ob[i]->move(me);       //保证add_action回来且优先于cmds指令       
           }      
        me->move(env);             //返回睡觉的地方      
        
        if ( weapon1 )  //如果有第一把兵器
            weapon1->wield();  

        if ( weapon2 )  //如果有第二把兵器
            weapon2->wield();

        if ( handing ) //如果有hand的物件
            me->set_temp("handing", handing); 

        armors = me->query_temp("armor1");
        if ( armors && sizeof(armors) > 0 )  //如果身上有穿armor       
        {
             foreach (armor in keys(armors))
             armors[armor]->wear();
        }    
        me->delete_temp("armor1");

        me->set_temp("block_msg/all", 0);
        me->delete("no_get");
        me->delete("no_get_from");
        me->delete_temp("sleeped");
        me->set_temp("disabled", 0);
      //  if (time() - me->query("last_sleep") >= 1)
       if (time() - me->query("last_sleep") != 1)
        {
		   if (me->query("family/family_name") == "丐帮" && me->query_skill("huimeng-xinfa", 1) > 300 && random (5) > 2 )
		   {
		        me->set("qi",    me->query("max_qi"));
                me->set("jing",  me->query("max_jing"));
                me->set("neili",  me->query("max_neili"));
				if (me->query_skill("nap-unarmed", 1) && me->can_improve_skill("nap-unarmed"))
			        me->improve_skill("nap-unarmed", ((int) me->query_skill("huimeng-xinfa", 1)) + 5);
		   }
		   else
		   {
                me->set("qi",    me->query("max_qi"));
                me->set("jing",  me->query("max_jing"));
                me->add("neili", me->query("max_neili") / 2 -
                                 me->query("neili") / 2 );
			}
                message("vision", me->name() + "一觉醒来，精力充沛"
                                  "地活动了一下筋骨。\n",
                                  environment(me), ({ me }));
                write("你一觉醒来，只觉精力充沛。该活动一下了。\n");
                me->set("last_sleep", time());
        } else
        {
                message("vision", me->name() + "迷迷糊糊的睁开眼睛，"
                                  "懒散无神的爬了起来。\n",
                        environment(me), ({ me }));
                write("你迷迷糊糊的睁开双眼，爬了起来。\n");
        }      
        me->write_prompt();       
}

int help(object me)
{
        write(@HELP
指令格式 : sleep
 
顾名思义，这个指令是用来睡觉的。
HELP );
        return 1;
}

