inherit ROOM;

void create()
{
        set("short", "��ζ���ݶ�����");
        set("long", @LONG

    ��������ζ���ݣ���ҿ���������������鼮�����ǲ���
���ߡ�

LONG);
        set("no_fight1", 1);
        set("no_fire", 1);
        set("sleep_room",1);        
        set("exits", ([
            "down" : __DIR__"shuyuan3",
            "up" : __DIR__"shuyuan5",
        ]));
	 set("no_clean_up", 0);
	 setup();
        //replace_program(ROOM);
}




