// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit NPC;

int is_bunch_npc() { return 1; }

int init_area_npc(object ob);
int do_join_bunch(object who);

void setup() 
{

        set("bunch/zhengzhao", 1 + random(3));
        ::setup(); 
        call_out("init_area_npc", 1, this_object());

} 
mixed accept_ask(object who, string topic)
{
        if (this_object()->is_quester())
                return QUEST_D->accept_ask(this_object(), who, topic);

        if (! this_object()->is_waiter()
           && (who->query("ultra_quest/next_npc") == this_object()->name()
           || who->query("ultra_quest/npc") == this_object()->name()))
                return ULTRA_D->ask_information(this_object(), who, topic);  
         if ( who->query("xquest/target_npc") == this_object()->name()
           || who->query("xquest/init_npc") == this_object()->name() )
                return XQUEST->accept_ask(this_object(),who, topic);
}

// �ظ����������Ӧ��
int need_accede(object who)
{
        if (! this_object()->is_waiter()
           && who->query("ultra_quest/quest/obj") == this_object()->name()
           && who->query("ultra_quest/next_npc") == this_object()->name())
                return ULTRA_D->need_accede(this_object(), who);
}

int init_area_npc(object ob)
{
        mapping bunch, sk;
        object area;
        int exp, level, i;
        string *ks;
        
        ob = this_object();

        if (! objectp(ob) || ! area = environment(ob)) 
               return 1;
        
        if (! area->is_area_room()) return 0;
        
        this_object()->set("bunch/area_file", base_name(area));
            
        if (! stringp(area->query("bunch/bunch_name"))) 
                return 0;
                
        if (area->query("bunch/npc_file") != base_name(ob))
                return 0;               
        
        bunch = ([ "bunch_name"       : area->query("bunch/bunch_name"),
                   "max_zhongcheng" : 100,
                   "zhongcheng" : area->query("bunch/zhongcheng") ]);
                           
        add("bunch", bunch);

        exp = BUNCH_D->query_bunch_fame(area) / 100;
        level = to_int(pow(to_float(exp), 1.0 / 3)) * 10 + 1;
                
        if (level < 100) level = 100;
        
        if (! mapp(sk = query_skills()))
        {
                set("combat_exp", 1000000 * level);
                set("max_qi", 400 * level);
                set("max_jing", 200 * level);
                set("max_neili", 420 * level);
                set("neili", 420 * level);
                set("level", level / 10);
                set("jiali", 7 * level);

                set_skill("force", level);
                set_skill("parry", level);
                set_skill("dodge", level);
                set_skill("sword", level);
                set_skill("cuff",  level);
                set_skill("strike", level);
                set_skill("huashan-neigong", level);
                set_skill("feiyan-huixiang", level);
                set_skill("huashan-jianfa", level);
                set_skill("hunyuan-zhang", level);
                set_skill("poyu-quan", level);

                map_skill("force", "huashan-neigong");
                map_skill("parry", "huashan-jianfa");
                map_skill("sword", "huashan-jianfa");
                map_skill("dodge", "feiyan-huixiang");
                map_skill("cuff" , "poyu-quan");
                map_skill("strike", "hunyuan-zhang");

                prepare_skill("cuff", "poyu-quan");
                prepare_skill("strike", "hunyuan-zhang");          
                
                return 1;     
        } 
         
        ks = keys(sk);

        for (i = 0; i < sizeof(ks); i++)
                set_skill(ks[i], level);   
        
        return 1;        
}

