// Room: /d/xiangyang/bingying3.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "��Ӫ");
	set("long", @LONG
�����Ǳ�Ӫ���������鵽�����ǹٱ����е����佫��ָ��
���жӲ������еĶ������������е����š�����������Ϣ����
ǽ��������˧��������ɫ��Ѱ�������ܡ����������������ȫ
������ɴ��۾������㡣
LONG );
	set("item_desc", ([
		"dong" : "\n",
	]));

	set("exits", ([
		"east" : __DIR__"southjie3",
	]));
	set("objects", ([
		__DIR__"npc/pian" : 1,
		__DIR__"npc/zuo"  : 1,
		__DIR__"npc/bing" : 2,
	]));
	set("coor/x",-494);
	set("coor/y",-415);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}
