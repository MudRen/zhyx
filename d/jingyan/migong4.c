#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
   ����������һ�����ǽ�Ͽ�������
��Щ�������͸߹�,�ֹ�ϸ�¾��ţ����̾����Ӵ�
���������ѽ⣬���Ķ���Щ�������������ʶ��
�㣬�������ϵ��������޾�һ��Ҳû������������
��֮����
LONG );
              set("no_stab", 1); 
       set("exits", ([
		"east" : __DIR__"migong2",
                "east" :"d/jingyan/migong2",		                          	
		                          	]));
                set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
