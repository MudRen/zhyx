// by yuchang
inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
�����Ƿ����Ĵ���У�������������������ĵ��������У�
��ǰ׹�ɭɭ�����ڶ���֮ǰ��������ʿ��������й�����
��ƴɱ�������ϵ������ż�ʸ�������������أ�����������
һֱδ����ɨ����
LONG
	);

	set("exits", ([
		"north" : __DIR__"zoulang",
                "out" : __DIR__"shanzhuang",
	]));
	
	setup();
	replace_program(ROOM);
}



