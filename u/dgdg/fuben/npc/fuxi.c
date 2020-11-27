#include <ansi.h>
inherit NPC;

void random_move();

string *gifts = ({
        "/clone/fam/pill/neili2", 
        "/clone/fam/pill/puti4", 
        "/clone/fam/pill/sheli4", 
        "/clone/fam/pill/neili2", 
        "/clone/fam/pill/puti4", 
        "/clone/fam/pill/sheli4", 
        "/clone/fam/pill/xuelian4",         
        "/clone/fam/pill/renshen4", 
        "/clone/fam/pill/lingzhi4", 
        "/clone/fam/pill/puti4", 
        "/clone/fam/pill/sheli4", 
        "/clone/fam/pill/xuelian4",         
        "/clone/fam/pill/renshen4", 
        "/clone/fam/pill/lingzhi4",       
        "/clone/fam/gift/int3", 
        "/clone/fam/gift/con3",   
        "/clone/fam/gift/int3", 
        "/clone/fam/gift/con3", 
        "/clone/fam/gift/str3", 
        "/clone/fam/gift/dex3",                                                 
        "/clone/fam/pill/yulu", 
        "/u/dgdg/fuben/obj/magic_item/shennongding.c",
         "/clone/fam/pill/puti4", 
        "/clone/fam/pill/sheli4", 
        "/clone/fam/pill/xuelian4",         
        "/clone/fam/pill/renshen4", 
        "/clone/fam/pill/lingzhi4",       
        "/clone/fam/gift/int3", 
        "/clone/fam/gift/con3", 
        "/u/dgdg/fuben/obj/magic_item/fuxiqin.c",
        "/u/dgdg/fuben/obj/wudaosheli.c",
        "/clone/fam/max/naobaijin",
         "/clone/fam/pill/xuelian4",         
        "/clone/fam/pill/renshen4", 
        "/clone/fam/pill/lingzhi4",       
        "/clone/fam/gift/int3", 
        "/clone/fam/gift/con3", 
       
});


void create()
{
        set_name("������", ({ "fuxi shi","fuxi" }) );
        set("nickname", HIW "������ʦ" NOR);
        set("title", HIC "�׻�����" NOR);
        set("gender", "����" );
        set("age", 200);
        set("long", HIC "����һ�������������ߣ����ú׷�ͯ�գ�\n"
                        "���������ŷ����١�������׻�������֮һ��\n"
                        "�ųơ�" HIR "������ʦ" HIC "�������ϡ�"
                        "\n" NOR);

        set("attitude", "friendly");        
        set("max_jing", 100000);
        set("max_qi", 100000);
        set("max_jingli", 100000);
        set("jingli", 100000);
        set("max_neili", 100000);
        set("neili", 100000);
        set("jiali", 500);
        set("str", 150);
        set("int", 150);
        set("con", 150);
        set("dex", 150);
        set("combat_exp", 200000000);
        set("no_get_from",1);
        
         set_skill("surge-force",500);
        set_skill("dodge", 444);
        set_skill("zhuangzi-wu",500);
        set_skill("unarmed", 400);
        set_skill("force", 550);
        set_skill("parry", 444);
        set_skill("qiankun-danuoyi",500);
        set_skill("sword", 50); 
        set_skill("hand", 400);
        set_skill("strike",500);
        set_skill("taiji-jian",500);
        set_skill("xianglong-zhang",500);
        set_skill("finger", 400);
        set_skill("liumai-shenjian", 400);
        set_skill("qianzhu-wandushou", 400);
        set_skill("sad-strike",500);
        set_skill("xuantie-jian",400);
        
        set_skill("martial-cognize",500);
        set_skill("lamaism",400);
        set_skill("jingluo-xue",400);
        set_skill("literate", 400);
        set_skill("taoism", 400);
      	set_skill("count", 150);
        set_skill("buddhism", 400);
        set_skill("shaolin-yishu", 2000);
        set_skill("idle-force", 850);
        set_skill("poison", 400);
        set_skill("medical", 850);
       
       
        
       
        map_skill("sword","xuantie-jian");
        map_skill("strike","xianglong-zhang");
        map_skill("unarmed", "sad-strike");
        map_skill("force", "surge-force");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("finger", "liumai-shenjian");
        map_skill("medical", "shaolin-yishu");
		
	set_temp("apply/damage", 400);
	set_temp("apply/unarmed_damage", 300);
        set_temp("apply/armor", 1000);
        set("apply/dodge", 200); 

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({ (: random_move :) }));
                set("born_time", time());
                keep_heart_beat();
        }  
        
        
