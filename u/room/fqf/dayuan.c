// File(/data/room/fqf/dayuan.c) of fqf's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "���ϸ��¥��Ժ");
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
        set("room_name", "���ϸ��¥");
        set("room_OWNER_id", "fqf");
        set("room_id", "qfxyl");
        set("room_owner_id", "fqf");
        set("room_position", "ƽԭС·");
}
