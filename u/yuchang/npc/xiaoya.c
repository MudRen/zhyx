//creat by wsw 2005 1 20
//wangxy.c
//���Ĵʵ������ˣ���СѾ

#include <ansi.h>

#define FILE 	__DIR__+"kxcd.txt"  //����ļ�����
#define LINES	19000				//����ļ��������
#define TIME	30					//�ش�һ���ʱ�����ƣ��룩

inherit NPC;

string name = HIY"�����Ĵʵ䡿"NOR+HIM"��СѾ"NOR;
int do_start();
int start_chuti();
void announce (string str);
void finish(object who);
int    filter_listener(object ob);
object *listeners ;

void create()
{
                  set_name(HIM"��СѾ"NOR, ({ "tang xiaoya","xiaoya" }));
                  set("shen_type", 1);
				  set("title", HIY"�����Ĵʵ䡿"NOR);
                  set("gender", "Ů��");
                  set("age", 36);
                  set("per",36);
                  set("long",
"���Ǵ��ƿ��Ĵʵ�������ˣ���Ȼ������ϣ����Ƿ����̴档\nֻ���京Ц�紺�ң��񴽺���,����ϸ��,��ȶ��ˣ�
��˵���Ų������������������㣬ʵ���˼��ɫ��\n"
);
                  set("attitude", "friendly");
                  set("inquiry", ([
    "���Ĵʵ�":  WHT"\n���Ĵʵ���һ�����е�������Ϸ��
    	start		��ʼ��Ϸ
    	kxcd		����Լ��ĳɼ�\n"NOR
                  ]));


                  setup();
              carry_object("/d/city/obj/cloth")->wear(); 


}




void init()
{
         add_action("do_start", "start");
         add_action("do_check", "kxcd");
}


int do_start()
{
	object me,who;
	string str;
	
	me = this_object();
	who = this_player();
	
	if (!who) return 1;

	if (time() - who->query_temp("kxcd/last_time")   < 60 ) {
		return notify_fail("��Ҫ������������\n");
	}
	
	if (me->query_temp("kxcd/doing") =="yes")   //���ڽ���
		return notify_fail("��Ҫ����һ��һ������\n");
		
	who->delete("env/no_story");
		
	listeners = filter_array(users(), (: filter_listener :));	
	
	str = name+"��"+HIY+who->query("name")+"("+who->query("id")+")�μӡ����Ĵʵ䡿������\n"+NOR;
	announce (str);
	
	me->set_temp("kxcd/doing","yes");
	
	who->set_temp("kxcd/last_time",time());
	
	
	who->set_temp("kxcd/score",0);//���ֵ÷�
	who->set_temp("kxcd/num",0);//���ִ���
	
	start_chuti();

	return 1;	
}

int start_chuti()
{
	string arg, quest, key_n, key_str, *choose, level;
	int i, k;
	
	object me = this_object();
	object who = this_player();
	
	arg = read_file(FILE,random(LINES),1);
	
	choose = allocate(6);	
	k = sscanf(arg, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\n", quest, key_n, key_str, 
		choose[0],choose[1],choose[2], choose[3], choose[4], choose[5],  level);
	
	arg = quest+"\n";
	for (i=0;i<6;i++) 
		if (sizeof(choose[i]) > 0)  arg += HIR"��"+ (i+1) +"����"NOR+HIW+choose[i];	
	arg += HIR"��"+replace_string(level," ","")+"��"+ "\n"NOR;
	announce (name+HIW+"��"+arg+NOR);
	
	who->set_temp("kxcd/start_time",time());
	
	write(HIG"����30��������ѡ�����֣���\n"NOR);
	input_to("get_num", 1, replace_string(key_n," ",""), replace_string(level," ",""));	
	
	remove_call_out("finish");
    call_out("finish",TIME,who);		
		
	return 1;
	
}

void get_num(string str, string key_n, string level)
{
	object who = this_player();
	float score;
	int time;
	
	remove_call_out("finish");
	
	if (str != key_n) {
		write (HIG+"�ش������ȷ��Ӧ���ǣ�"+key_n+"��\n"NOR);
		finish(who);
		return;			
	}
		
	
	time =TIME - time() + who->query_temp("kxcd/start_time");
	
	if (time<0) {
		write (HIG"�����̫���ˡ�\n"NOR);
		return;
	}
	
	who->add_temp("kxcd/num",1);//���ִ�����1
		
	score = (int)(time/10)*0.5; //ʱ��ӷ�:10����1�֣�20����0.5��30���ڲ��ӷ�
	
	if (level=="�߼�") score += 3;
	else if (level=="�м�") score += 2;
	if (level=="�ͼ�") score += 1;
	
	who->add_temp("kxcd/score",score);//���ֵ÷�
	
	write(HIG"�ش���ȷ���÷֣�"+sprintf("%1.1f",score)+"��\n"NOR);
		
	//start_chuti();
	remove_call_out("start_chuti");
    call_out("start_chuti",1);
    
    return;
			

}


void finish(object who)
{
	string str;
	
	this_object()->delete_temp("kxcd");
	if (!who->query_temp("kxcd/num")) return;
	
	//����÷�
	str =  name+HIW+"��"+who->query("name")+"���ش���ȷ��"+chinese_number(who->query_temp("kxcd/num"))+"���⣬�����"
		+sprintf("%3.1f",who->query_temp("kxcd/score")) +"�֡�\n";
		
	announce(str);
	
	who->add("kxcd/num",1); 
	if (who->query_temp("kxcd/score") > who->query("kxcd/score"))
		who->set("kxcd/score",who->query_temp("kxcd/score"));
		
	who->delete_temp("kxcd");//������μ�¼
	who->set_temp("kxcd/last_time",time()+60); //һ�������ڲ��òμ�
	
	return;
		
	
}

int do_check()
{
	string str;
	object who = this_player();
	
	if ( who->query("kxcd/score")) 
		str= "�㹲�μ���"+	chinese_number(who->query("kxcd/num"))+"�β��ԣ���߷�Ϊ"+
			sprintf("%3.1f",who->query("kxcd/score"))+"�֡�\n";
	else str = "�㻹û�вμӹ����Ĵʵ���ԡ�\n";
	write(HIG+str+NOR);
	return 1;
}

void announce (string str)
{
  //command_function ("chat "+str);
  //tell_room(environment(this_object()),str);
  message("story", str, listeners);
}

int filter_listener(object ob)
{
        if (ob->query("env/no_story")) return 0;
        return 1;
}