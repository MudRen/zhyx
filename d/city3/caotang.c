inherit ROOM;

void create()
{
	set("short", "¶Å¸¦²ÝÌÃ");
	set("long", @LONG
ÕâÀïÊÇ¶Å¸¦Á÷Ô¢³É¶¼µÄ¹Ê¾Ó¡£²ÝÌÃÀïÁ÷Ë®»ØÝÓ£¬Ð¡ÇÅ¹´Á¬
ÖñÊ÷ÑÚÓ³£¬ÏÔµÃ¼È×¯ÑÏËàÄÂ£¬¹ÅÆÓµäÑÅ£¬ÓÖ²»Ê§ÓÄÉî¾²Ú×£¬Ðã
ÀöÇåÀÊ¡£
LONG);
        set("outdoors", "chengdu");
	set("no_clean_up", 0);
	set("exits", ([
		"south"  : __DIR__"path2",
	]));

        if (random(10) > 8) 
        {
              set("objects", ([
                      "/u/xiner/npc/dashi" : 1,
              ]));
        }
 
	setup();
	//replace_program(ROOM);
}
