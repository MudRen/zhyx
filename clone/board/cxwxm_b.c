// marry 99.8
inherit BULLETIN_BOARD;

void create()
{
        set_name("���������ŵ������԰�", ({ "board" }) );
        set("location", "/d/cxwxm/dating");
        set("board_id", "board");
        set("long", "����һ�������������ŵ��ӽ��������԰塣\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}
