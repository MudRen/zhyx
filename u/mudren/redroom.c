// afting.c
#include "room.h"
inherit ROOM;

void create()
{
        set("short", "�����¥");
        set("long", @LONG
[1;31m ��¥���������䣬�鲭Ʈ�ƶ��Թ顣[2;37;0m
[31m �����������Ω�Ƽ����C�����Ķ���֪��[2;37;0m
����һ�Ǻ�ǽ������ɽ�ڣ�����ǽ�Ͽ�һ����������������ͤ����
�¼������򻨣�����δ����֦Ҷ���Ե���������һ�ǵ�����һ����
����������ϯ��������߼�������������ʫ����һ���綹��������
�����������⸲��һ��������
LONG );
        set("exits", ([
                "out"   : "/d/hangzhou/chashi.c",
        ]));
        
        set("sleep_room", "1");
	 set("no_fight", "1");
//      set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}