set("coagents", ({
                ([ "startroom" : "/u/dgdg/fuben/room/sncave",
                   "id"        : "shennong dizi" ]),
                
        }));


        prepare_skill("unarmed", "sad-strike");

        create_family("��Ĺ��", 0, "����̩��");

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({               
          
          
          
              	(: perform_action, "unarmed.jingtao" :),  
                (: exert_function, "recover" :),
           //     (: exert_function, "powerup" :),
                 // (: exert_function, "roar" :),
                 
                 
 }) );
        setup();

       
       if (random(100)==1) 
       	{ carry_object("u/dgdg/fuben/obj/magic_item/donghuangzhong")->wear(); }
       else carry_object("d/city/obj/cloth")->wear(); 
       
    //   carry_object("u/dgdg/fuben/obj/magic_item/donghuangzhong")->wear();
       
       
       if (random(10)==1) carry_object("/clone/fam/pill/neili2");
       if (random(10)==1) carry_object("/clone/fam/pill/lingzhi4");
       if (random(10)==1) carry_object("/clone/fam/pill/puti4");
       if (random(10)==1) carry_object("/clone/fam/pill/sheli4"); 
       if (random(10)==1) carry_object("/clone/fam/pill/xuelian4");         
       if (random(10)==1) carry_object("/clone/fam/pill/renshen4");     
       if (random(10)==1) carry_object("/clone/fam/gift/int3");
       if (random(10)==1) carry_object("/clone/fam/gift/con3");
       if (random(10)==1) carry_object("/clone/fam/gift/str3");
       if (random(10)==1) carry_object("/clone/fam/gift/dex3");
       if (random(10)==1) carry_object("/clone/fam/pill/yulu");
       	
       if (random(30)==1) carry_object("/u/dgdg/fuben/obj/magic_item/fuxiqin.c");
       if (random(30)==1) carry_object("/u/dgdg/fuben/obj/wudaosheli.c");
       if (random(100)==1)  carry_object("u/dgdg/fuben/obj/magic_item/shennongding");
       if (random(30)==1) carry_object("/clone/fam/max/naobaijin"); 
       if (random(30)==1) carry_object("/u/dgdg/fuben/obj/meirong wan.c");
       if (random(30)==1) carry_object("/u/dgdg/fuben/obj/meirong shenwan.c");
       if (random(30)==1) carry_object("/u/dgdg/fuben/obj/xiaomeirongwan.c");

       if (random(500)==1) carry_object("/clone/tattoo/zs_spcs1.c");
       if (random(500)==1) carry_object("/clone/tattoo/zs_spcs2.c");
       if (random(500)==1) carry_object("/clone/tattoo/zs_spcs3.c");
       if (random(500)==1) carry_object("/clone/tattoo/zs_spcs4.c");
       if (random(500)==1) carry_object("/clone/tattoo/zs_spcs5.c");
       if (random(500)==1) carry_object("/clone/tattoo/zs_spcs6.c");
       if (random(500)==1) carry_object("/clone/tattoo/zs_spcs7.c");
      
}


             void init() 
        { 
                object ob = this_player();         
                ::init(); 
       
                if (interactive(ob)) 
                { 
                        remove_call_out("kill_ob"); 
                        call_out("kill_ob", 1, ob);  
                }        
        }  

greeting(object ob)
{
     object me;
     me=this_player();
     if (!ob || !present(ob, environment())) return;
     command("look " + me->query("id"));
     command("say ������Ե����������ᣬ��Ӯ�Ҿ��ܵõ��ҵı��");     
     return ;
}

void random_move()
{
	if (time() - query("born_time") > 7200)
	{
		message_vision("$N����ææ�����ˡ�\n", this_object());
		destruct(this_object());
		return;
	}
        NPC_D->random_move(this_object());
}

int accept_kill(object ob)

