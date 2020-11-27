// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit NPC;

#include "mgb2.h"

void create()
{ 
        set_name("�ɹű�ʿ", ({"menggu bingshi","bingshi"}));
        set("long","����һλ�ַ���ԭ���ɹű�ʿ��\n");
        set("gender", "����" );
        set("age", random(30)+14);
        
        set("vendetta/authority", 1);
        set("attitude", "peaceful");    
        set("bellicosity", 100000);
        set("max_qi", 1000);
        set("eff_qi", 1000);
        set("qi", 1000);
        set("max_jing", 900);
        set("jing", 900);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 20);
        set("shen_type", -10);
        set("combat_exp", 200000);
        set("is_guojob",1);
        set_skill("force", 80); 
        set_skill("unarmed", 80);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        setup();
        carry_object(__DIR__"wandao")->wield();
        carry_object(__DIR__"tiejia")->wear();
}

void do_change(object ob)
{
        object me;
        mapping hp_status, skill_status;
        string *sname;
        int i, temp;
        me = this_object();

      
      	if (mapp(skill_status = me->query_skills())) 
      	{
                skill_status = me->query_skills();
                sname  = keys(skill_status);
                temp = sizeof(skill_status);
                for (i = 0; i < temp; i++) 
                {
                        me->delete_skill(sname[i]);
                }
      	}

    	if (mapp(skill_status = ob->query_skills())) 
    	{
                skill_status = ob->query_skills();
                sname  = keys(skill_status);
                temp = skill_status[0];
                for (i = 0; i < sizeof(skill_status); i++) 
                {
                  	if (sname[i] == "force" || sname[i] == "literate") continue;
                  	if (skill_status[sname[i]] >= temp)
                  	{ 
                  		temp = skill_status[sname[i]];}
              		}
        }
        
        if (temp < 60) temp = 60;
        if (temp > 200) temp = 200;
        
        me->set_skill("wuhu-duanmendao", temp - random(50));
        me->set_skill("unarmed", temp - random(50));
        me->set_skill("changquan", temp-random(50));
        me->set_skill("dodge", temp-random(50));
        me->set_skill("blade", temp-random(50));
        me->set_skill("parry", temp-random(50));
        me->set_skill("force", temp-random(50));
        me->set_skill("yunlong-shengong", temp-random(50));

        me->map_skill("blade","wuhu-duanmendao");
        me->map_skill("parry","wuhu-duanmendao");
        me->map_skill("unarmed", "changquan");
        me->map_skill("force", "yunlong-shengong");



/* copy hp */

        hp_status = ob->query_entire_dbase();
        me->set("str", hp_status["str"]+random(2));
        me->set("int", hp_status["int"]);
        me->set("con", hp_status["con"]+random(2));
        me->set("dex", hp_status["dex"]+random(10));
        me->set("combat_exp",hp_status["combat_exp"]*3/4);
        me->set("max_qi",    hp_status["max_qi"]*3/4);
        me->set("eff_qi",    hp_status["max_qi"]*3/4);
        me->set("qi",        hp_status["max_qi"]*3/4);
        me->set("max_jing",  hp_status["max_jing"]*3/4);
        me->set("eff_jing",  hp_status["eff_jing"]*3/4);
        me->set("jing",      hp_status["eff_jing"]*3/4);
        me->set("max_neili", hp_status["max_neili"]*3/4);
        me->set("neili",     hp_status["max_neili"]*3/4);   

        return;
}


void die()
{
        object ob, robber, room;
        
        if (! objectp(ob = query_last_damage_from())) 
                return;
                
        room = environment();  
        
        if (room->query("short") != "�׻�����"
                && room->query("short") != "��������"
                && room->query("short") != "��ȸ����"
                && room->query("short") != "��������")
                return ::die(); 
      
        if (ob->query_temp("guo_shoucheng/start_job") == 1 
                && ob->query_temp("guo_shoucheng/killed_mgb") < 40)
                ob->add_temp("guo_shoucheng/killed_mgb", 1);
                
        else
        if (ob->query_temp("guo_shoucheng/help_killed") < 30) 
                ob->add_temp("guo_shoucheng/help_killed", 1);  

        if (! objectp(ob = query("want_kill")) 
                || environment(ob) != environment())
                return ::die();
                
        switch (random(3)) 
        {
        case 0:
                message_vision(HIR "������������һ���ɹű�ʿ��\n" NOR, ob); 
                robber = new(__DIR__"robber1");
                robber->do_change(ob);
                robber->set("want_kill", ob);
                robber->move(room);
                robber->kill_ob(ob);
                ob->kill_ob(robber);
                break;
        case 1:
                message_vision(HIR"������������һ���ɹŽ��졣\n" NOR,ob); 
                robber = new(__DIR__"robber2");
                robber->do_change(ob);
                robber->set("want_kill", ob);
                robber->move(room);
                robber->kill_ob(ob);
                ob->kill_ob(robber);
                break;
        case 2:
                message_vision(HIR"������������һ���ɹŸ��֡�\n" NOR,ob); 
                robber = new(__DIR__"robber3");
                robber->do_change(ob);
                robber->set("want_kill", ob);
                robber->move(room);
                robber->kill_ob(ob);
                ob->kill_ob(robber);
                break;
        }       

        if (ob->query_temp("guo_shoucheng/start_job") == 1)
                robber->set("ygjg", ob);
                
        message_vision("$N���ڵ��������˼��£������������" HIR "��Ѫ" NOR "�����ˣ�\n",this_object());
        destruct(this_object());
        return;
}

