// ��Ů��/������Ů���յص��

#include <ansi.h> 
inherit ROOM;

void create()
{
	set("short", "��Ů��");
	set("long", @LONG
ֻ���������ʮ�ְ������Ĵ��ҳ��������ƺ����кܾ�δ��
���������˴���
LONG );
	set("exits", ([		
		"up"  : __DIR__"nvwamiao",
	]));
       set("no_fight",1);	
	setup();
	
}
/*
void init()
{
    add_action("do_ketou", "ketou");  
    add_action("do_tuotai", "tuotai");      
}

*/

