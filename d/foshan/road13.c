inherit ROOM;

void create()
{
        set("short", "�ּ��");
        set("long", @LONG
������һ���ּ�С���������������ѡ�����ɽ��ï�ܣ���
�����棬����·�˾����˵ض��Ƿǳ���С�ġ�
LONG);
	set("objects", ([
	        __DIR__"obj/shuzhi": 1,
	]));
	set("outdoors", "foshan");
	set("exits", ([
	        "northeast" : __DIR__"road14",
	        "southwest" : __DIR__"road11",
	]));
	setup();
	//replace_program(ROOM);
}
