inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����������úͺ��õĳ��ȣ��䲻����ľ����Ҳ���ŵ���
���Ļ��㡣
LONG);
        set("exits", ([
               "north"   : __DIR__"changlang3",
               "south"   : __DIR__"neitang",
        ]));

        set("no_clean_up", 0);

        set("coor/x",-525);
	set("coor/y",-330);
	set("coor/z",19);
	setup();
        //replace_program(ROOM);
}
