inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����Ǳ������������⡣����������ɷ�����֡�
LONG );
        set("exits", ([
                "east" : __DIR__"xichengmen",
                "west" : "/d/heimuya/road3",
                "north" : __DIR__"liandan_lin1",
                "south" : __DIR__"liandan_lin2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "beijing");
        set("coor/x",-80);
	set("coor/y",1020);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}

