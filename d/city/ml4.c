inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
����һƬï�ܵ������֣�һ�߽�������·���ʧ�˷���
LONG);
        set("exits", ([
                "east" : __FILE__,
                "west" : __FILE__,
                "south" : __DIR__"dongmen",
                "north" : __DIR__"ml5",
        ]));
        set("outdoors", "city");
        set("coor/x",21);
	set("coor/y",11);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}