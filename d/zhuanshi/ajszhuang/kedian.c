// by yuchang

#include <ansi.h>
#include <room.h>
inherit ROOM; 

void create()
{
	set("short", "õ���ջ");
	set("long", @LONG       
����������ոտ�ҵ��õ���ջ���ϰ�����ǳ���¡��
��ջ�����ǽ�Ϲ���һ����Ŀ������(paizi)��
LONG
);	
	set("no_sleep_room",1);
	set("item_desc", ([
		"paizi" : "¥���ŷ���ÿҹ����������\n",
	]));

	set("objects", ([
                __DIR__"npc/xiaoer" : 1,
	]));

	set("exits", ([
                "west" : __DIR__"shanlu",                
		  "up" : __DIR__"kedian2",
	]));
	setup();
}

int valid_leave(object me, string dir)
{

	if ( !me->query_temp("rent_paid") && dir == "up" )
		return notify_fail("��ô�ţ����ס����\n");

	if ( me->query_temp("rent_paid") && dir == "west" )
		return notify_fail("�͹��Ѿ��������ӣ���ô��ס��������أ����˻���ΪС���ź����أ�\n");

	return ::valid_leave(me, dir);
}
