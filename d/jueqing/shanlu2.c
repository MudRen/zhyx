inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
���ô˴���һ·�����Ƿ����ʤ��ֻ��·���ɺ���������
¹��Ⱥ������С�ã����Ǽ��˲�����ż���ŵ�����Ļ��㣬��
�����԰��á�С¹��ȥ��Ծ�����ǿɰ��������Ŀ�������
LONG);
        set("outdoors", "jueqing");
        set("exits", ([
               "northeast"   : __DIR__"zhulin1",
               "southdown"   : __DIR__"shanlu1",
        ]));

        set("no_clean_up", 0);

        set("coor/x",-530);
	set("coor/y",-355);
	set("coor/z",20);
	setup();
        //replace_program(ROOM);
}
