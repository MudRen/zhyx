inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
����һ����������ʯ��ֵ���������ͷ���졣�������
�������ڣ�����ϡ�٣������ĵغ������塣������һ�����ֵ�
�㳡���ϱ���һ����ׯ�����߾��������ˡ�
LONG);
        set("outdoors", "city");
	set("no_clean_up", 0);
	set("exits", ([
		"east"  : __DIR__"guangchang",
		"south" : __DIR__"shan",
		"west"  : __DIR__"xidajie2",
		"north" : __DIR__"yamen",
	]));

        set("coor/x",-10);
        set("coor/y",1);
	set("coor/z",0);
	setup();
        "/clone/fam/notice(killed)"->foo(); 
	//replace_program(ROOM);
}

