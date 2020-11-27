// Code of ShenZhou
//Kane
// mantian Bug fix may/11/2001

#include <room.h>
#include <ansi.h>

inherit ROOM;

int do_pigua();
void create()
{
	set("short", "������");
	set("long", @LONG
�˶����ϱ�������֮������С���������겻�����⡣����ֵ��Ƕ���ʮ�ָ��
Ҳû��ʲô����������(wall)����һЩģģ���������Σ����˻���֮״��������
������һЩ������ѧͼ�⡣
LONG
	);
	set("item_desc", ([
		"wall" : " ������ʮ�������Σ����ݸ߷��ͣ����ƴ�����ÿһ�������Ų�ָͬ����\n"
                         "��Ϊ�鶯���ƺ����һ�����һ��������ѧ���������ʽ��\n",
		]));
	set("exits", ([
		"out" : __DIR__"tzfeng",
		]));
	setup();
}

void init()
{
	add_action("do_tanzhi","tanzhi");
	add_action("do_use","use");
}

int do_use(string arg)
{
	object me = this_player();

	if( !arg || arg=="" ) return 0;
	if (!present("fire", me))  return 0;
	if( arg=="fire" )
	{
		write("���Ż��ӳ�գ����������ȥ��\n");
		me->move(__DIR__"neidong");
	}
	return 1;
}

int do_tanzhi()                
{
	object me, ob, *inv; 
	int check,i;

	me = this_player();
	ob = present("tie bagua", me);

	if (!ob) 
		return notify_fail("�㿴��ͼ��ѧ����ָ�ҵ������������ָ������ʹ��ɶ��û���֡�\n");

	if (me->query("jing") <30) 
		return notify_fail("��ľ����޷����С�\n");

	if ( (int)me->query_skill("finger", 1) >= 50 && 
             (int)me->query_skill("finger", 1) <= 200 &&
             ob )
	{
		check = (int)me->query_skill("finger",1);
		check *= check;
		check *= check;
		if ( check < (int)me->query("combat_exp")*10)
		{
			me->recieve_damage("jing",15+random(15));
			me->improve_skill("finger", me->query("int")*2);
			write(CYN"����ָ���������ϵ�����ȥ��\n"NOR);
			write("�������˻���ָ������ļ������ѡ�\n");
		}
		else
		{
			write ("��ʵս���鲻�㣬�޷��������ָ����\n");
		}	
	} 
	else if ( (int)me->query_skill("finger", 1) > 200 )
	{
		write(HIC"ֻ�������һ���������Է���һ������\n"NOR);
	}	  
	else
	{
		write(HIC"�����������ʹ�ϳ��̵ľ�����һ���������ָ�۵ĸ�����һ����\n"NOR);
	} 
	return 1;
}