inherit ROOM;

void create()
{
        set("short", "��ʯ��·");
        set("long", @LONG
������ľ�������������ˣ�ż�ŷ���������ʯ���������ۣ�
ң����Զ��ɽ���ڸ�����������ʯ�ݡ�
LONG);
        set("outdoors", "jueqing");
        set("exits", ([
               "north"   : __DIR__"shanzhuang",
               "south"   : __DIR__"zhulin1",
        ]));

        set("no_clean_up", 0);

        set("coor/x",-525);
	set("coor/y",-345);
	set("coor/z",20);
	setup();
        //replace_program(ROOM);
}