inherit ROOM;

void create()
{
	set("short", "���ټ����ܲ��Գ�");
	set("long", @LONG������ܰ�����ֵļ��ܲ��Գ���
���ﶼ�����ټ�����㡣
LONG );
	set("objects", ([
		__DIR__"npc/test11" : 1,
//		__DIR__"npc/test12" : 1,
	]));
	set("exits", ([
		"down" : __DIR__"test",
//		"up"   : __DIR__"test1",
	]));
	setup();
        //replace_program(ROOM);
}

