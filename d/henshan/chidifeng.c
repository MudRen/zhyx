inherit ROOM;

void create()
{
        set("short", "��۷�");
        set("long",@LONG
�ഫף�����Ի�ʩ�����ǻƵ۵Ļ����٣��������Ϸ�����
���������ڴˣ�������۷塣
LONG);
        set("exits", ([
                "southdown"  : __DIR__"shanlu2",
                "eastdown"   : __DIR__"shanlu11",
                "northdown"  : __DIR__"shanlu3",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

        setup();
        //replace_program(ROOM);
}
