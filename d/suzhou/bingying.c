// Room: /d/suzhou/bingying.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "��Ӫ");
	set("long", @LONG
�����Ǳ�Ӫ���������鵽�����ǹٱ����е����佫��ָ��
���жӲ������еĶ������������е����š�����������Ϣ����
ǽ��������˧��������ɫ��Ѱ�������ܡ����������������ȫ
�������Χ�˹��������ƿ�����̫�
LONG );
	set("outdoors", "suzhou");
//	set("no_clean_up", 0);
	set("exits", ([
		"north"  : __DIR__"xidajie1",
	]));
	set("objects", ([
		"/d/city/npc/wujiang": 1,
		"/d/city/npc/bing": 4,
	]));
	set("coor/x",190);
        set("coor/y",-155);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}
