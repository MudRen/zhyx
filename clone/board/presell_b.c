
inherit BULLETIN_BOARD;

void create()
{
	set_name("��Ϸ���������԰�", ({ "board" }) );
	set("location", "/u/viremploy/presell");
	set("board_id", "presell_b");
	set("long", "�������¼��\n" );
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}
