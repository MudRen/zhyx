// Code of ShenZhou
// ���ոİ�
// maco 2/17/2000

inherit ROOM;

void create()
{
	set("short", "С��");
	set("long", @LONG
������ƫƧ��С�������ѵ��������ɽ��������Ȼ������ң����
������һ�������ɽ�ȣ�������ɭ���Ǿ��ǰ���ɽ���߹ȡ����ߵĲ�
·ͨ������ɽׯ���߳���
LONG
	);
	set("exits", ([ 
	    "east" : __DIR__"shechang",
	    "north" : __DIR__"shegu1",
	    "south" : __DIR__"barn",
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
