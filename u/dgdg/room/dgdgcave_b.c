// /u/dgdg/fuben/room/dgdgcave_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("Զ��ͨ�����԰�", ({ "board" }) );
	set("location", "/u/dgdg/fuben/room/wolfcave");
	set("board_id", "sdgdgcave_b");
	set("long", "����һ�������������������԰塣\n" );
	setup();
	set("capacity", 1200);
	replace_program(BULLETIN_BOARD);
}
