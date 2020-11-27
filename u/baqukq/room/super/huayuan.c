// File(/data/room/super/huayuan.c) of super's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "��԰");
	set ("long", @LONG
������Ʒ�õĺ�԰������һЩ���ɲ�������ĺ�����ɽ�󴨵�
�滨��ݣ������ǳ���������ʱ��������ƣ���ˣ��͵�����������Ϣ��
���ͻ������������֣�������ͻ����У����������������ͨ����
�˾��������ţ���������һƬ���֡� 
LONG );

	set("exits", ([
                "south"  : __DIR__"houyuan",
                "east"   : __DIR__"zhulin",
	]));

        set("outdoors", "nanhai");
        set("sleep_room", 1);
        set("room_key", "1 of super");
        setup();

        set("KEY_DOOR", ([
                "exit" : "west",
                "room" : __DIR__"jusuo",
        ]));
    
        set("room_owner", "����");
        set("room_owner_id", "super");
        set("room_name", "��Ʒ��");
        set("room_id", "room");
        set("room_position", "ƽԭС·");
}

void init()
{
        ::init();
        add_action("do_sit", "sit");
        this_player()->delete_temp("has_sit");
}

int do_sit(string arg)
{
        object me;

        me = this_player();
        if (me->query_temp("has_sit"))
        {
                message_vision("$N��������ҡ��ҡ���ò���⡣\n", me);
                return 1;
        }

        message_vision("$N���˵ĵط���������������ȥ���ɶ��ˡ�\n", me);
        me->set_temp("has_sit", 1);
        return 1;
}

int valid_leave(object me, string dir)
{
        if (me->query_temp("has_sit"))
        {
                message_vision("$N����������վ��������\n", me);
                me->delete_temp("has_sit");
        }

        return ::valid_leave(me, dir);
}
