inherit ROOM;

void create()
{
	set("short", "����С·");
	set("long", @LONG
���Ƕ����ϵ�һ���Ӳݴ�������С·��������ƽʱûʲ
ô�˼���·�߿��Ų�֪��Ұ��������������Ȼ�ߴ�ͦ�Ρ�����
͸�����յ��������ǰ߲߰�����Ӱ�ӡ�
LONG );
	set("exits", ([
		"south"     : __DIR__"dalu",
		"north"     : __DIR__"xiaolu2",
	]));
	set("objects", ([
		"/clone/quarry/tu" : 1,
	]));
	set("outdoors", "lingzhou");
	set("coor/x",-2970);
	set("coor/y",3030);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

