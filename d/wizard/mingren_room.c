// /d/wizard/guest_room.c

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�л�������");
	set("long", @LONG
�������л������ĸ�λ���֣�������ﲻ���������£�������ֵĺڵ�ħͷ��Ҳ
�����ݺ��ĺ����ŵ��ȳ��İ׵����������������Ѿ��뿪��̶��Ʈ��Զȥ�����ﱣ��
�Ľ��������ǵ������ò�似������Щ�������������µ��񻰹���ȴ��Զ�����ڽ���
֮�У�����ĥ��
LONG );

	set("exits", ([
		"east": __DIR__"guest_room",
        ]));
	set("no_fight", "1");
set("objects", ([ 
]));
	setup();
}

