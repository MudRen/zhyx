inherit ROOM;

void create()
{
        set("short", "Â¹Ãù·å");
        set("long", @LONG
ÁúÃÅ·åÎ÷²àÊÇÂ¹Ãù·å¡£Â¹Ãù·åÓÖ³ÆÖ¥ÅÌ·å£¬Òò·åÉÏÓĞÒ»²İ
µé×Ó£¬ĞÎÔ²Èç¸Ç£¬ÓĞÈÈÆø´ÓµØÏÂÃ°³ö£¬Ã¿µ½ÑÏ¶¬£¬ÆäËü·å¾ù»ı
Ñ©Éõºñ£¬Î¨Â¹Ãù·åÒÀÈ»Ö²ÎïÃ¯Ê¢£¬ÇÒÊ¢²úÖ¥²İ£¬Â¹¶à¾ÓÖ®¡£³£
ÓĞº×¡¢È¸¡¢µñ¡¢Ñà·ÉÂäÆäÉÏ£¬ÓĞÂ¹Ãù´ä¹È£¬µñ·ÉÖ¥¸ÇÖ®³Æ¡£
LONG );
        set("exits", ([
                "south"   : __DIR__"baiyun",
                "east"    : __DIR__"longmen",
                "northdown" : __DIR__"famu",
        ]));
        set("objects", ([
                "/clone/quarry/lu" : 2,
                "/clone/quarry/diao" : 1,
        ]));
        set("outdoors", "guanwai");
        setup();
        //replace_program(ROOM);
}

void init()
{
                add_action("do_enter", "enter");
}

int do_enter(string arg)
{
        object me = this_player();
        
        if (! arg || arg != "milin")
                return notify_fail("ÄãÒª½øÈëÄÄÀï°¡£¿\n");
        
        me->move("/d/guanwai/milin.c");
        return 1;
}
