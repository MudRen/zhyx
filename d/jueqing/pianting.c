inherit ROOM;

void create()
{
        set("short", "ƫ��");
        set("long", @LONG
��������ö������ƫ���������ǹ����к�����̸��Ȳ�
�ĵط����˴������徲��ż��һ������а����ŵ�����������
����һ��˵�������泩��
LONG);
        set("exits", ([
               "west"   : __DIR__"neitang",
        ]));

        set("no_clean_up", 0);

        set("coor/x",-524);
	set("coor/y",-335);
	set("coor/z",19);
	setup();
        //replace_program(ROOM);
}

