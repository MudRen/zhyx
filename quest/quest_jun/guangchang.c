inherit ROOM;

void create()
{
	set("short", "����㳡");
	set("long", @LONG
����������������㳡��������ʯ���档����ͨ�������ţ�
����ͨ��׻��ţ�����ֱ����ȸ�ţ�ԶԶ����ɿ�����������
������ʹ���š��������ɹŴ���Ŵι����������ٸ�Ϊ��ֹ��
�ż�ϸ���ӽ������Ѿ������������ڴ˾ۼ���ֻ��һ�ӹٱ���
������Ѳ�ߣ��㻹�ǿ��뿪�ɡ�
LONG );
        set("outdoors", "xiangyang");
	set("exits", ([
		"east"  : __DIR__"eastjie1",
		"west"  : __DIR__"westjie1",
		"south" : "/d/xiangyang/southjie1",
		"north" : "/d/xiangyang/anfupailou",
	]));
	set("objects", ([
		"/d/xiangyang/npc/pian" : 1,
		"/d/xiangyang/npc/bing" : 1,
                "/clone/npc/walker" : 1,
	]));
	set("coor/x",-490);
	set("coor/y",-400);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

