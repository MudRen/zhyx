
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "����������");
	set("long", @LONG
�����Ǳ����⣬�������������������ۻ����ҡ��������������𹿰���
�󵶡��������ڰ����̵����̽����̹�����ɫ�����ı���Ӧ�о��У���һ
ʱ��֪����ʲô�á�
LONG );

	set("exits", ([
		"north" : __DIR__"bingyin1",
		"southwest" :  __DIR__"aobai12",
	]));
	set("objects", ([
		"/clone/weapon/changjian" : 1,
		"/clone/weapon/tiegun" : 1,
		"/clone/weapon/changbian" : 1,
		"/clone/weapon/duanjian" : 1,
		"/clone/weapon/gangdao" : 2,
	]));

//	set("no_clean_up", 0);
	create_door("north", "����", "south", DOOR_CLOSED);
	setup();
	replace_program(ROOM);
}
