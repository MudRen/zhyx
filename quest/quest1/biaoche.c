// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ITEM;

mapping default_dirs = ([
        "north"     : "����",
        "south"     : "����",
        "east"      : "����",
        "west"      : "����",
        "northup"   : "����",
        "southup"   : "�ϱ�",
        "eastup"    : "����",
        "westup"    : "����",
        "northdown" : "����",
        "southdown" : "�ϱ�",
        "eastdown"  : "����",
        "westdown"  : "����",
        "northeast" : "����",
        "northwest" : "����",
        "southeast" : "����",
        "southwest" : "����",
        "up"        : "����",
        "down"      : "����",
        "enter"     : "����",
        "out"       : "����",
]);

void create()
{       
        seteuid(getuid());
        set_name(HIW "�ڳ�" NOR, ({ "biao che", "cart", "che" }));
        set_weight(300000);
        set("no_get", 1);
        set("unit", "��");
        set("value", 0);
        set("long", 
                HIW "һ�������ھֵ��ڳ���һ����ͷ��׼���ϳ�(gan)����ء�" NOR); 
        set("owner", "lonely");
        set("owner_name", "�ڿ�");
        set("no_clean_up",1);
        setup();
        call_out("destroy1", 2, this_object());
}

void init()
{
        if (this_player()->query("id") == this_object()->query("owner"))
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
        object me;
        if (objectp(ob))
        {
                
                message("channel:rumor", HIY "���ھִ��š�����" + query("owner_name") +
                        "���͵��ڳ�δ�����ڵִ�����ھ�������ǰȥ�ӹ��ڳ���\n" NOR, users());
                
                tell_object(all_inventory(environment(ob)),
                            HIW "��Ȼ��ԶԶ����һȺ�ˣ�ԭ��������ͷ����ǰ���ˣ�Ϊ�׵���ʦ\n" +
                            "�������ﻹ��������������̵ģ�������ô��Ҳ��û��������ͷ\n" +
                            "����Ϊ���˸����ˣ������Ӱ���һ�ˣ���˵�꣬һ���˵�������\n" +
                            "�����ﳤ��ȥ��\n" NOR);

                remove_call_out("destroy1");
                remove_call_out("destroy2");

                me = present(ob->query("owner"), environment(ob));
                if (objectp(me))
                {
                        me->delete_temp("apply/short");
                        me->delete_temp("quest_yunbiao/have_task");
                        me->set_temp("quest_yunbiao/finished_time", time());
                }
                destruct(ob);
        }
        return 1;
}


int do_gan(string arg)
{        
        object me, ob, env, obj, robber, *killer;
        string item, dir, dest, target;
        int reward_exp, reward_pot, reward_score, flag, i;

        mapping exit;
        me = this_player();
        ob = this_object();

        if (! arg) return notify_fail("��Ҫ��ʲô��\n");

        if (me->query("id") != ob->query("owner")) 
                return notify_fail("��ϵĲ����Լ����ڳ��ɣ�\n"); 

        if (sscanf(arg, "%s to %s", item, dir) != 2 
        ||  item != "biao che" && item != "che")
                return notify_fail("ָ�gan �ڳ� to ���� \n");        
                        
        if (me->is_busy())
                return notify_fail("��������æ������\n");

        flag = 0;
        killer = all_inventory(environment(me));
        for (i = 0; i < sizeof(killer); i++)
        {
                if (objectp(killer[i]) 
                &&  killer[i]->query("want_kill") == me->query("id"))
                flag = 1;
        }

        if (flag)   
                return notify_fail(CYN "�㻹���Ȱ���ǰ�ĵ��˽������˵�ɣ�\n" NOR);
        
        env = environment(me);
        if (! env) return notify_fail("��Ҫȥ���\n");

        if (! mapp(exit = env->query("exits")) || undefinedp(exit[dir])) 
                return notify_fail("����������ȥ��\n");
        
        dest = exit[dir];

        if (! (obj = find_object(dest)))
                call_other(dest, "???");
        if (! (obj = find_object(dest)))
                return notify_fail("����������ȥ��\n");

        if (! undefinedp(default_dirs[dir]))
                target = default_dirs[dir];
        else
                target = obj->query("short");

        message_vision(HIG "$N�����ڳ���" + target + "ʻȥ��\n" NOR, me);  
        me->delete_temp("lonely");
        
        if (file_name(obj) != ob->query("file"))
        {
                if (ob->move(obj) && me->move(obj)) 
                {
                        all_inventory(env)->follow_me(me, dir);
                        message_vision(HIG "$N�����ڳ�ʻ�˹�����\n" NOR, me);
                        me->start_busy(random(2) + 2);
                }

                if (random(12) < 2 && ! environment(ob)->query("no_fight"))
                {
                        robber = new(__DIR__"robber");
                        robber->set("want_kill", me->query("id")); 
                        robber->move(environment(ob));  
                        robber->kill_ob(me);
                        robber->check_me();  
                        me->start_busy(1);
                        robber->start_busy(1);
                }
        } else
        {
                reward_exp = (int)me->query("combat_exp") / 3000;
                reward_exp = reward_exp + (int)me->query_temp("quest_yunbiao/bonus") * 20;
                reward_exp = reward_exp / 2 + random(reward_exp);
                if (reward_exp > 3000) reward_exp = 3000;
                reward_pot = reward_exp;
                reward_score = reward_exp / 40;
                
                message("channel:rumor", HIY "���ھִ��š�" + me->query("name") + 
                        "���͵��ڳ�����ǧ����࣬����˳���ִ\n" NOR,
                        users());
                
                tell_object(me, HIW "�ڴ˴�������������" +
                            CHINESE_D->chinese_number(reward_exp) + "��ʵս���顢" +
                            CHINESE_D->chinese_number(reward_pot) + "��Ǳ�ܼ�\n" +
                            CHINESE_D->chinese_number(reward_score) + "���ۺ����۽�����\n" NOR);

                me->add("quest_yunbiao/reward_exp", reward_exp);
                me->add("quest_yunbiao/reward_potential", reward_pot);
                me->add("combat_exp", reward_exp);
                me->add("potential", reward_pot);
                if (me->query("potential") > me->query_potential_limit()) 
                        me->set("potential", me->query_potential_limit()); 
                me->add("score", reward_score);

                me->delete_temp("quest_yunbiao/have_task");
                me->set_temp("quest_yunbiao/finished_time", time());
                me->delete_temp("apply/short");
                remove_call_out("destroy1");
                remove_call_out("destroy2");
                destruct(ob);
        }   
        return 1;
}

int destroy1(object ob)
{
        object me;

        if (! objectp(ob) || ! environment(ob))
                return 1;

        if (objectp(ob) && ! present(ob->query("owner"), environment(ob)))
        {
                me = find_player(ob->query("owner"));
                if (! me) me = find_living(ob->query("owner"));
                if (objectp(me))
                {
                        me->delete_temp("quest_yunbiao");
                        me->delete_temp("apply/short");
                }

                message("channel:rumor", HIY "���ھִ��š�" + query("owner_name") +
                        "���͵��ڳ��ڰ�·���˸����ˣ�\n" NOR, users());
                remove_call_out("destroy1");
                remove_call_out("destroy2");
                destruct(ob);
        } else
        {
                remove_call_out("destroy1");
                call_out("destroy1", 2, ob);
                return 1;
        }
}

