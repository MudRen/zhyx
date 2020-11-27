//modified by vikee for xlqy-zq station
//2000-12-2 1:34

inherit NPC;
#include <ansi.h>
int start_job(object me);

string *list=({"yg-baituo","yg-duan","yg-emei","yg-gaibang","yg-gumu",
								"yg-honghua","yg-hu","yg-huashan","yg-jueqing","yg-kunlun",
								"yg-lingxiao", "yg-mingjiao","yg-murong",	"yg-shang",
								"yg-shaolin","yg-shenlong","yg-taohua","yg-tiezhang",
								"yg-wudang","yg-wudu","yg-xiaoyao","yg-xingxiu","yg-xuanming",
								"yg-xuedao","yg-xueshan",
	});

int work_me();
int cancel_me();
 
void create()
{
 
	set_name("��ս��ʹ", ({ "da shi" }) );
	set("gender", "����" );
	set("long", "��ս������ռ�BOSS��\n");
	set("age",999);
	set("title", HIW"һ�м���" NOR);
	set("class", "xian");
	set("attitude", "heroism");
	set("age", 18);
	set("str", 20);
	set("int", 30);
	set("con", 30);
	set("dex", 20);
	set("per", 28);
	set("combat_exp", 100);
	set("max_qi", 100);
	set("max_jing", 100);
	set("neili",100);
	set("max_neili",100);
	set("chat_chance",1);
	set("chat_msg", ({
		    name()+"˵������λ����Ը�������ս����\n",
		    }));

        seteuid(getuid());

	set("inquiry", ([
	"kill": (: work_me :),
	"����": (: cancel_me :),
	"fangqi": (: cancel_me :),
	]));

	setup();
}

//this funtion is modified by vikee 2000-11-20 1:32
int cancel_me()
{	object ghost,me=this_player();
//this modi by cnd delete here if for bug
	if(!me->query("mieyao/time_start")||
	   me->query("mieyao/time_start")+1800<time() ||
	   me->query("mieyao/time_start")>time() ||
	   me->query("mieyao/done")||
	   !me->query_temp("mieyao/ob"))
	   
	{
	   command("bite");
	   command("say ��û��������������ʲô���֣�\n");
        me->delete_temp("mieyao/ob");
         me->delete_temp("mieyao/name");
         me->set_temp("mieyao/level",1);
         me->set("mieyao/done",1);
	   return 1;
       }
	ghost=me->query_temp("mieyao/ob");
	if (!living(ghost))
	{
	   command("say "+ghost->query("name")+"�Ѿ�����!\n");
	   return 1;
        }
	me->delete_temp("mieyao/ob");
// ɾ����սnpc����
	me->delete_temp("mieyao/name");
	me->delete_temp("mieyao/time_start");
	//��������������,��ǰ��level�ӵ�һ����ʼ.
	me->set_temp("mieyao/level",1);
	command("shrug");
	command("say ���Ȼ�����շ�"+ghost->query("name")+", ֻ������ȥ�ˡ�\n");
	me->set("mieyao/done",1);

	destruct(ghost);
	return 1;
}
 
int work_me()
{
    object me;
	int t, lvl;
	me=this_player();

	if(!me->query("mieyao")) {
		start_job(me);
		return 1;
	}
	if( (t=(int)me->query("mieyao/time_start")) &&
		!me->query("mieyao/done")) {

	    if(t<=time() &&
		    time()<t+1800) {
		command("heng");
		command(
 		  "say �Ϸ�������ȥ����"+me->query("mieyao/name")
		  +"��\n");
		return 1;
	    }
	    // here is modified by vikee for the #9 ask li about kill 's bug
	    // or the #8 {u;ask li about kill;d}'s bug,
	    // set a flag "mieyao/level_change" to judge the monster level.
	    
	    if(!me->query_temp("mieyao/level_changed")) {
		lvl=me->query_temp("mieyao/level");
		if(lvl>0) lvl--;
		me->set_temp("mieyao/level",lvl);
		me->set_temp("mieyao/level_changed",1);
	    }
	    // allow ask again.
	} else { // job done
	    if(t<=time() && !wizardp(me) &&
                    time()<t+40) {
		message_vision("$N����������һ����˵"+
			"����λ"+RANK_D->query_respect(me)
			+",������ѷ������,������ȥЪϢ��\n",
			this_object(), me);
		return 1;
	    }
	    // succeed, increase lvl.
	    if(!me->query_temp("mieyao/level_changed")) {
		lvl=me->query_temp("mieyao/level");
		if(lvl<11) lvl++; // total 10 levels: 0, ..., 9
		else
		    lvl=1; // reach the top level, reduce difficulty.
		me->set_temp("mieyao/level",lvl);
		me->set_temp("mieyao/level_changed",1);
	    }
	}
	me->delete("mieyao/time_start");
	call_out("start_job", 1, me);
	return 1;
}
int start_job(object me)
{	
	
	string place;
	object ghost;
	int lvl;
 
	if(environment(me)!=environment()) return 1;
	if(me->query("mieyao/time_start")) return 1;
	me->delete("mieyao/done");
	me->set_temp("mieyao/level_changed",0);

	// determine levels.
	// use temp mark, if quit, then start over.
				lvl=me->query_temp("mieyao/level");
	
        ghost = new(__DIR__+list[random(sizeof(list))]);
        NPC_D->place_npc(ghost);
        NPC_D->random_move(ghost);
        NPC_D->random_move(ghost);
        NPC_D->random_move(ghost);
        place = ghost->query("place");    
        ghost->invocation(me, lvl);
		message_vision("$N��$n˵��������"+ghost->name()+"��"+place+"һ�������Ϊ�����ս�ߣ�"
		+"����ȥ������\n"
		,this_object(),me);
	me->set("mieyao/time_start", time());
	me->set("mieyao/name",ghost->query("name"));
	me->set_temp("mieyao/ob",ghost);
	return 1;
}

