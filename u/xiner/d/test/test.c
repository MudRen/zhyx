inherit ROOM;

void create()
{
	set("short", "��ټ����ܲ��Գ�");
	set("long", @LONG������ܰ�����ֵļ��ܲ��Գ���
���ﶼ����ټ�����㡣
LONG );
	set("objects", ([
		__DIR__"npc/test01" : 1,
//		__DIR__"npc/test02" : 1,
	]));
	set("exits", ([
		"down" : "/d/wizard/wizard_room",
		"up"   : __DIR__"test1",
	]));
	setup();
        //replace_program(ROOM);
}

