//create by xgchen 2003

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "��������");
	set("long", @LONG
���������ţ��������Ϸ����ż����������֡���ǽ�����ż��Źٸ�
��ʾ��һ��·����ͨ�������ڤ�塣
LONG );
	set("exits", ([
		"west"      : "/d/xuanminggu/xiaolu1",
		"southeast" : __DIR__"biaoqiyin",
	]));
	set("no_clean_up", 0);
	set("outdoors", "lingzhou");
	set("coor/x",-3025);
	set("coor/y",3010);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

