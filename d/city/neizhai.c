inherit ROOM;

void create()
{
	set("short", "内宅");
	set("long", @LONG
这里是衙门内宅，住着知府的家眷。外人到此就该止步了。
LONG );
	set("exits", ([
		"south" : __DIR__"ymzhengting",
	]));
	set("objects", ([
		__DIR__"npc/yuhuan" : 1,
	]));
	set("coor/x",-10);
	set("coor/y",31);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

