inherit BULLETIN_BOARD;

void create()
{
        set_name("�������԰�", ({ "board" }) );
        set("location", "/u/xgchen/admin_room");
        set("board_id", "admin_b");
        set("long", "����һ������ʹ�õ����԰塣\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

