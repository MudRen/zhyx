inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
����������ŵ������ˣ����϶����������ס������һ��
����������������ϸ������ǽ������һ�����ң����顸�����
�����ĸ���������Ĵ��֡�֪���������İ����������飬ʦү
�����ں�
LONG );
	set("exits", ([
		"east"  : __DIR__"dongting",
		"west"  : __DIR__"xiting",
		"north" : __DIR__"neizhai",
		"south" : __DIR__"yamen",
	]));
	set("objects", ([
		__DIR__"npc/cheng" : 1,
		__DIR__"npc/shiye" : 1,
	]));
	set("coor/x",-10);
	set("coor/y",21);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

