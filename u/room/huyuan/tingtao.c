// File(/data/room/huyuan/tingtao.c) of huyuan's room
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
    
        set("room_owner", "��Ԩ");
        set("room_name", "�콣ɽׯ");
        set("room_id", "tianjian");
        set("room_owner_id", "huyuan");
        set("room_position", "�ݵ�");
}
