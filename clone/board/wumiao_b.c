// /clone/board/wudao_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("���齻����", ({ "board" }) );
        set("location", "/d/city/wumiao");
        set("board_id", "wumiao_b");
        set("long", "����һ��ר����Ҿ��齻����������ˮɱ���⡣\n" );
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}

