#include <room.h>
inherit ROOM;

void create()
{
    	set("short", "����");
    	set("long", @LONG
���ݽ����ï�����֣���ɭ�ɲ���̧ͷ�������ա�����Ҳ
�����������������ĵط��������߳��ε����
LONG);
        set("outdoors", "city");
    	set("exits", ([
        	"east"  : __DIR__"jiaowai9",
        	"west"  : __DIR__"jiaowai11",
        	"north" : __DIR__"jiaowai12",
    	]));
    	set("coor/x",-30);
	set("coor/y",-40);
	set("coor/z",0);
	setup();
    	//replace_program(ROOM);
}