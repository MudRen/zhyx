inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
����һ����������ʯ��ֵ���������ͷ���졣���߲�ʱ
�ش�������ײ�����������������ӡ�������һ��Ժ�ӣ�������
�Ĵ����Ϸ�д�š���¹��Ժ���ĸ��̽���֣��Ծ�����������
��ʱ�ش���ѧ��������ٴ�Ķ��������ϱ���һ���ӻ��̡�
LONG );
        set("outdoors", "city");
	set("exits", ([
		"east" : __DIR__"dongdajie2",
		"south" : __DIR__"zahuopu",
		"west" : __DIR__"guangchang",
		"north" : __DIR__"shuyuan",
	]));

	set("objects", ([
		"/clone/npc/xunbu" : 1,
	]));
	set("coor/x",10);
        set("coor/y",1);
	set("coor/z",0);
	setup();
        "/clone/fam/notice(con)"->foo(); 
	//replace_program(ROOM);
}

