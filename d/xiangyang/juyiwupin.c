inherit ROOM;

void create()
{
	set("short", "��Ʒ��");
	set("long", @LONG
���Ǿ���ݵĶѷŸ��ָ�����Ʒ�ķ��䡣
LONG );
	set("exits", ([
		"northwest" : __DIR__"juyihuayuan",
	]));
	set("coor/x",-495);
	set("coor/y",-412);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

