inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
������ϣ����ż�ʵ����ʯ����档�����Ƕ����ţ�����
�����سǹٱ���ߺ���������������ʵĶ�����������һ�𡣱�
����һ�����ֺŵ�ҩ�̣��ϱ��Ǵ����̣�����������������Զ
����������
LONG);
        set("outdoors", "city");
	set("exits", ([
		"east"  : __DIR__"dongmen",
		"south" : __DIR__"datiepu",
		"west"  : __DIR__"dongdajie1",
		"north" : __DIR__"yaopu",
	]));

	set("coor/x",20);
        set("coor/y",1);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

