// File(/data/room/addd/zhulin.c) of addd's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "����");
	set ("long", @LONG
�������źô�һƬ���֣��ǳ��ľ�����һ�������Ҷɳɳ���죬
��ʱ���׾�ȥ���θ�Ĭ�����������������书�� 
LONG );

	set("exits", ([
                "west" : __DIR__"huayuan",
                "east" : __DIR__"tingtao",
	]));

        set("outdoors", "suzhou");
        set("sleep_room", 1);
        setup();

        set("room_owner", "����");
        set("room_name", "�ּҴ�Ժ");
        set("room_id", "lin");
        set("room_owner_id", "addd");
        set("room_position", "�ϴ��");
}
