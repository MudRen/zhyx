inherit ROOM;

void create()
{
        set("short", "��ζ�����ߺ���");
        set("long", @LONG

    ��������ζ���ݣ���ҿ���������������鼮�����ǲ���
���ߡ�

LONG);
        set("no_fight1", 1);
        set("sleep_room",1);        
        set("exits", ([
            "down" : __DIR__"shuyuan8",
        ]));
	 set("no_clean_up", 1);
	 setup();
        //replace_program(ROOM);
}





