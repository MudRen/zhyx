inherit ROOM;

void create()
{
        set("short", "Ѿ���Է�");
        set("long", @LONG
����Ѿ�ߵķ��䡣���г���򵥣�ûʲô������
LONG );

        set("exits", ([
                "east" : __DIR__"houyuan",
        ]));
        set("objects", ([
                __DIR__"npc/juyou" : 1,
        ]));
        set("cost", 0);
        set("coor/x", -480);
	set("coor/y", -230);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}

