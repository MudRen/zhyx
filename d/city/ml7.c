inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
����һƬï�ܵ������֣�һ�߽�������·���ʧ�˷���
LONG );
        set("exits", ([
                "east" : __FILE__,
                "west" : __FILE__,
                "south" : __DIR__"dongmen",
                "north" : __DIR__"pomiao",
        ]));
        set("outdoors", "city");
        set("coor/x",33);
	set("coor/y",21);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}
