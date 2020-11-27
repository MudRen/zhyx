#include <room.h>
#include <ansi.h>

inherit CREATE_CHAT_ROOM;

int is_chat_room() { return 1; }

void create()
{
	set("short", "�͵�");
	set("long", @LONG
����һ�Ҽ�Ǯ�����Ŀ�ջ������ȴ�Ƿǳ���¡������ο�
��ѡ��������ţ��������������������صķ������顣��С
����������æ������ת���Ӵ�����ǻ�����Ŀ��ˡ��͵������
�Ӳ�¶�棬��������˭���и��ָ����Ĳ²⡣�͵����ǽ�Ϲ�
��һ������(paizi)��
LONG );
	set("no_fight", 1);
	set("valid_startroom", 1);
        set("no_sleep_room",1);
	set("item_desc", ([
		"paizi" : WHT "\n\n        ����������������������������������\n"
                              "        ��                              ��\n"
                              "        ��   " NOR + HIW "�����ҿ͵꣬����ṩס�ޡ�" NOR + WHT " ��\n"
                              "        ��                              ��\n"
                              "        ����������������������������������\n\n\n" NOR,
	]));
	set("objects", ([
                __DIR__"npc/xiaoer" : 1,             
	]));
	set("exits", ([
		"west" : __DIR__"beidajie1",
              "up":"/d/wizard/advice",
		"down"   : __DIR__"kedian2",
		"south": __DIR__"liaotian",
	]));
	
	setup();
	"/clone/board/kedian_b"->foo();
    "/adm/npc/beichou"->come_here();
}

void init()
{
        add_all_action();
}

