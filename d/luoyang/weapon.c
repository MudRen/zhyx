inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
���������ͽֶ���Ŀ��׵궼��ͬһ���ϰ忪�ģ�֮���԰����Ƿ�
����ֻ��Ϊ�˷���˿͹����Լ���Ҫ�Ķ����������ı��Ϲ����˸�ʽ����
�ı��������Ƶģ����Ƶģ�ͭ�Ƶģ����Ƶģ�Ƥ�Ƶģ�Ʒ����ȫ��Ӧ�о�
�С�
LONG);
        set("no_fight", 1);
	set("exits", ([
  		"north" : __DIR__"eroad1",
	]));
        set("objects", ([
                __DIR__"npc/zhu2" : 1,
        ]));
	setup();
	//replace_program(ROOM);
}