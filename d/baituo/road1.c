// Code of ShenZhou
// ���ոİ�
// maco 2/17/2000

inherit ROOM;

void create()
{
	set("short", "С��");
	set("long", @LONG
һ�������С�������洫����˻˻�������졣
LONG
	);
	set("exits", ([ 
	    "north" : __DIR__"barn",
            "south" : __DIR__"sheyuan",
	]));
        set("objects",([
                "/clone/beast/jinshe" : random(3),
                "/clone/beast/dushe"  : 1 + random(3),
                "/clone/beast/fushe"  : random(2),
                "/clone/beast/qingshe": random(2),
                "/clone/beast/wubushe": random(3),
        ]));

	set("outdoors","baituo");
	replace_program(ROOM);
	set("cost", 1);
	setup();
}
