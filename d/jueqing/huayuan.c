inherit ROOM;

void create()
{
        set("short", "��԰");
        set("long", @LONG
���Ǿ���ȵĺ�԰������԰��Ⱥ�����涷�ޣ�ż�Ż���
�˱ǣ��������顣���ܴ�ľ����������׷����Ϸ������һ����
�¡�
LONG);
        set("exits", ([
               "north"   : __DIR__"zizhuxuan",
               "west"    : __DIR__"xiaojing",
        ]));

        set("no_clean_up", 0);

        set("coor/x",-515);
	set("coor/y",-340);
	set("coor/z",19);
	setup();
        //replace_program(ROOM);
}
