#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
����������һ�����ǽ�Ͽ���������Щ
�������͸߹ţ��ֹ�ϸ�¾��ţ����̾����Ӵ󣬶�
���������ѽ⣬���Ķ���Щ�������ޡ������ʶ
��㣬�������ϵ��������޾�һ��Ҳû����������
���֮����
LONG );              
       set("exits", ([
           "east" : __DIR__"migong2",
       ]));               
	setup();
	replace_program(ROOM);
}
