// dulewu.c 独乐居小屋

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
	set("short", "小屋");             /* EXAMPLE */
//**    set("short", "ROOM_NAME小屋");
	set("long", @LONG
屋子不大，靠窗的地方摆了一张床，屋中一张桌，几只椅，非常简单。
恐怕只有甘于寂寞的人才住得了这种简朴的屋子。
LONG );

	set("default_long", "屋子不大，靠窗的地方摆了一张床，"   /**/
                            "屋中一张桌，几只椅，非常简单。"     /**/
                            "看来主人是一个甘于平淡寂寞的人。"); /**/
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
                return notify_fail("大门开着呢，你还推什么？\n");

        me = this_player();
        message_vision("$N用力推了推大门，就听大门“吱呀呀”的打开了。\n",
                           me);
    
        room = get_object(__DIR__"xiaoyuan");
        message("vision", "大门“吱呀呀”的被人推开了。\n", room);
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
                return notify_fail("大门关着呢，你还再关一遍？\n");

        me = this_player();
        if (! n)                       
                message_vision("$N走上前去，用力合上大门。\n", me);
         else
        
                message("vision", "大门“吱呀呀”的被人关上了。\n",
                        this_object());
        

        room = get_object(__DIR__"xiaoyuan");
        message("vision", "大门“吱呀呀”的被人关上了。\n", room);
        set("gate", "close");
        delete("exits/south");
        room->set("gate", "close");
        room->delete("exits/north");
        return 1;
}
