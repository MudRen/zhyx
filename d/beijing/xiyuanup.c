inherit ROOM;

void create()
{
	set("short", "ϷԺ��̨");
	set("long", @LONG
�����ǳ���ϷԺ�ĺ�̨����̨����ȴ��ɨ�úܸɾ�������Ϸ�����ں�̨
��ױ�����������ˣ����ú���ֵ��������㡣
LONG );
	set("exits", ([
		"south" : __DIR__"xiyuan",
	]));
	set("objects", ([
		__DIR__"npc/xizi1" : 2,
		__DIR__"npc/xizi2" : 1,
		__DIR__"npc/xizi3" : 1,
	]));

	set("coor/x",30);
	set("coor/y",1060);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}
