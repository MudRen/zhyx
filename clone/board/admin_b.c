inherit BULLETIN_BOARD;

void create()
{
        set_name("天神留言板", ({ "board" }) );
        set("location", "/u/xgchen/admin_room");
        set("board_id", "admin_b");
        set("long", "这是一个天神使用的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

