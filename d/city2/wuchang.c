
inherit ROOM;

void create()
{
	set("short", "���䳡");
	set("long", @LONG
����һ�����䳡,�ɾ޴�Ļ�����ʯ���̾�,�����ż���ľ�ˡ�
LONG );
	set("exits", ([
		"west" : __DIR__"kang2",
	]));
	set("objects",([
                "/clone/npc/mu-ren" : 3
	]));
//	set("no_clean_up", 0);
	set("outdoors", "city2");
	setup();
	replace_program(ROOM);
}