int accept_object(object who, object ob)
{
        int r; 
        mapping data;
        string  *obj;
        string  stuffid, stuffname;

        if (r = ::accept_object(who, ob))   
                return r;            
        
        if (this_object()->is_quester())
                return QUEST_D->accept_object(this_object(), who, ob);

        if (! this_object()->is_waiter()
           && (who->query("ultra_quest/next_npc") == this_object()->name()
           || who->query("ultra_quest/quest/obj") == this_object()->name()))
                return ULTRA_D->accept_object(this_object(), who, ob); 
         if ( who->query("xquest/target_npc") == this_object()->name()
           || who->query("xquest/init_npc") == this_object()->name() )
                return XQUEST->accept_object( who, ob, this_object() );

        if (who->query("bunch/bunch_name") == query("bunch/bunch_name")) 
        {
                command("say ���ǰ����ֵܣ��α���˿�����\n");
                return 0;
        }  

/*
        if (base_name(environment(this_object())) != query("bunch/area_file"))
        {
                command("say �������е㲻�ʣ������µ��һ�ȥ��˵�ɡ�\n");
                return 0;
        }
*/
                             
                             
        if (query("bunch/zhengzhao") == 1)       
        {
                command("say " + RANK_D->query_self(this_object()) +
                	"ֻ���书����Ȥ������һ����̸��\n");
                return 0;
        }        

        if (query("bunch/zhengzhao") == 2)       
        {
                if (query_temp("invite/target") != who) 
                {
                        command("say �޹�����»����֪" + 
                        	RANK_D->query_respect(who) + "����" + ob->name() + 
                        	"�к����⣿\n");
                        return 0;
		}       
		
                if (! ob->query("money_id"))     
                {
                        command("say " + RANK_D->query_self_rude(this_object()) +
                         	"ֻ��Ǯ����Ȥ������������Լ����Űɡ�\n");
                        return 0;
                }       

                if (ob->value() < query_temp("invite/money") * 10) 
                {
                        command("say �Ҳ���˵������" +
                        	chinese_number(query_temp("invite/money") / 1000) +
                        	"���ƽ���һ����Ҳ���У�\n");
                        return 0;
                }
                
                if (query("bunch/bunch_name") && 
                    query("bunch/zhongcheng") > who->query("meili"))   
                {
                        command("say �����������Ǯ������ζԵ�������������֣�\n");
                        return 0;
                }
                
                return do_join_bunch(who);
        }
        
        if (query("bunch/zhengzhao") == 3)       
        {
                data = query_temp("invite/target");
                
                if (! mapp(data)) data = ([]);
                
                obj = keys(data);
                
                if (member_array(who->query("id"), obj) == -1)        
                {
                        command("say �����ز���ʶ��Ϊ�θ�" +
                        	RANK_D->query_self(this_object()) + ob->name() +
                        	"��\n");
                        return 0;
                }
                
                sscanf (data[who->query("id")], "%s:%s", stuffid, stuffname);
                
                if (stuffname != ob->query("name") 
                ||  stuffid != ob->query("id"))    
                {
                        command("say " + RANK_D->query_respect(who) +
                        	"������Ҫ����" + stuffname + "(" +
                        	stuffid + ")������" + ob->query("name") +
                        	"(" + ob->query("id") + ")��\n");
                        return 0;
                }
                
                if (query("bunch/bunch_name") && 
                    query("bunch/zhongcheng") > who->query("meili"))     
                {
                        command("say ����������Ķ���������ζԵ�������������֣�\n");
                        return 0;
                }
                
                return do_join_bunch(who);
        }
}

int do_join_bunch(object who)
{
        string fname, bunch, area;
        
        if (! stringp(bunch = who->query("bunch/bunch_name")))      
        {
                command("say �ף���û�м����ᣬ������μ����أ�\n");
                return 0;
        }
        
        if (bunch == query("bunch/bunch_name"))        
        {
                command("say ���Ƕ���ͬ����֣����º������\n");
                return 0;
        }
         
        area = base_name(environment(this_object()));
        
/*
       	if (sizeof(children(base_name(this_object()) + ".c")) > 2 ||
       	    area != query("bunch/area_file") ||
            ! environment(this_object())->is_area_room())
       	{
                command("say " + RANK_D->query_self_rude(this_object()) +
                	"���岻�ʣ������´���˵�ɡ�\n");
                return 0;
        }
*/
        
        if (stringp(fname = query("bunch/bunch_name")))        
                BUNCH_D->remove_area_into_bunch(fname, area, this_object());

        command("say ��Ȼ" + RANK_D->query_respect(who) +
                "��˿�����" + RANK_D->query_self(this_object()) +
                "������Ҳ���ܶԲ����㰡��\n");
        message_vision("$N���������ᡸ" + bunch + "����\n",
                this_object());

        BUNCH_D->add_area_into_bunch(bunch, area, this_object());
        
        if (query_temp("invite/target"))
               delete_temp("invite/target");
        
        set("no_clean_up", 1);
                       
        return 1;
}

void die()
{      
        object area; 
        int kaifa;

        area = environment(this_object());
        
        if (! area->is_area_room()) 
                return ::die();
                
        if (base_name(area) != query("bunch/area_file"))
                return ::die();

        if (area->query("bunch/npc_id") != query("id"))
                return ::die();
                 
        if (! stringp(query("bunch/bunch_name")))
                return ::die();                

        kaifa = area->query("bunch/kaifa");
        kaifa = kaifa - (random(10) + 1); 
        
        if (kaifa < 20) kaifa = 20;

        area->set("bunch/kaifa", kaifa);
        area->add("bunch/zhongcheng", -10);
        area->save();

        message("channel:rumor", HIM "��ҥ������ĳ�ˣ�����" + query("name") + "��ɱ��" + 
                                 area->short() + "�Ŀ����Ƚ�Ϊ" + kaifa + "��\n" NOR, users());
                
        return ::die();
}
