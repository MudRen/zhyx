#include <room.h>
inherit ROOM;

void create()
{
    	set("short", "�ݵ�");
    	set("long", @LONG
�������ݽ����һƬ���ݵأ���Ӣ�ͷף������裬��¶
Ϧ�⣬������Ƣ�������ѿ�����������ʱ��
LONG);
        set("outdoors", "city");
    	set("exits", ([
        	"east" : __DIR__"nanmen",
        	"west" : __DIR__"jiaowai9",
    	]));
        if (random(10) < 8)
        {
              set("objects", ([
                      __DIR__"npc/shuang" : 1,
              ]));
        }
    	set("no_clean_up", 0);
    	set("coor/x",-5);
	set("coor/y",-40);
	set("coor/z",0);
	setup();
    	//replace_program(ROOM);
}
