//����2(ת��npc/����ǰ������)

#include <ansi.h>
inherit  NPC;
int ask_recover();
int ask_tu();

void create()
{
        seteuid(getuid());       
        set_name(HIY "����Ĳ��" NOR, ({ "buddha", "fo zu", 
                "fo", "shijia muni" }));
        set("long", @LONG
����ׯ�ϱ������˲������ӡ�
LONG);
        set("nickname", HIW "���編��" NOR);
        set("title", HIC "����" NOR);
        set("gender", "����" );
        set("age", 500);
        set("attitude", "friendly");
        set("max_jing", 99999);
        set("max_qi", 99999);
        set("max_jingli", 99999);
        set("jingli", 99999);
        set("max_neili", 99999);
        set("neili", 99999);
        set("jiali", 9999);
        set("str", 99);
        set("int", 99);
        set("con", 99);
        set("dex", 99);
        set("combat_exp", 99999999);

        set("inquiry", ([ 
            "ǰ��" : (: ask_recover :),
	    "ת��ͼ��": (: ask_tu :),
        ])); 

        set_skill("dodge", 999);
        set_skill("unarmed", 999);
        set_skill("force", 999);
        set_skill("parry", 999);
        set_skill("sword", 999);      
        set_skill("medical", 999);       
        set_skill("literate", 999);
        set_skill("lamaism", 999);
        set_skill("buddhism", 999);  
        set_skill("shaolin-yishu", 999); 
        set_skill("idle-force", 999);
        set_skill("huntian-baojian", 999);
        set_skill("lunhui-jian", 999);
      
        map_skill("force", "huntian-baojian");       
        map_skill("parry", "lunhui-jian");    
        map_skill("sword", "lunhui-jian");     
        map_skill("medical", "shaolin-yishu");   

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),
        }));

        setup();
        carry_object("d/city/obj/jiasha")->wear();
        carry_object("/d/city/obj/changjian")->wield(); 
}





void init()
{
     add_action("do_recall", "recall");
}


int ask_recover()
{    
    object me = this_player();

    command("look " + me->query("id"));
    command("say ������ǰ����Ե��?");    
    command("say ��ɼǵ�ǰ����������˭���Ҹ���Ľ�������ʲô��");
    command("say �����ܴ�������ұ���㿪��ǰ��ȫ�����䡣");

    tell_object(me, HIW"�����������˵����"
                    "�����������˾�����recall <id> <����> \n"NOR);   
    return 1;
}

int do_recall(string arg)
{
    int i, have;
    string id, pass, skills_name;
    mapping special, my_sk;
    object fo, me = this_player();
    have = 0;	

    my_sk = me->query_skills();

    if ( me->query("reborn") )
    {
       command("say ��İ���Үʶ�����Ѿ�������");
       return 1;
    }


    fo  = find_object(__DIR__"buddha");  
    if ( ! fo ) fo = load_object(__DIR__"buddha");  

    if ( ! arg || sscanf(arg, "%s %s", id, pass) != 2 )
	 return notify_fail("�㾿���ǲ��ǵ��Լ�ǰ����˭��\n");   

    for(i = 0; i < sizeof(fo->query("data")); i++)    
       if (keys(fo->query("data"))[i] == id ) have = 1;

    if ( have == 0 ) 
    {
       command("say ����ô���ǵ�ǰ��������Ե�أ�");
       return 1;
    }

    if ( fo->query("data/" + id + "/reborn_time") 
           > me->query("birthday") ) 
    {
       command("say ����ת��֮ʱ���������ϣ�"
               "������ô���ܻ���������Ͷ̥֮����");
       return 1;
    } 

    if ( fo->query("data/" + id + "/pass") != pass ) 
    {        
       command("say ����������Ҹ���Ľ��");
       return 1;
    }


    command("say �������Ȼ��ǰ��������Ե֮�ˣ����ҽ���ǰ������򿪣�");

    message_vision(HIY"\n����˵�ű㳯��$N����һ���֡�\n\n"NOR
                   HIR"$NͻȻ�е�ͷʹ����......\n\n"NOR, me);

    me->set("str", fo->query("data/" + id + "/str"));
    me->set("int", fo->query("data/" + id + "/int"));
    me->set("con", fo->query("data/" + id + "/con"));
    me->set("dex", fo->query("data/" + id + "/dex"));
    me->delete("family");
    me->set("gongxian", 0);
    me->delete("quest");
    me->delete_temp("quest");
    me->set("title", "��ͨ����");
    me->set("combat_exp", 0);       	
    me->set("max_neili",0);
    me->set("neili",0);
    me->set("max_jingli",0);
    me->set("jingli",0);
    me->set("max_qi",100);
    me->set("eff_qi",100);
    me->set("qi",100);
    me->set("max_jing",100);
    me->set("eff_jing",100);
    me->set("jing",100);
    me->set("shen",0);
    me->delete("breakup");
    me->delete("animaout");
    me->set("mud_age",0);            
    me->set("age", 14);
   
    if (fo->query("data/" + id + "/sun"))
        me->set("gift/sun",1);
    if (fo->query("data/" + id + "/water"))
        me->set("gift/water",1);
    if (fo->query("data/" + id + "/feng"))
        me->set("gift/feng",1);
    if (fo->query("data/" + id + "/lighting"))
        me->set("gift/lighting",1);

    special = fo->query("data/" + id + "/special_skill");
 
    me->delete("special_skill");

    for( i = 0; i < sizeof(special); i++)
       me->set("special_skill/" + values(special)[i], 1); 
     
    me->set("reborn", 1);
    me->set("gift/kaizhan",1);
    me->set("gift/bobo/rmb", 0);
    me->set("gift/jindan",2);

    log_file("static/reborn", sprintf("%s(%s) reborn from %s at %s.\n",
             me->name(1), me->query("id"), id, ctime(time())));  

    message("vision", HIG"����紫�š���˵�����ѵ÷�����䣬"
                      "�����˰���Үʶ��\n"NOR, users());
    me->unconcious();

    foreach(skills_name in keys(my_sk))
    {
    me->delete_skill(skills_name);
    }
    me->delete("mark/guofu_ok"); 	 
    me->delete("mark/guofu_over"); 	
    me->delete("mark/guofu_out"); 	

    fo->delete("data/" + id);
    fo->save();   
    return 1;
}

