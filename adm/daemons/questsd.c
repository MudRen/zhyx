// quests.c
// creat by wsw 05/10/15
// �����ܹܣ�������������Ľ���ϵ��



#include <ansi.h>

#define X_TIMES 	1800 //����ʱ�䣬��λΪ��
#define X_MIN 		300 //��С����ϵ��
#define X_MAX 		5000 //������ϵ��

inherit F_DBASE;
inherit F_SAVE;

int add_quest(string quest,int n);
int query_quest_x(string quest);
void announce_x();
mapping quest_x(mapping quest_sum);
void calculate_x();


nosave mapping quests = ([ //�����б� ����ɡ�ץ����ʫ���
//1.lijing 2.xue �ӷ����� 3.9mi 4.rulai 5.����ɱ�� 6�������� 7�� 8����

   "li"		:	"�л���ս",
  // "jiumi"	:	"��������",
  // "menpai1":	"����Ѱ��",
  // "menpai2":	"��������",
  // "zhongkui":	"��ظץ��",
  // "kaifeng":	"��������",
  ]);
nosave mapping level = ([ //�Ѷ�ϵ��

   "li"		:	1,
  // "jiumi"	:	10,
  // "menpai1":	1,
  // "menpai2":	1,
  // "zhongkui":	1,
  // "kaifeng":	"��������",
  ]);

void create()
{
    	seteuid(getuid());
    	set("name", "�����ܹ�");
   	 	set("id", "quests");
        restore();

        remove_call_out("calculate_x");
        call_out("calculate_x",1);
        remove_call_out("announce_x");
        call_out("announce_x",10);
}

void announce_x() //����������ϵ��
{
    string *klist,str;
    int i;
    object me = this_object();

	klist = keys(quests);
	str = HIR"���л�����"+HIW"�˷���:װ��������������ϣ�\n";
	for(i=0; i<sizeof(klist); i++) {
    	str +=HIW+"��"+quests[klist[i]] + "��:���ҵ����������¥��װ������������װ��ϵͳ��\n";
    }
    str += NOR;

  	message("sys",str,users());

  	 remove_call_out("announce_x");
     call_out("announce_x",600); //ÿ10���ӷ���һ��
}

void calculate_x() //����������ϵ��
{
	string *klist,str;
	int sum,x,i;
	mapping a1,a2,a3,a;
    object me = this_object();

	klist = keys(quests);

	a1 = quest_x(me->query("quest_a1"));
	a2 = quest_x(me->query("quest_a2"));
	a3 = quest_x(me->query("quest_a3"));
	a = quest_x(me->query("quest_sum"));

	me->set_temp("quest_a1",a);

	for(i=0; i<sizeof(klist); i++) {
		me->set("quest_x/"+klist[i],to_int(a1[klist[i]]*0.4+
			a2[klist[i]]*0.3+a3[klist[i]]*0.2+a[klist[i]]*0.1));
	}

	//����
	sum = 0;
	for(i=0; i<sizeof(klist); i++) {
		sum += me->query("quest_x/"+klist[i]);
	}

	sum = (sum-sizeof(klist)*1000)/sizeof(klist);
	for(i=0; i<sizeof(klist); i++) {
		x = me->query("quest_x/"+klist[i])-sum;
		if (x < X_MIN) x = X_MIN;
		if (x > X_MAX) x = X_MAX;
		me->set("quest_x/"+klist[i],x);
	}
	//��������

	me->save();

  	 remove_call_out("calculate_x");
     call_out("calculate_x",600); //ÿ10���Ӽ���һ��
}


int add_quest(string quest,int n) //ÿ���һ����������n�㣬һ��Ϊ1��questΪ������룬����������
{
	int i;
	object me = this_object();
	//���������б��еĲ�����
	string *klist = keys(quests);
	if (member_array(quest,klist) == -1)
		return 0;
	//"quest_a"��¼һ��ʱ�������������� ��һ��ʱ���Ժ����㡣
	//"quest_a1"Ϊ��һʱ��ε������������
	//"quest_a2"Ϊ����һʱ��ε������������
	//"quest_a3"Ϊ������һʱ��ε������������
	if (time() - me->query("quest_a/times") > X_TIMES ) {
		me->set("quest_a3",me->query("quest_a2"));
		me->set("quest_a2",me->query("quest_a1"));
		me->set("quest_a1",me->query("quest_a"));
		me->delete("quest_a");
		me->set("quest_a/times",time());
	}
	//��λʱ�������������
	me->add("quest_a/"+quest,n);
	//���������������
	me->add("quest_sum/"+quest,n);
	me->save();
	return 1;
}
int query_quest_x(string quest) //��ѯ����ǰ����ϵ������ϵ���Ŵ�1000����ʵ�ʼ���ʱҪ����1000��
{
	int quest_x;
	//return 1000; //������
	quest_x = this_object()->query("quest_x/"+quest);
	if (!quest_x) quest_x = 1000;
	return quest_x;
}

mapping quest_x(mapping quest_sum)
{
	string *klist;
	int i,sum,x;
	mapping quest_x;
	quest_x=allocate_mapping(100);
	klist = keys(quests);
	klist = sort_array(klist, "sort_keys", this_object());

	if (sizeof(klist) <= 1 || !mapp(quest_sum)) {//ֻ��һ�����Ͳ��ü�����
  	 	for(i=0; i<sizeof(klist); i++) {
  	 		quest_x[klist[i]]=1000;
  	 	}
		return quest_x;
	}
	sum = 0;
	for(i=0; i<sizeof(klist); i++) {
		sum += quest_sum[klist[i]]*level[klist[i]];
	}
	if (sum == 0) {
  	 	for(i=0; i<sizeof(klist); i++) {
  	 		quest_x[klist[i]]=1000;
  	 	}
		return quest_x;
	}
	for(i=0; i<sizeof(klist); i++) {
		x = quest_sum[klist[i]]*level[klist[i]];
		x = 1000 - x + (sum-x)/(sizeof(klist)-1);
		if (x < X_MIN) x = X_MIN;
		if (x > X_MAX) x = X_MAX;
		quest_x[klist[i]]=x;
	}
	return quest_x;
}

string query_save_file() { return DATA_DIR + "npc/quests"; }
