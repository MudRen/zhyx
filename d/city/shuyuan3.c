inherit ROOM;
int is_chat_room()
{
	return 1;
}
void create()
{
        set("short", "��ζ����һ����");
        set("long", @LONG

    ��������ζ���ݣ���ҿ���������������鼮�����ǲ���
���ߡ�

LONG);
        set("no_fight1", 1);
        set("no_fire", 1);
       // set("sleep_room",1);        
        set("exits", ([
            "down" : __DIR__"shuyuan2",
            "up" : __DIR__"shuyuan4",
        ]));
	 set("no_clean_up", 0);
	 setup();
        //replace_program(ROOM);
}





