// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ITEM;

mapping default_dirs = ([
        "north"     : "北面",
        "south"     : "南面",
        "east"      : "东面",
        "west"      : "西面",
        "northup"   : "北边",
        "southup"   : "南边",
        "eastup"    : "东边",
        "westup"    : "西边",
        "northdown" : "北边",
        "southdown" : "南边",
        "eastdown"  : "东边",
        "westdown"  : "西边",
        "northeast" : "东北",
        "northwest" : "西北",
        "southeast" : "东南",
        "southwest" : "西南",
        "up"        : "上面",
        "down"      : "下面",
        "enter"     : "里面",
        "out"       : "外面",
]);

void create()
{       
        seteuid(getuid());
        set_name(HIM "福威大镖车" NOR, ({ "da biaoche", "biaoche", "che" }));
        set_weight(500000);
        set("no_get", 1);
        set("unit", "辆");
        set("value", 0);
        set("long", 
                HIM "一辆福威镖局的大镖车，上面结结实实盖着蓬布，一群镖头赶(gan)着车，牢牢地护在一边。" NOR); 
        set("owner", "lonely");
        set("parter", "lonely");
        set("owner_name", "黑客");
        set("no_clean_up", 1);
        setup();
        call_out("destroy1", 2, this_object());
}

void init()
{
        if (this_player()->query("id") == this_object()->query("owner")
        ||  this_player()->query("id") == this_object()->query("parter"))
        {
                add_action("do_gan", "gan"); 
                add_action("do_gan", "drive");
        }
}

void start_escape_me()
{
        call_out("destroy2", (int)query("time"), this_object());
}

int destroy2(object ob)
{
        object me, parter;
        
        if (objectp(ob))
        {
                /*
                message("channel:rumor", MAG "【镖局传闻】由于" + query("owner_name") +
                        "率领的镖队未能如期抵达，福威镖局已派人前去接管镖队！\n" NOR, users());
                */
                
                tell_object(all_inventory(environment(ob)),
                            HIW "忽然，远远走来一群人，原来是总镖头派人前来了，为首的镖师\n" +
                            "边走嘴里还边骂道：“他奶奶的！等了这么久也还没到，总镖头\n" +
                            "还以为让人给劫了，害老子白跑一趟！”说完，一干人等拉起镖\n" +
                            "车，扬长而去！\n" NOR);

                remove_call_out("destroy1");
                remove_call_out("destroy2");

                me = present(ob->query("owner"), environment(ob));
                if (! me) me = find_living(ob->query("owner"));
                if (objectp(me))
                {
                        me->delete_temp("apply/short");
                        me->delete_temp("quest_yunbiao/have_task");
                        me->set_temp("quest_yunbiao/finished_time", time());
                        me->delete_temp("quest_yunbiao/bandit_killed");    
                }
                parter = present(ob->query("parter"), environment(ob));
                if (! parter) parter = find_living(ob->query("parter"));
                if (objectp(parter))
                {
                        parter->delete_temp("apply/short");
                        parter->delete_temp("quest_yunbiao/have_task");
                        parter->set_temp("quest_yunbiao/finished_time", time());
                        parter->delete_temp("quest_yunbiao/bandit_killed");     
                }
                destruct(ob);
        }
        return 1;
}


