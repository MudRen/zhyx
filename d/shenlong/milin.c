// milin.c
// Modified by haiyan

inherit ROOM;
 
void create()
{
        set("short", "����");
        set("long",@LONG
�����ǻĵ��ϵ�ï�����֣���ɭ�ɲ���̧ͷ�������ա������߳�
�ε����
LONG);   
        set("no_clean_up", 0);
        set("exits", ([ 
            "east"     : __FILE__,
            "west"     : __FILE__,
            "south"     : __FILE__,
            "north"     : __DIR__"huangdao", 
        ])); 

        set("objects", ([ 
            "/clone/beast/dushe" : 1, 
        ])); 

        setup();
        replace_program(ROOM); 
}

