// File(/data/room/keep/dayuan.c) of keep's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "����С����Ժ");
	set ("long", @LONG
����һ��������Ժ�䣬���Ÿ�����ľ������������͸������Ͷ��
���Ӱ�ӡ�һ����·ͨ�����棬�ȵ÷ǳ�ƽ���ģ������Ǿ���������
���� 
LONG );

	set("exits", ([
		"north"  : __DIR__"qianting",
                "out"    : "/d/suzhou/nandajie1",
	]));

        set("outdoors", "suzhou");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);
        setup();

        set("room_owner", "���ҵ�");
        set("room_name", "����С��");
        set("room_OWNER_id", "keep");
        set("room_id", "fyxz");
        set("room_owner_id", "keep");
        set("room_position", "�ϴ��");
}
