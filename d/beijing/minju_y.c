#include <room.h>
inherit ROOM;

void create()
{
        set("short", "�ĺ�Ժ");
        set("long", @LONG
�ĺ�Ժ�Ǳ�����ӵĵ��ͣ�������ͬ�е�����ĺ�Ժ�����Ѿ�����һ�κ�
���õ���ʷ�ˡ��ĺ�Ժ�Ĵ����ƾɲ���������ԭ�����ŵ���ɫ���޷����ϣ���
�ϻ�����һ�����ƵĶ��ӣ��ּ�ģ�����壬����Ҳ���޷���Щ���������⡱ʲ
ô�ġ���տ���ĺ�Ժ�Ĵ��ţ�Ժ�ڵľ�������ֵ��������´������㣬û��
���ǳ����뿪�ɡ�
LONG );
       set("exits", ([
                "east" : __DIR__"yangliu1",
        ]));
        set("objects", ([
                __DIR__"npc/jumin1" : 1,
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "beijing");
        set("coor/x",-35);
        set("coor/y",980);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}

