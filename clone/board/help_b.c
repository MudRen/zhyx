inherit BULLETIN_BOARD;

void create()
{
        set_name("���������", ({ "board" }) );
         set("location", "/d/city/advice/help");
        set("board_id", "game_advice");
        set("long", "���õĻ���������˵���ҹ�ˮɱ���⡣\n" );
        setup();
        set("capacity", 100000);
        replace_program(BULLETIN_BOARD);
}
