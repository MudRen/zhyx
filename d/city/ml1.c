inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
����һƬï�ܵ������֣�һ�߽�������·���ʧ�˷���
LONG );
        set("exits", ([
                "east" : __DIR__"ml2",
                "west" : __FILE__,
                "south" : __DIR__"dongmen",
                "north" : __FILE__,
        ]));
        set("outdoors", "city");
        set("coor/x",30);
	set("coor/y",10);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}