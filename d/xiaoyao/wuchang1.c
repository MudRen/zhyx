inherit ROOM;

void create()
{
        set("short", "��ң��");
        set("long", @LONG
������û�ж���İ��裬ֻ������Щ�����õ�ľ�ˣ�����
��ʧ�ޣ������𻵵ò���ˡ����������ǹ�����ң�ɵ�����
���õĳ�����
LONG);
        set("exits", ([
                "south" : __DIR__"xiaodao1",
                "north" : __DIR__"wuchang3",
        ]));

        set("outdoors", "xiaoyao");
        set("for_family", "��ң��");
        setup();
        //replace_program(ROOM);
}