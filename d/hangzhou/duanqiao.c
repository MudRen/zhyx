#include <room.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�������������������ķ�ˮ���ϡ�����ͤ�����䣬��ӳ������
����֮�¡���ɽ��ˮ��������������������������������������
��ľ�ɫ���ڶ����Ͽ����������ɽ�ͺ�����ķ�⡣ÿ��ѩ���ᣬ
վ����ͷ��ֻ��һ�ж������ϰ�ѩ��������¥�ĺ�ɽ��ò��������ʮ
��֮һ�ġ����Ų�ѩ��������񻰡����ߴ����еİ���������ɾ���
�������ġ����������߱��ǰ׵��ˡ������߿�ͨ����ʯ�����
LONG);
        set("exits", ([
            	"northeast" : __DIR__"road9",
            	"south"      : __DIR__"baiti",
        ]));
        set("objects", ([
            	__DIR__"npc/poorman" : 1,
        ]));
        set("outdoors", "hangzhou");
        set("coor/x",189);
	set("coor/y",-361);
        set("coor/z",0);
	setup();
        //replace_program(ROOM);
}
