// Room: /d/xiangyang/juyimale.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "�пͷ�");
	set("long", @LONG
���Ǽ�������᷿�����Ŵ������ţ����ߺܻ谵�������
�����ֻ�����߷��ż�����ʰ����������Ĵ󴲣����ž���
����˯����
LONG );
	set("sleep_room", "1");
	set("no_clean_up", 0);

	set("exits", ([
		"east" : __DIR__"juyihuayuan",
	]));
	set("coor/x",-505);
	set("coor/y",-411);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

