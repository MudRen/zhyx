inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
������Ǿ�����Ϊ��������������֡�������������æ�Ľֵ��ϣ��ֵ���
��ˮ�������������������ַǷ����ϱ߽Ӿ��ǵĽ�ͨҪ���������֣�����ͨ��
�ذ��Ŷ���֡�
LONG );
       set("exits", ([
		"north" : __DIR__"wang_9",
		"south" : __DIR__"wang_5",
		"east" : __DIR__"wang_8",
		"west" : __DIR__"dong_1",
	]));

	set("objects", ([
		__DIR__"npc/girl3" : 1,
	]));

	set("coor/x",10);
	set("coor/y",1040);
	set("coor/z",0);
	setup();
       set("outdoors", "beijing");
	//replace_program(ROOM);
}

