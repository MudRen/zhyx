// File(/data/room/rong/dayuan.c) of rong's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "ܽ�ؾӴ�Ժ");
	set ("long", @LONG
����һ��������Ժ�䣬���Ÿ�����ľ������������͸������Ͷ��
���Ӱ�ӡ�һ����·ͨ�����棬�ȵ÷ǳ�ƽ���ģ������Ǿ���������
���� 
LONG );

	set("exits", ([
		"north"  : __DIR__"qianting",
                "out"    : "/d/xiakedao/xkroad4",
	]));

        set("outdoors", "nanhai");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);
        setup();

        set("room_owner", "ˮ�ض�");
        set("room_name", "ܽ�ؾ�");
        set("room_OWNER_id", "rong");
        set("room_id", "rong");
        set("room_owner_id", "rong");
        set("room_position", "�Ϻ����");
}
