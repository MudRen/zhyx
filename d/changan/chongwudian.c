// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
�����ǹض���������ڳ���������һ������꣬�����ر�𱩣�����
������ĳ���������Ե�ԭ��
LONG );

        set("exits", ([
                "south" : __DIR__"road4",
        ]));
        set("objects", ([
                "/adm/npc/horseboss" : 1,
        ]));
        set("no_fight", 1);
        setup();
        replace_program(ROOM);
}



