// /u/haiyan/hybook.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("����ıʼǱ�", ({ "board" }) );
        set("location", "/u/haiyan/workroom");
        set("board_id", "hybook");
        set("long", "���Ǻ���ƽʱ��¼��һЩѧϰ�ĵá�\n" );
	setup();
        set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}

