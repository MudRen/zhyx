// Room: /d/xiangyang/eastroad1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "���ڴ��");
	set("long", @LONG
����һ����ʯ�̾͵Ĵ�֡�������һ�¸��ź�ɫ�����ߵ�
��ǽ�������������سǴ�����ĸ�ۡ��Ժ����������һ����
�֣�����������ʯ�̵Ĵ�ֵ���������һ�����ʮ�ֵֽ���ֻ
�������������ǳ����֡�
LONG );
        set("outdoors", "xiangyang");

	set("no_clean_up", 0);
	set("exits", ([
		"south" : __DIR__"eastjie2",
		"north" : __DIR__"eastroad2",
	]));
	set("coor/x",-475);
	set("coor/y",-390);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

