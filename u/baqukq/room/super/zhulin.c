// File(/data/room/super/zhulin.c) of super's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "����");
	set ("long", @LONG
�������źô�һƬ���֣��ǳ��ľ�����һ�������Ҷɳɳ���죬
��ʱ���ɾ�ȥ���θ�Ĭ�����������������书�� 
LONG );

	set("exits", ([
                "west" : __DIR__"huayuan",
                "east" : __DIR__"tingtao",
	]));

        set("outdoors", "nanhai");
        set("sleep_room", 1);
        setup();

        set("room_owner", "����");
        set("room_name", "��Ʒ��");
        set("room_id", "room");
        set("room_owner_id", "super");
        set("room_position", "ƽԭС·");
}
