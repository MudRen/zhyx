inherit ROOM;

void create()
{
	set("short", "���ڴ��");
	set("long", @LONG
����һ����ʯ�̾͵Ĵ�֡�������������������һ���ܸ�
�Ĳ�¥��������һ�¸��ź�ɫ�����ߵĸ�ǽ�������ǹ�����Ժ��
���������������ֺŵĿ͵꣬��������ʯ�̵Ĵ�֡�
LONG );
        set("outdoors", "xiangyang");

	set("no_clean_up", 0);
	set("exits", ([
		"northeast"  : __DIR__"kedian",
		"south" : __DIR__"westjie2",
		"north" : __DIR__"westroad2",
	]));
	set("coor/x",-500);
        set("coor/y",-395);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