int do_gan(string arg)
{        
        object me, parter, ob, env, obj, robber, *killer;
        string item, dir, dest, target;
        int reward_exp1, reward_pot1, reward_score1, flag, i, num, reward_exp2, reward_pot2, reward_score2;

        mapping exit;
        
        ob = this_object();
        me = present(ob->query("owner"), environment(ob));
        parter = present(ob->query("parter"), environment(ob));

        if (! arg) return notify_fail("你要赶什么？\n");

        if (! objectp(me) || ! objectp(parter)) 
                return notify_fail("护镖要两个人齐心协力，你的同伴不在，不要轻举妄动！\n"); 

        if (sscanf(arg, "%s to %s", item, dir) != 2 
        ||  item != "biaoche" && item != "che" && item != "da biaoche")
                return notify_fail("指令：gan 镖车 to 方向 \n");        
                        
        if (me->is_busy())
                return notify_fail("你现在正忙着哩。\n");

        flag = 0;
        killer = all_inventory(environment(me));
        for (i = 0; i < sizeof(killer); i++)
        {
                if (objectp(killer[i]) 
                &&  (killer[i]->query("want_kill1") == me->query("id")
                ||  killer[i]->query("want_kill2") == me->query("id")))
                flag = 1;
        }

        if (flag)   
                return notify_fail(CYN"你还是先把眼前的敌人解决了再说吧！\n"NOR);
        
        env = environment(me);
        if (! env) return notify_fail("你要去那里？\n");

        if (! mapp(exit = env->query("exits")) || undefinedp(exit[dir])) 
                return notify_fail("这个方向过不去。\n");
        
        dest = exit[dir];

        if (! (obj = find_object(dest)))
                call_other(dest, "???");
        if (! (obj = find_object(dest)))
                return notify_fail("那里好象过不去。\n");

        if (! undefinedp(default_dirs[dir]))
                target = default_dirs[dir];
        else
                target = obj->query("short");

        message_vision(HIG "$N赶着镖车往" + target + "驶去。\n" NOR, me);  
        me->delete_temp("lonely");
        if (objectp(parter))
                parter->delete_temp("lonely");
        
        if (file_name(obj) != ob->query("file"))
        {
                if (ob->move(obj) && me->move(obj) && parter->move(obj)) 
                {
                        all_inventory(env)->follow_me(me, dir);
                        message_vision(HIG "$N赶着镖车驶了过来。\n" NOR, me);
                        me->start_busy(random(2) + 1);
                        parter->start_busy(random(2) + 1);
                }

                if (random(10) < 2 && ! environment(ob)->query("no_fight"))
                {
                        num = random(2) + 1;
                        for (i = 0; i < num; i++)
                        {
                                robber = new(__DIR__"bandit");
                                robber->set("want_kill1", me->query("id"));
                                robber->set("want_kill2", parter->query("id")); 
                                robber->move(environment(ob));  
                                robber->kill_ob(me);
                                robber->kill_ob(parter);
                                robber->check_me();  
                                robber->start_busy(1);
                        }
                        me->start_busy(1);
                        parter->start_busy(1);   
                }
        } else
        {
                reward_exp1 = (int)me->query("combat_exp") / 3000;
                reward_exp1 = reward_exp1 + (int)me->query_temp("quest_yunbiao/bonus") * 25;
                reward_exp1 = reward_exp1 + (int)me->query_temp("quest_yunbiao/bandit_killed") * 200;               
                reward_exp1 = reward_exp1 / 2 + random(reward_exp1 / 2);
                if (reward_exp1 > 4000) reward_exp1 = 4000;
                reward_pot1 = reward_exp1;
                reward_score1 = reward_exp1 / 40;
                
                reward_exp2 = (int)parter->query("combat_exp") / 3000;
                reward_exp2 = reward_exp2 + (int)parter->query_temp("quest_yunbiao/bonus") * 20;
                reward_exp2 = reward_exp2 + (int)parter->query_temp("quest_yunbiao/bandit_killed") * 200;                  
                reward_exp2 = reward_exp2 / 2 + random(reward_exp2 / 2);
                if(reward_exp2 > 4000) reward_exp2 = 4000;
                reward_pot2 = reward_exp1;
                reward_score2 = reward_exp1 / 40;
                /*
                message("channel:rumor", HIM "【镖局传闻】" + me->query("name") +
                        "率领的镖队历经千辛万苦，终于顺利抵达！\n" NOR,
                        users());
                */
                tell_object(me, HIW "在此次运镖中你获得了" +
                            CHINESE_D->chinese_number(reward_exp1) + "点实战经验、" +
                            CHINESE_D->chinese_number(reward_pot1) + "点潜能\n及" +
                            CHINESE_D->chinese_number(reward_score1) + "点综合评价奖励！\n" NOR);

                tell_object(parter, HIW "在此次运镖中你获得了" +
                            CHINESE_D->chinese_number(reward_exp2) + "点实战经验、" +
                            CHINESE_D->chinese_number(reward_pot2) + "点潜能\n及" +
                            CHINESE_D->chinese_number(reward_score2) + "点综合评价奖励！\n" NOR);

                me->add("quest_yunbiao/reward_exp", reward_exp1);
                me->add("quest_yunbiao/reward_potential", reward_pot1);
                me->add("combat_exp", reward_exp1);
                me->add("potential", reward_pot1);
                if (me->query("potential") > me->query_potential_limit()) 
                        me->set("potential", me->query_potential_limit()); 
                me->add("score", reward_score1);
       
                parter->add("quest_yunbiao/reward_exp", reward_exp2);
                parter->add("quest_yunbiao/reward_potential", reward_pot2);
                parter->add("combat_exp", reward_exp2);
                parter->add("potential", reward_pot2);
                if (parter->query("potential") > parter->query_potential_limit()) 
                        parter->set("potential", parter->query_potential_limit()); 
                parter->add("score", reward_score2);       

                me->delete_temp("quest_yunbiao/have_task");
                me->set_temp("quest_yunbiao/finished_time", time());
                parter->delete_temp("quest_yunbiao/have_task");
                parter->set_temp("quest_yunbiao/finished_time", time());
                me->delete_temp("quest_yunbiao/bandit_killed");     
                me->delete_temp("apply/short");  
                parter->delete_temp("quest_yunbiao/bandit_killed");
                parter->delete_temp("apply/short");
              
                remove_call_out("destroy1");
                remove_call_out("destroy2");
                destruct(ob);
        }   
        return 1;
}

int destroy1(object ob)
{
        object me, parter;

        if (! objectp(ob) || !environment(ob))
                return 1;

        if (objectp(ob) && ! present(ob->query("owner"), environment(ob)) 
        &&  ! present(query("parter"), environment(ob)))
        {
                me = find_player(ob->query("owner"));
                if (! me) me = find_living(ob->query("owner"));
                
                parter = find_player(ob->query("parter"));
                if(! parter) parter = find_living(ob->query("parter"));     
                
                if (objectp(me))
                {
                        me->delete_temp("quest_yunbiao");
                        me->delete_temp("apply/short");
                }
                if (objectp(parter))
                {
                        parter->delete_temp("quest_yunbiao");
                        parter->delete_temp("apply/short");
                }

                message("channel:rumor", HIB "【镖局传闻】" + query("owner_name") +
                        "率领的镖队在半路让人给劫了！\n" NOR, 
                        users());
                remove_call_out("destroy1");
                remove_call_out("destroy2");
                destruct(ob);
        } else
        {
                remove_call_out("destroy1");
                call_out("destroy1",2,ob);
                return 1;
        }
}