{    
	
	if (ob->query("reborn")==1) 
		{  if (ob->query_skill("force",1)>=450||ob->query_skill("dodge",1)>=450||ob->query_skill("parry",1)>=450||ob->query_skill("sword",1)>=450||ob->query_skill("unarmed",1)>=450||ob->query_skill("martial-cognize",1)>=450)
			{ write("���书��ôǿ���ѻ����������˰�\n");
			 return -1;
			}
		}
		
	if (ob->query_skill("force",1)>=550||ob->query_skill("dodge",1)>=550||ob->query_skill("parry",1)>=550||ob->query_skill("sword",1)>=550||ob->query_skill("unarmed",1)>=550||ob->query_skill("martial-cognize",1)>=550)
	
		{
			write("���书��ôǿ���ѻ����������˰�\n");
			return -1;
		} 
		
		if (is_fighting())
        {
                message_vision(CYN "$N" CYN "��$n" CYN "�е������ȱ�"
                               "���Ҵ�����ܾ��������ġ�\n" NOR,
                               this_object(), ob);
                return -1;
        }     

         if (query_temp("fight_cd")>0||
        	  query("qi") < 60000 ||
            query("jing") < 60000 ||
            query("neili") < 60000)
        {
                message_vision(CYN "$N" CYN "ҡҡͷ��$n" CYN "��������"
                               "��̫���ˣ�����Ъ�����˵�ɡ�\n" NOR,
                               this_object(), ob);
                return -1;
        }
	
		
	message_vision(CYN "$N" CYN "��$n" CYN "��У������ë���������ҵı���!\n" NOR,this_object(),ob);
//	competition_with(ob);
	 this_object()->set_temp("fight_cd",20);
  this_object()->start_call_out((: call_other, __FILE__, "fight_cdend",this_object(), 20 :), 20); 


	kill_ob(ob);
	return 1;
}



 void fight_cdend(object me, int amount) 
      { 
         /*     if ((int)me->query_temp("fight_cd")) 
              { 
                      me->add_temp("apply/attack", -(amount * 2 / 5)); 
                     me->add_temp("apply/defense", -(amount * 2 / 5)); 
                     if (me->query("reborn")) 
                      { 
                              me->add_temp("apply/whip", -(amount / 6)); 
                              me->add_temp("apply/club", -(amount / 6)); 
                             me->add_temp("apply/sword", -(amount / 6)); 
                              me->add_temp("apply/blade", -(amount / 6)); 
                              me->add_temp("apply/staff", -(amount / 6)); 
                              me->add_temp("apply/hammer", -(amount / 6)); 
                              me->add_temp("apply/dragger", -(amount / 6)); 
                  */
                  
         me->add_temp("fight_cd",-20);                      
                              
}
/*
int accept_fight(object ob)
{	
	
	if (ob->query_skill("force",1)>=500||ob->query_skill("dodge",1)>=500||ob->query_skill("parry",1)>=500||ob->query_skill("sword",1)>=500||ob->query_skill("unarmed",1)>=500)
	
		{write("���书��ôǿ���ѻ����������˰�\n");
			return 0;
		} 
	
       if (is_fighting())
        {
                message_vision(CYN "$N" CYN "��$n" CYN "�е������ȱ�"
                               "���Ҵ�����ܾ��������ġ�\n" NOR,
                               this_object(), ob);
                return -1;
        }     

        if (query("qi") < 20000 ||
            query("jing") < 20000 ||
            query("neili") < 20000)
        {
                message_vision(CYN "$N" CYN "ҡҡͷ��$n" CYN "��������"
                               "��̫���ˣ�����Ъ�����˵�ɡ�\n" NOR,
                               this_object(), ob);
                return -1;
        }
       
        message_vision(HIW "$N" HIW "��ϲ�����úúã�����������������"
                       "���Ȼ��Ȼ���\n" NOR, this_object(), ob);
       
        competition_with(ob);
        return -1;
}


void win()
{
        object ob;
        if (! objectp(ob = query_competitor()))
                return;

        message_vision(CYN "$N" CYN "���˿�$n" CYN "���ٺ�Ц�������ˮ"
                       "ƽ̫���ˣ�Ҫ�ú��������ú�������\n" NOR,
                       this_object(), ob);
        ::win();
}

 void lost()
{
  
	object me,ob;
	string gift;
 
         if (! objectp(me = query_competitor()))
                return; 
                
        gift = gifts[random(sizeof(gifts))];
        ob = new(gift);
        if (! objectp(ob))
        {
        	write(HIR "��� " + gift + " ���Ƴ���\n" NOR);
        }
        else
        {
                write(HIG "��õ��˷����ű�" + ob->name() + HIG + " ��\n" NOR);
                ob->move(me, 1);
        }


        
        ::lost();
} 



void unconcious()
{
        say( HIC"����˵�����������û��ô���ס���˵��ʹӻ����ó�һ�����������������������������\n"NOR);
        say( HIC"Ƭ��֮�䣬��ũ�ָֻ��˾��񣬡��ٺ١���Ц��������\n"NOR);
        revive();
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
	remove_all_enemy(1);
	lost();
 }  


void die()
{
	unconcious(); 

	
} */