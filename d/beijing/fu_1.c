#include <room.h>
inherit ROOM;

void create()
{
	set("short", "����·");
	set("long", @LONG
�����Ǿ��ǵĻ���·�������ӷ����š�ֻҪ����������Ǯ����������ͻ�
�ܵ�������к����κ��㲻֪�����£����������һ�£�������֪�����˾Ų�
��ʮ���ϱ���һ��СС����ݣ������洫��һ���������
LONG );
	set("exits", ([
		"south" : __DIR__"mianguan",
		"east" : __DIR__"fu_2",
	]));

	set("outdoors", "beijing");
	set("coor/x",-25);
	set("coor/y",980);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

