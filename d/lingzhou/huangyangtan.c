inherit ROOM;

void create()
{
	set("short", "����̲");
	set("long", @LONG
��������������������Ļ���̲�������ǻƺӱߵ�һ��Ƭ
ˮ���μ�أ��ƺ�ˮ���ĺ���ȥ�γ���һ��Ƭ����ˮ̲������
ˮ�ݷ�ʢ���������������˴���������Ұ��������������ˮ
��Ϸ��������Ϣ����Ϊ����һ�󾰹ۡ�
LONG);
	set("exits", ([
		"north"     : __DIR__"nanmen",
		"southwest" : __DIR__"xiaoba",
	]));
	set("no_clean_up", 0);
	set("objects", ([
		"/clone/quarry/yang3" : 1,
	]));
	set("outdoors", "lingzhou");
	set("coor/x",-3000);
	set("coor/y",2970);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}
