inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
����һƬï�ܵ������֣�һ�߽�������·���ʧ�˷���
LONG);
        set("exits", ([
                "east" : __FILE__,
                "west" : __DIR__"ml4",
                "south" : __DIR__"dongmen",
                "north" : __FILE__,
        ]));
        set("outdoors", "city");
        set("coor/x",31);
	set("coor/y",11);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}