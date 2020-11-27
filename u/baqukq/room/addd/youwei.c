// File(/data/room/addd/youwei.c) of addd's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        object ob;

        set("short", "林家大院右卫舍");
	set ("long", @LONG
这里是右卫舍，是看护林家大院大门的家丁放哨的地方。 
LONG );

	set("exits", ([
                "east"   : __DIR__"qianting",
	]));

        set("objects", ([
                "/d/room/roomnpc/shouwei" : 2,
        ]));

        set("no_sleep_room", 1);
        setup();

        ob = present("shou wei", this_object());
        ob->set("coagents", ({
                ([ "startroom" : __DIR__"youwei",
                   "id"        : "shou wei 1" ]),
                ([ "startroom" : __DIR__"youwei",
                   "id"        : "shou wei 2" ]),
                ([ "startroom" : __DIR__"zuowei",
                   "id"        : "shou wei 2" ]),
                ([ "startroom" : __DIR__"zuowei",
                   "id"        : "shou wei 1" ]),
        }));

        ob = present("shou wei 2", this_object());
        ob->set("coagents", ({
                ([ "startroom" : __DIR__"youwei",
                   "id"        : "shou wei 1" ]),
                ([ "startroom" : __DIR__"youwei",
                   "id"        : "shou wei 2" ]),
                ([ "startroom" : __DIR__"zuowei",
                   "id"        : "shou wei 2" ]),
                ([ "startroom" : __DIR__"zuowei",
                   "id"        : "shou wei 1" ]),
        }));

        set("room_owner", "玄炎");
        set("room_name", "林家大院");
        set("room_id", "lin");
        set("room_owner_id", "addd");
        set("room_position", "南大街");
}
