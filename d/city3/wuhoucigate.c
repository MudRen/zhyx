inherit ROOM;

void create()
{
	set("short", "���������");
	set("long", @LONG
����ԭ����������������˽��˳�������������ԭ
�������ǰ�����츣������������������ȥ������Ϊ���
Т֮�ס���������Ű������ǧ�����´���ͷ���Բ�ȥ�ס�
LONG);
        set("outdoors", "chengdu");
	set("exits", ([
		"northeast" : __DIR__"southroad3",
		"north"     : __DIR__"liubeidian",
	]));
	set("no_clean_up", 0);
	set("coor/x",-515);
	set("coor/y",-220);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}
