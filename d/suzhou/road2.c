// Room: /d/suzhou/road2.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "��ʯ�ٵ�");
	set("long", @LONG
������һ����ʯ����ϣ����������ǳ���æ����ʱ������
������ҴҶ��������������һЩС��̯���ƺ���һ�����С�
����������ݳ��ˡ���Ȼ�ǳ��⣬���Ǿ�ɫ���ˣ�������һ��
��ס����
LONG );
	set("outdoors", "suzhou");
	set("exits", ([
		"west"  : __DIR__"road3",
		"east"  : __DIR__"ximen",
	]));

        set("max_room", 4);

	setup();
}
