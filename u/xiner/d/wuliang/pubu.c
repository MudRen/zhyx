// pubu.c 
// Modified by Winder June.25 2000
// Modified by xiner 2009 02 20 to fix zhyx

inherit ROOM;

#include <ansi.h>
void create()
{
	set("short", "����ٲ�");
	set("long", @LONG
ѭС·ֱ����ɽ���������ˮ�����������¡¡�����糱ˮ����
һ�㣬̧ͷһ����ֻ�����������������ӵ�����һ�����ٲ��Ӹ�����ֱ
к���������֮ǰ���ǽ�������������������ȣ�������������������
ͷ����
LONG );
	set("exits", ([ /* sizeof() == 2 */
		"southdown" : "/d/wanjiegu/wlshan",
	]));
	set("no_clean_up", 0);
	setup();
}
 
void init()
{
	add_action("do_jump","jump");
}

int do_jump(string arg)
{
	object ob;
//	int new_jing;
	ob = this_player();
	if (ob->query("reborn") != 1)
		return notify_fail("�㻹���ᣬ��ô����Ҫ������ɱ��\n");
//	new_jing = random( ob->query("max_jing")*3 );
//	if ( new_jing > ob->query("jing") ) new_jing = ob->query("jing") + 1;
        if( !arg || arg=="" ) return 0;
        if( arg != "down" )
		return notify_fail("����Ҫ������ɱ����ô�벻������\n");

	if((int)ob->query_skill("dodge")<200) 
		return notify_fail("���������ʵ����̫���ˣ�������������\n");

	tell_object(ob, HIR"�㲻��˼��������һԾ�����������¡���\n"NOR);

	message("vision", NOR"ֻ��" + ob->query("name") + "�����ң���������������֮�С���\n"NOR, environment(ob), ob);
	if((random((int)ob->query("dex") +(int)ob->query("kar")) < 40 ))
	{
		ob->unconcious();      
		ob->receive_wound("qi", (int)(ob->query("max_qi") / 2));
		ob->move("/d/wanjiegu/wlhoushan");
		return 1;
	}
//	ob->add("jing", 0 - new_jing);
	ob->move(__DIR__"yanfeng");
	return 1;
}