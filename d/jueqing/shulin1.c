inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����ɽ��ˮ�̣���ɫ�������ģ�ֻ�����¼�����Ϣ������
͸�����գ�ż��ȴ����Լ����Ϫ������֮���ص���ɽ�ȡ� 
LONG);
        set("outdoors", "jueqing");
        set("exits", ([
               "northup"   : __DIR__"shuitang",
               "southdown" : __DIR__"shanjiao",
        ]));

        set("no_clean_up", 0);

        set("coor/x",-535);
	set("coor/y",-365);
	set("coor/z",10);
	setup();
        //replace_program(ROOM);
}
