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
        	"east"  : __DIR__"jiaowai4",
        	"west"  : __DIR__"jiaowai6",
    	]));
    	set("objects", ([
        	__DIR__"obj/shuzhi": 2,
        	"/clone/beast/dushe" : 1,
    	]));
    	set("coor/x",25);
	set("coor/y",-40);
	set("coor/z",0);
	setup();
    	//replace_program(ROOM);
}
