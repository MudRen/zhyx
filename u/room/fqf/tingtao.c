// File(/data/room/fqf/tingtao.c) of fqf's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "���θ�");
	set ("long", @LONG
��������һ�ǵ����θ�������紵��Ҷ�������������ķǳ���
�У����������Ŀ�������ʵ����һ�������书�ĺ�ȥ���� 
LONG );

	set("exits", ([
                "west" : __DIR__"zhulin",
	]));

        set("sleep_room", 1);
        setup();

        set("research_improve", 10);  //10% improved
    
        set("room_owner", "����");
        set("room_name", "���ϸ��¥");
        set("room_id", "qfxyl");
        set("room_owner_id", "fqf");
        set("room_position", "ƽԭС·");
}
