inherit ROOM;

void create()
{
        set("short", "����԰");
        set("long", @LONG
�����ǳ�������������԰,�ֶ��·�����ס������,
����԰���п�ˮ��!�����е�Ź�!

LONG    );

        set("exits", ([
               "west" : "/d/changan/zao",
                          ]));

        setup();
        replace_program(ROOM);
}
