// Room: /d/xiangyang/hutong2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "��ͬ");
	set("long", @LONG
���������������ϰ��յľ�ס����ֻ����ͬ��������ЩС
���棬�����С�С�ӻ��̵ȡ�һЩ������������������
LONG );
        set("outdoors", "xiangyang");

	set("exits", ([
		"south" : __DIR__"jiekou1",
	]));
	set("objects", ([
		__DIR__"npc/girl" : 2,
	]));
	set("coor/x",-500);
	set("coor/y",-370);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}
