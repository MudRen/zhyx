
inherit BULLETIN_BOARD;

void create()
{
	set_name("��Ҵ��������԰�", ({ "board" }) );
	set("location", "/u/viremploy/assistant");
	set("board_id", "assistant_b");
	set("long", "�������¼��\n" );
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}
