// Room: /xiakedao/lin2.c

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����һƬï�ܵ����֣��ƺ����������������һ������һ�߽�
���������ʧ�˷���
LONG );
        set("outdoors", "xiakedao");
        set("exits", ([
                "east" : __DIR__"lin3",
                "west" : __DIR__"lin1",
                "south" : __FILE__,
                "north" : __FILE__,
                "southeast" : __FILE__,
                "northeast" : __FILE__,
        ]));
        setup();
        //replace_program(ROOM);
}
