
//��̨npc�̳��ļ�

#include <ansi.h>    
#define  SAVE_FILE      "/data/leitai/npc"   
#define  JINYONG         __DIR__"jinyong"        

inherit NPC;

void init();
int accept_fight(object ob);
int pfm();
int do_copy(object me);
string query_save_file();
int save();
int restore();
void disappear();
void do_disappear();

void init()
{     
     add_action("do_copy", "copy");
}


int accept_fight()
{
     if ( ! this_player()->query_temp("leitai") )
        {
           command("say ���ֲ��Ǵ��޵ģ�Ϲ��ʲô���֡�");
           return 0;
        }
     command("say ��,�����Ǿ����Ȼ��Ȼ���");       
     if ( ! is_busy() ) 
        {
           exert_function("powerup");
           exert_function("shield");
        }
     return 1; 
}

int pfm()
{    
    string pfm;
    if ( ! query("pfm") ) return 0;
    pfm = query("pfm")[random(sizeof(query("pfm")))];
    if ( ! pfm || pfm == 0 || pfm =="") return 0; 
    perform_action(pfm);     
    return 1;
}

int do_copy(object ob)
{
        object me;
        mapping hp_status, skill_status, map_status, prepare_status;
        mapping my;
        string *sname, *mname, *pname;
        int i, temp;
       
        me = this_object();        
       
        set_name(ob->query("name"), ({ob->query("id")}));
        set("title", ob->query("title"));       
        set("gender", ob->query("gender"));
        set("family", ob->query("family"));
        set("class", ob->query("class"));
        set("age", ob->query("age"));       
        set("long", ob->query("long"));
        set("str", ob->query("str"));
        set("int", ob->query("int"));
        set("con", ob->query("con"));
        set("dex", ob->query("dex"));

        if (mapp(skill_status = me->query_skills()))
        {
                skill_status = me->query_skills();
                sname = keys(skill_status);

                temp = sizeof(skill_status);
                for (i = 0; i < temp; i++)
                        me->delete_skill(sname[i]);
        }
        if (mapp(skill_status = ob->query_skills()))
        {
                skill_status = ob->query_skills();
                sname = keys(skill_status);

                for (i = 0; i < sizeof(skill_status); i++)
                        me->set_skill(sname[i], skill_status[sname[i]]);
        }        
        if (mapp(map_status = me->query_skill_map()))
        {
                mname = keys(map_status);

                temp = sizeof(map_status);
                for (i = 0; i < temp; i++)
                        me->map_skill(mname[i]);
        }
        if (mapp(map_status = ob->query_skill_map()))
        {
                mname = keys(map_status);

                for(i = 0; i < sizeof(map_status); i++)
                        me->map_skill(mname[i], map_status[mname[i]]);
        }
        if (mapp(prepare_status = me->query_skill_prepare()))
        {
                pname = keys(prepare_status);

                temp = sizeof(prepare_status);
                for(i = 0; i < temp; i++)
                        me->prepare_skill(pname[i]);
        }
        if (mapp(prepare_status = ob->query_skill_prepare()))
        {
                pname = keys(prepare_status);

                for(i = 0; i < sizeof(prepare_status); i++)
                        me->prepare_skill(pname[i], prepare_status[pname[i]]);
        }
        hp_status = ob->query_entire_dbase();
        my = me->query_entire_dbase();

        my["str"] = hp_status["str"];
        my["int"] = hp_status["int"];
        my["con"] = hp_status["con"];
        my["dex"] = hp_status["dex"];

        my["max_qi"]     = hp_status["max_qi"];
        my["eff_qi"]     = hp_status["eff_qi"];
        my["qi"]         = hp_status["qi"];
        my["max_jing"]   = hp_status["max_jing"];
        my["eff_jing"]   = hp_status["eff_jing"];
        my["jing"]       = hp_status["jing"];
        my["max_neili"]  = hp_status["max_neili"];
        my["neili"]      = hp_status["neili"];
        my["jiali"]      = hp_status["jiali"];
        my["combat_exp"] = hp_status["combat_exp"];

        if (ob->query("can_learn/dugu-jiujian/nothing"))
            me->set("can_learn/dugu-jiujian/nothing",1);

        if ( ob->query("couple/id"))
            me->set("couple/id",ob->query("couple/id"));
           
        save();
      //  restore();
        return 1;
}

void setup()
{
     set_name(query("name"), ({ query("id") }));
     
     :: setup();
}

string query_save_file()
{
        string id;   
        return sprintf(SAVE_FILE + query("level") + ".o");     
}

int save()
{
        string file;

        if (stringp(file = this_object()->query_save_file()))
        {
                assure_file(file);
                return save_object(file);
        }
        return 0;
}

