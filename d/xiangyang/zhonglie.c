inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����������ǵ���������ʮ������Ϊ������������������
ʿ�ŹǶ����������ÿ���а����ĵĺú����ⶼ��������һ
���һꡣ
LONG );
        set("exits", ([
                "west" : __DIR__"eastroad2",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("coor/x",-470);
	set("coor/y",-385);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}

