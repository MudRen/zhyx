inherit ROOM;

void create()
{
	set("short","Ϸ԰��");
	set("long",@LONG
����һ�����ݳ��ﶦ��������Ϸ԰��Ϸ԰�е�������������
ī����һӦ��ȫ������һ����Ϸ̨��̨�����ڳ��š�����������
̨�²�ʱ�ش���Ʊ���ǵĽ�Ծ���Ȳ�������Ҳ�̲�ס��������
����Ϸ������һ�½�ǡ�
LONG);
	set("objects", ([
		__DIR__"npc/piaoyou": 3,
	]));
	set("exits", ([
		"east" : __DIR__"beidajie1",
	]));
	set("coor/x",190);
	set("coor/y",-140);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}
