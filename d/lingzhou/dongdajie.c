#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
�������ݶ���֣�ͬ���Ŀ�����ɾ����������ֵ�����Ҫ���ֶ�
�ˣ�����������������������������С�����ں�ͬ����ˣ�������в���
��Χ��һ�𣬱��������ţ�·������������׷һֻè��
LONG );
	set("exits", ([
		"south" : __DIR__"jiangjungate",
		"north" : __DIR__"yamen",
		"west"  : __DIR__"center",
		"east"  : __DIR__"dongmen",
	]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
	set("no_clean_up", 0);
	set("outdoors", "lingzhou");
	set("coor/x",-2990);
	set("coor/y",3000);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}
