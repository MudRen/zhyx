// File(/data/room/guoke/dulewu.c) of guoke's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "ÎŞ¾¡ÑÂĞ¡Îİ");
	set ("long", @LONG
[1;36mÎİ×Ó²»´ó£¬ÖĞ¼äÊÇÒ»·ùÉ½Ë®»­£¬¿¿´°µÄµØ·½°ÚÁËÒ»ÕÅ´²£¬
    ÎİÖĞÒ»ÕÅ×À£¬¼¸Ö»ÒÎ£¬·Ç³£¼òµ¥¡£
    Ì§Í·×ĞÏ¸¿´¿´ÄÇ»­ÖĞÉ½Ë®£¬ÄËÊÇĞñÈÕ¶«ÉıÏÂµÄÎŞ¾¡ÑÂ£¬
    ÅÔ±ßÓÃÁøÊéĞ´×Å£º
    ¡°[1;31mÓÎÏ·Ò»Éú£¬À´È¥´Ò´Ò£»Ç§½ğÉ¢¾¡£¬ÄùÅÍÖØÉú£¡[1;36m¡±£¬
    Âä¿î¡°[33mÒ»¸ö¹ı¿Í[1;36m¡±¡£[2;37;0m
LONG );

        set("objects", ([
                "/d/room/obj/storage" : 1,
        ]));

    setup();

        set("KEY_DOOR", ([
                "exit" : "south",
                "room" : __DIR__"xiaoyuan",
        ]));
    
        set("sleep_room", 1);
        set("loving_room", 1);
        set("no_fight", 1);
    
        set("room_owner", "¹ı¿Í");
        set("room_name", "ÎŞ¾¡ÑÂ");
        set("room_id", "forever");
        set("room_owner_id", "guoke");
        set("room_position", "ÄÏº£Ö®±õ");
}

