inherit ROOM;

void create()
{
        set("short", "ϷԺ��̨");
        set("long", @LONG
�����ǳ���ϷԺ�ĺ�̨����̨����ȴ��ɨ�úܸɾ�������Ϸ�����ں�̨
��ױ�����������ˣ����ú���ֵ��������㡣
LONG );
        set("exits", ([
                "south" : __DIR__"xiyuan",
        ]));
        set("objects", ([
                __DIR__"npc/q" : 2,
        ]));

        setup();
        replace_program(ROOM);
}


