
inherit BULLETIN_BOARD;

void create()
{
	set_name("�����������԰棨�ϳͶ����ˮ����", ({ "board" }) );
	set("location", "/d/city/wumiao");
	set("board_id", "newplayer_b");
	set("long", "����һ��ר�����ַ�������ʹ�õ����԰塣���ϳͶ����ˮ����\n" );
	setup();
	set("capacity", 200);
	replace_program(BULLETIN_BOARD);
}

