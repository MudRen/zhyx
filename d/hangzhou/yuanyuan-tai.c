// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "ԲԵ̨");
	set("long", @LONG
ɽ�����Ѷ��ϣ���ǰ������һ�鲻���ƽ�أ����߱�������������������
����ǰʯ��������֪��������Ƭ�յ�ԭ��������ԲԵ̨������νǧ����Եһ
��ǣ��ԲԵ̨������ָԲ������Ե�ĵط����������ܣ�ֻ��������´��������
�壬������ˣ���ɫ���ˣ����ļ�Ȥ��
LONG );
	set("exits", ([
		"north" : __DIR__"yuelao-ci",
        "east" : __DIR__"qixi-tai",
        "south" : __DIR__"shandao2",
	]));
	set("objects", ([
		__DIR__"npc/shusheng": 1,
	]));
//	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