int ask_tu()
{
	command("say �������һ��ʮ�弶������ȡһ��ת��ͼ�ڡ�");
	this_player()->set_temp("want_tu", 1);
	return 1;
}

int accept_object(object me, object ob)
{
	object itm;
	string *tu_list = ({
		"/clone/tattoo/zs_spc1",
		"/clone/tattoo/zs_spc2",
		"/clone/tattoo/zs_spc3",
		"/clone/tattoo/zs_spc4",
		"/clone/tattoo/zs_spc5",
		"/clone/tattoo/zs_spc6",
		"/clone/tattoo/zs_spc7",
        });

	if (me->query("mark/reborn_tattoo"))
	{
		me->delete_temp("want_tu");
		command("say �Ҳ����Ѿ�������ͼ��ô����ô����Ҫ��");
		return 0;
	}

	if (!ob->is_item_make()) return 0;  

	if (ob->item_owner() != me->query("id"))
	{
		command("kick " + me->query("id"));
		command("say ���ֲ�����Ķ�������ʱ����������Ҫ���ֻ���ô�죿");
		return 0;
	}

	if (ob->query("owner/" + me->query("id")) < 44000000 
		||  ob->query("bless") < 30 )
	{
	command("say �������������ü������������������ﻻ������");
	me->delete_temp("want_tu");
	return 0;
	}

/*	if (!ob->query("magic/tessera") || ob->query("magic/blood") < 5)
	{  
		command("say ��ѱ�����û�������������ܻ�ת��ͼ�ڡ�");
		me->delete_temp("want_tu");
		return 0;
	}
*/

	if ( me->query_temp("want_tu") )
	{
		itm = new(tu_list[random(sizeof(tu_list))]);
		itm->move(me);
		command("nod");
		command("say ��Ȼ�������ת��ͼ�ھ͸����ˡ�");
		command("say ���������������Ҿ�û���ˡ�");

		message_vision("$N�ó�һ��"+itm->name()+"��$n��\n\n", 
        	                   this_object(), me);

		log_file("static/rb_special", sprintf("%s(%s) get %s by %s(%s) at %s .\n",
			me->name(1), me->query("id"), itm->name(), ob->name(), ob->query("id"), ctime(time())));


		me->delete_temp("want_tu");
		me->delete("can_summon/" + ob->query("id"));
		me->set("mark/reborn_tattoo",1);
		rm(base_name(ob) + ".c");
		DBASE_D->clear_object(ob);
		return 1;
	}
      return 0;
}
