// File(/data/room/guoke/xiaoyuan.c) of guoke's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "ÎŞ¾¡ÑÂĞ¡Ôº");
	set ("long", @LONG
[1;36mÕâÀïÊÇÒ»¸ö²»´óµÄÔº×Ó£¬½ÇÂäÀïÔÔÁË¼¸¿ÃÊ÷£¬µØÉÏÁãÁãÉ¢É¢ÓĞÒ»
    Ğ©ËéÂäÒ¶Æ¬¡£ÔºÃÅĞéÑÚ£¬´©¹ıÔº×Ó¾ÍÊÇÒ»¸öĞ¡Îİ£¬·Ç³£¾«ÖÂ¡£
    Ğ¡ÔºÇ°Ãæ¾ÍÊÇÒ»×ùĞüÑÂ£¬Ò»ÌõĞ¡Â·òêÑÑ¶øÉÏ¡£
    »·¹ËËÄÖÜ£¬Ö»¼û²»Ô¶´¦µÄ¾ÉÊ¯±®ÉÏĞ´×Å¡°ÎŞ¾¡ÑÂ¡±¡£[2;37;0m
LONG );

        set("room_key", "1 of guoke");
	setup();

	set("exits", ([
                "out"    : "/d/xiakedao/haibin",
	]));

        set("outdoors", "nanhai");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "¹ı¿Í");
        set("room_owner_id", "guoke");
        set("room_name", "ÎŞ¾¡ÑÂ");
        set("room_id", "forever");
        set("room_position", "ÄÏº£Ö®±õ");
}
