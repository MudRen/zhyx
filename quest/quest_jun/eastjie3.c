// Room: /d/xiangyang/eastjie3.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
����һ����������ʯ�ֵ���������ͷ���졣����������
���ţ��ϱ���ľ���̣���ľ������ľ���������������������
�ǵĶ���Ӫ���������������洫���α��Ĳ�������������һ��
ʮ�ֽֿڣ�ֻ���������������ﲻ����
LONG );
        set("outdoors", "xiangyang");
	set("no_clean_up", 0);

	set("exits", ([
		"east"  : __DIR__"eastgate1",
		"west"  : __DIR__"eastjie2",
		"south" : "/d/xiangyang/mujiang",
		"north" : "/d/xiangyang/bingying2",
	]));
        set("coor/x",-473);
	set("coor/y",-400);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

