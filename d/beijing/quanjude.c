inherit ROOM;

void create()
{
	set("short", "ȫ�۵¾�¥");
	set("long", @LONG
������Ǿ�������Ϊ������ȫ�۵¾�¥����Բ������������ȫ�۵¾�¥��
��Ѽ����˵�����˲�֪�����˲�����¥������˽ǣ���ľ�̵أ�������������
���ϻ����ż�����������װ��������Ż�������С������һ�������ľ�ǻ��
����к��ſ��ˡ���¥��ǽ����һ��¥�ݣ�ͨ��ȫ�۵¾�¥��¥��������
LONG );
	set("exits", ([
		"south" : __DIR__"wang_10",
		"up"   : __DIR__"quanjudeup",
	]));
	set("objects", ([
		__DIR__"npc/xiaoer1" : 1,
	]));

	set("coor/x",20);
	set("coor/y",1060);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

