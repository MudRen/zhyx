inherit ROOM;

void create()
{
	set("short", "���µ�");
	set("long", @LONG
�������������¹󸾳���֮��������Ҳ��������Ҳң�֬
�ۺ�ɡ���Ϊ��������ʱ�У�һֱ�����������Ե�װ�硣����
�Ǹ��ܿ��˵�СŮ����������һ������ʱ���������������Ů
�˼���һ�𣬻�������������
LONG );
	set("exits", ([
		"down" : __DIR__"zahuopu",
	]));
	set("objects", ([
		"/adm/npc/zeng": 1, //Ȩ������ ��NPC�ƶ���/adm/npc/Ŀ¼
	]));
	set("no_fight", 1);
	set("coor/x",10);
	set("coor/y",-10);
	set("coor/z",10);
	setup();
	//replace_program(ROOM);
}

