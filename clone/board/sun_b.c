// /clone/board/wiz_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("��ʦ���Բ�", ({ "board" }) );
        set("location", "/u/sun/workroom");
	set("board_id", "wiz_b");
        set("long", "����һ��ĩ�յ����԰塣\n" );
	setup();
	set("capacity", 1000);
	replace_program(BULLETIN_BOARD);
}

