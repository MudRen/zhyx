inherit ROOM;

void create()
{
        set("short", "����¥");
        set("long", @LONG
����¥Ϊ��������������֮�����������ͣ��ʹ��־裬��
�����������ۡ�
LONG);
        set("exits", ([
               "south"  : __DIR__"jiayingmen",
               "north"  : __DIR__"dadian",
        ]));

        set("no_clean_up", 0);

        setup();
        //replace_program(ROOM);
}
