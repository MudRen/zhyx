inherit ROOM;

void create()
{
	set("short", "��լ");
	set("long", @LONG
������������լ��ס��֪���ļҾ졣���˵��˾͸�ֹ���ˡ�
LONG );
	set("exits", ([
		"south" : __DIR__"ymzhengting",
	]));
	set("objects", ([
		__DIR__"npc/yuhuan" : 1,
	]));
	set("coor/x",-10);
	set("coor/y",31);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

