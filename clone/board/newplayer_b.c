
inherit BULLETIN_BOARD;

void create()
{
	set_name("新手问题留言版（严惩恶意灌水！）", ({ "board" }) );
	set("location", "/d/city/wumiao");
	set("board_id", "newplayer_b");
	set("long", "这是一个专供新手发表问题使用的留言板。（严惩恶意灌水！）\n" );
	setup();
	set("capacity", 200);
	replace_program(BULLETIN_BOARD);
}

