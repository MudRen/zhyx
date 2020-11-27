// Code of JHSH

#include <ansi.h>
#include "mingjiao_job.h"

inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;

string ask_job();
int get_jingtie_num();
string ask_jingtie();
string ask_jingtie_num();
void dest_ob(object);

void create()
{
        set_name("�⾢��", ({ "wu jincao","wu"}) );
	set("long",
        "����һλ����ȥ�ܾ��ɵ��������ӣ���һ���ײ����ۡ�\n"
        "���������������е���ͷ����������򲻵�֮�£�����һ���������ݵĺ��ӡ�\n"
	);
        set("title", HIG "����" HIW "�����" NOR "���츱ʹ");
	set("gender", "����");
	set("attitude", "friendly");
        set("class", "fighter");

        set("age", 42);
	set("shen_type", 1);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);
	set("max_qi", 1000);
	set("max_jing", 1000);
	set("neili", 1000);
	set("max_neili", 1000);
	set("jiali", 100);
	set("combat_exp", 100000);
	set("score", 5000);

	set_skill("force", 85);
	set_skill("hunyuan-yiqi", 85);
	set_skill("dodge", 85);
	set_skill("shaolin-shenfa", 85);
	set_skill("cuff", 95);
	set_skill("jingang-quan", 95);
	set_skill("parry", 85);
	set_skill("buddhism", 85);
	set_skill("literate", 85);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("cuff", "jingang-quan");
	map_skill("parry", "jingang-quan");

	prepare_skill("cuff", "jingang-quan");
        create_family("����", 37, "��������츱ʹ");
        

	set("inquiry", ([
		"name" : "���¾���������������츱ʹ�⾢�ݣ���֪�����к�ָ�̡�",
		"����" : (: ask_job :),
		"datie": (: ask_job :),
		"��������" : (: ask_jingtie_num :),
		"reserve"  : (: ask_jingtie_num :),
		"����" : (: ask_jingtie :),
		"jingtie" : (: ask_jingtie :),
	]));

        setup();

        carry_object("/d/mingjiao/obj/langyabang")->wield();
        carry_object("/d/mingjiao/obj/baipao")->wear();

}

string ask_job()
{
     object player=this_player();
     mapping fam ;
     object ling,chui,qiao;

    if (!(fam = this_player()->query("family")) || fam["family_name"] != "����")
        return "��λ"+RANK_D->query_respect(player)+"�����ҽ̵��֣��Ǹ������Ǹҷ��ɸ���ʲô�����ء�\n";

	if (fam["generation"] <37)
		 return "��λ"+RANK_D->query_respect(player)+"���������е�λ�ĸߣ�����ͷ���ܡ�\n";

	if(player->query("mingjiao/job") != "jin_caikuang")
		return judge_jobmsg(player,0);

	if( !present("wujin kuangshi",player ) )
		return "�㲢δ������ʯ����δ�����\n";

	qiao=present("tie qiao",player );
	if (qiao) destruct(qiao);
	tell_object(player,"������½����⾢�ݡ�\n\n");	

	command("nod "+player->query("id"));

	chui=new(OBJ_PATH"/tiechui");
	chui->move(player);
	tell_object(player,"�⾢�ݸ���һ��������\n");
	
	return "�ã���ȥ�Ѳ����Ŀ�ʯ���ɾ����ɡ�\n";
}   

int accept_object(object me, object ob)
{
	string name;
	string job_flg;
	object room,tool;


	name = ob->query("id");	
	if ( name != "jing tie")
		return 0;

	job_flg = judge_jobmsg(me,1);

	if ( job_flg !=  "�ɼ�����" ) 
	{
		command("hmm "+me->query("id"));
		command("say û����������Ͳ�Ҫ���ҿ��ɣ�");
		return 0;
	}
	else
	{
		command("thumb "+this_player()->query("id"));
		command("say ��λ�ֵ�������!��ȥ�ú���Ϣ��Ϣ��");
	        tool=present("tie chui",me );
		if (tool) destruct(tool);
		remove_call_out("dest_ob");
		call_out("dest_ob",1,ob);
	        if (!(room = find_object("/d/mingjiao/mj_center.c")))
			room = load_object("/d/mingjiao/mj_center.c");
		room->add("jingtie",1);
		call_out("reward",0,this_player(),job_flg);
		return 1;
	}
	
	return 0;

}


int get_jingtie_num()
{
        int num;
        object room;
        
        if (!(room = find_object("/d/mingjiao/mj_center.c")))
		room = load_object("/d/mingjiao/mj_center.c");
        num = room->query("jingtie");

	return num;

}

string ask_jingtie_num()
{
	return "���ڻ���"+chinese_number(get_jingtie_num())+"�龫����\n";
}

string ask_jingtie()
{
	int num;
	object me=this_player();
	object jingtie,room;
	string job_flg;

	job_flg = judge_jobmsg(me,1);
	if (job_flg != "�����ǹ")
		return "��λ"+RANK_D->query_respect(me)+"����û�����ǹ������ɡ�\n";
	
	if (present("jing tie",me) )
	{
		command("hmm "+me->query("id"));
		return "�㲻���Ѿ���һ�����𣿻���Ҫ������̰�����ᡣ\n";
	}

	if ( get_jingtie_num() <= 0 )
		return "�Բ����������Ѿ�û�о����ˡ�\n";

	command("nod "+me->query("id"));
	message_vision("�⾢������һ�龫����$N\n",me);
        if (!(room = find_object("/d/mingjiao/mj_center.c")))
		room = load_object("/d/mingjiao/mj_center.c");
	room->add("jingtie",-1);

	jingtie=new(OBJ_PATH"/jingtie");
	jingtie->move(me);

	return "�����ֵ�����������������ľ�������Ҫ�����úô��������\n";
}

void dest_ob(object ob) { destruct(ob);}
