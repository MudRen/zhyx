inherit ROOM;

void create()
{
        set("short", "��ɭ��");
        set("long", @LONG
������������ĺ�ɭ�֣����ܾ���ï�ܵĴ��֣��޴�Ĺ�ľ����
���գ�ͷ��������һƬ��ա����²�ʱ������΢�����죬�ƺ���ʲô
�����Ӳݴ����ι���Զ��ż������һ��Ұ�޵ĺ�������
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "enter" : __DIR__"langwo",
                "south" : __DIR__"milin5",
                "west" : __DIR__"milin3",
                "north" : __DIR__"milin3",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        setup();
        //replace_program(ROOM);
}