inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
����һ����������ʯ��ֵ���������ͷ���졣������һ
����ʮ�ֽֿڡ�����������������㳡���������˳ƹ�������
���ĸ�ۡ���ţ���ʱ�����˴��������������������һ�ҵ��̣�
��˵���泣����������Ķ�����
LONG );
        set("outdoors", "xiangyang");
	set("no_clean_up", 0);

	set("exits", ([
		"east"  : __DIR__"guangchang",
		"west"  : __DIR__"westjie2",
		"south" : "/d/xiangyang/dangpu",
		"north" : "/d/wuguan/guofu_gate",
	]));
	set("objects", ([
		"/d/xiangyang/npc/poorman" : 1,
	]));
	set("coor/x",-495);
	set("coor/y",-400);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

