
inherit BULLETIN_BOARD;

void create()
{
	set_name("��ҳά�������԰�", ({ "board" }) );
	set("location", "/u/viremploy/webmaster");
	set("board_id", "webmaster_b");
	set("long", "�������¼��\n" );
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}
