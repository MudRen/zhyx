inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
����һ����������ʯ��ֵ���������ͷ���졣�������
�������ڣ�����ϡ�٣������ĵغ������塣�����ǲ���ͤ�ͱ�
���ţ��ϱ��Ǳ�Ӫ�����߾��������ˡ�
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"west"  : __DIR__"xidajie2",
		"east"  : __DIR__"zhongxin",
		"north" : __DIR__"yamen",
		"south" : __DIR__"bingying",
	]));
	set("coor/x",190);
	set("coor/y",-150);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