int restore()
{
        string file;

        if (stringp(file = this_object()->query_save_file()) &&
            file_size(file) > 0)
        {
              restore_object(file);
	       set("chat_msg_combat", ({	
                  (: pfm : ),
		    (: exert_function, "recover" :),		
	        }) );   
              set("chat_msg", ({ 
                        (: do_disappear :),                       
               }));
         

         /*     if ( query("weapon") )
              carry_object(query("weapon"))->wield(); 
              if ( query("hand") )
              carry_object(query("hand"))->wear();     */         
              return 1;
        }
        return 0;
}

void win()
{
    object me, jy, ob;
    string msg;
    

    if (! objectp(me = query_competitor())) return; 

    ob = this_object();    
    jy = find_object(JINYONG);
    if ( ! jy ) jy = load_object(JINYONG);   


    message_vision (HIC"ֻ���������ָ��$Nһָ��$N��ʱ�ָ��˾���\n"NOR,me);
    me->set("eff_qi",me->query("max_qi")); 
    me->set("eff_jing",me->query("max_jing"));               
    me->set("qi",me->query("eff_qi"));
    me->set("jing",me->query("eff_jing")); 
    me->set("neili",me->query("max_neili")); 
    me->clear_condition("poison");

    msg = "���α���������"NOR HIR + ob->name() + NOR HIY"սʤ��ս��"NOR HIR+ 
          me->name() + NOR HIY"��\n";
    call_other(JINYONG, "shout_message", msg ); 
   
    command("haha");
    if ( query("level") < 2 || 
         jy->query("idlist/" + (query("level") - 1)) == me->query("id") )
    {
        command("say ��λ" + RANK_D->query_respect(me) + 
                "�������ü����̿�ѧ����ܸ���һ��¥ѽ!");   
        message_vision(HIW"\nֻ��$N˵���Ҵ�ææ���뿪����̨��\n\n"NOR,
                    this_object()); 
     
        me->delete_temp("leitai");        
        jy->save();   
        msg = "";
        msg = "�˴ι���" + me->name() + "�޹�������\n";
        call_other(JINYONG, "shout_message", msg );     
        destruct(this_object()); 
    } else
    {       
        command("say ��λ" + RANK_D->query_respect(me) + 
                "������ң���Ҳ��ν��һ����ʦ�ˣ������ְ���Ӧ����һϯ��");
        command("say ���µ����鷳�ɽ���������ˡ�");

        message_vision(HIW"\nֻ��$N˵���Ҵ�ææ���뿪����̨��\n\n"NOR,
                    this_object());        
        call_other(__DIR__"jinyong", "set_tishen", me); 
        destruct(this_object());           
    }   
} 


void lost()
{
    object me, jy, ob;
    string msg;
    
    if (! objectp(me = query_competitor())) return; 

    ob = this_object();    
    jy = find_object(JINYONG);
    if ( ! jy ) jy = load_object(JINYONG); 



    message_vision (HIC"ֻ���������ָ��$Nһָ��$N��ʱ�ָ��˾���\n"NOR,me);
    me->set("eff_qi",me->query("max_qi")); 
    me->set("eff_jing",me->query("max_jing"));               
    me->set("qi",me->query("eff_qi"));
    me->set("jing",me->query("eff_jing")); 
    me->set("neili",me->query("max_neili")); 
    me->clear_condition("poison");


    msg = "���α�����ս��"NOR HIR+ me->name() + NOR HIY"սʤ������"NOR HIR+ 
           ob->name() + NOR HIY"��\n";
    call_other(JINYONG, "shout_message", msg ); 

    me->add_temp("leitai/level",1);    

    if ( query("level") >= 5 )
    {
        command("say ��λ" + RANK_D->query_respect(me) + 
                "���շǷ�����������ķ��ڷ�����������֮ͨ������ʱ�������ˡ�");
        command("say ���µ����鷳�ɽ���������ˡ�");  

        message_vision(HIW"\nֻ��$N˵���Ҵ�ææ���뿪����̨��\n\n"NOR,
                    this_object());        
        call_other(__DIR__"jinyong", "set_tishen", me);    
        destruct(this_object());  
    }  
    else
    {
        command("say ��λ" + RANK_D->query_respect(me) + 
                "���շǷ�����������ķ��ڷ���������ready������ս��һλ���ְɡ�");       
        me->set_temp("leitai/prepare", 1);   
        disappear();          
    }
   
} 
void do_disappear()
{
     if (query("born_time") && time() - query("born_time") > 300 )  
     {        
         message_vision(HIG"\n$NͻȻ˵�����������е㼱��Ҫȥ�죬���޵��»������ɡ�\n"
                       "$N˵��Ҵ�ææ���뿪����̨��\n\n"NOR, this_object());  
         destruct(this_object());
     }
}


void disappear()
{
     message_vision(HIW"\nֻ��$N�Ҵ�ææ���뿪����̨��\n\n"NOR,
                    this_object());  
     destruct(this_object());
}
