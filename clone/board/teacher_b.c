
inherit BULLETIN_BOARD;

void create()
{
	set_name("���ֵ�ʦ�����԰�", ({ "board" }) );
	set("location", "/u/viremploy/teacher");
	set("board_id", "teacher_b");
	set("long", "�������¼��\n" );
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}
