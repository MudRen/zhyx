inherit ROOM;

void create()
{
        set("short", "С��");
        set("long", @LONG
���Ǿ���ȴ���ͨ����԰��һ���ؾ�֮·����·���Ի�
�ݴ������������ˡ�
LONG);
        set("exits", ([
               "east"   : __DIR__"huayuan",
               "west"   : __DIR__"dating",
        ]));

        set("no_clean_up", 0);

        set("coor/x",-520);
	set("coor/y",-340);
	set("coor/z",19);
	setup();
        //replace_program(ROOM);
}
