inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
������Ǿ�����Ϊ��������������֡�������������æ�Ľֵ��ϣ��ֵ���
��ˮ�������������������ַǷ����ϱ��Ǿ��ǵĽ�ͨҪ���������֣������ڽ�
����һ�ҵ��̡�
LONG );
       set("exits", ([
		"north" : __DIR__"wang_8",
		"south" : __DIR__"wang_4",
		"west" : __DIR__"wang_5",
		"east" : __DIR__"dangpu",
	]));

	set("objects", ([
		__DIR__"npc/boy2" : 1,
	]));

	set("coor/x",20);
	set("coor/y",1030);
	set("coor/z",0);
	setup();
       set("outdoors", "beijing");
	//replace_program(ROOM);
}

