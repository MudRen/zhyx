// dulewu.c ���־�С��

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
	set("short", "С��");             /* EXAMPLE */
//**    set("short", "ROOM_NAMEС��");
	set("long", @LONG
���Ӳ��󣬿����ĵط�����һ�Ŵ�������һ��������ֻ�Σ��ǳ��򵥡�
����ֻ�и��ڼ�į���˲�ס�������ּ��ӵ����ӡ�
LONG );

	set("default_long", "���Ӳ��󣬿����ĵط�����һ�Ŵ���"   /**/
                            "����һ��������ֻ�Σ��ǳ��򵥡�"     /**/
                            "����������һ������ƽ����į���ˡ�"); /**/
                                                                 /**/
	

        set("exits", ([                         /* EXAMPLE */
                "south" : __DIR__"xiaoyuan",    /* EXAMPLE */
        ]));                                    /* EXAMPLE */
                                                /* EXAMPLE */
        set("gate", "close");

//**    set("objects", ([
//**            "/adm/obj/locker" : 1,
//**    ]));


//**
//**    set("sleep_room", 1);
//**    set("loving_room", 1);
        set("no_fight", 1);
        setup();
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}


void init()
{
//**        add_action("do_push", "push");
//**        add_action("do_close", "close");
}

int do_push(string arg)
{
        object me;
        object room;

        if (query("gate") == "open")
                return notify_fail("���ſ����أ��㻹��ʲô��\n");

        me = this_player();
        message_vision("$N���������ƴ��ţ��������š�֨ѽѽ���Ĵ��ˡ�\n",
                           me);
    
        room = get_object(__DIR__"xiaoyuan");
        message("vision", "���š�֨ѽѽ���ı����ƿ��ˡ�\n", room);
        set("gate", "open");
        set("exits/south", __DIR__"xiaoyuan");
        room->set("exits/north", __FILE__);
        room->set("gate", "open");
        remove_call_out("do_close");
        call_out("do_close", 10, 0, 1);
        return 1;
}

int do_close(string arg, int n)
{
        object me;
        object room;

        if (query("gate") == "close")
                return notify_fail("���Ź����أ��㻹�ٹ�һ�飿\n");

        me = this_player();
        if (! n)                       
                message_vision("$N����ǰȥ���������ϴ��š�\n", me);
         else
        
                message("vision", "���š�֨ѽѽ���ı��˹����ˡ�\n",
                        this_object());
        

        room = get_object(__DIR__"xiaoyuan");
        message("vision", "���š�֨ѽѽ���ı��˹����ˡ�\n", room);
        set("gate", "close");
        delete("exits/south");
        room->set("gate", "close");
        room->delete("exits/north");
        return 1;
}
