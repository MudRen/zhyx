// File(/data/room/kxin/dayuan.c) of kxin's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "���гǴ�Ժ");
	set ("long", @LONG
����һ��������Ժ�䣬���Ÿ�����ľ������������͸������Ͷ��
���Ӱ�ӡ�һ����·ͨ�����棬�ȵ÷ǳ�ƽ���ģ������Ǿ���������
���� 
LONG );

	set("exits", ([
		"north"  : __DIR__"qianting",
                "out"    : "/d/xiakedao/xkroad3",
	]));

        set("outdoors", "nanhai");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);
        setup();

        set("room_owner", "����");
        set("room_name", "���г�");
        set("room_OWNER_id", "kxin");
        set("room_id", "yzc");
        set("room_owner_id", "kxin");
        set("room_position", "ƽԭС·");
}
