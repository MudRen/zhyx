inherit ROOM;
 
void create()
{
        set("short", "��");
        set("long", @LONG
��������ãã��֮�С��㼫ĿԶ����ֻ������һ�ߣ���
Χ�����ڵ㶼û�С�����ֻ�к��˵��Ĵ�����
LONG);   
        set("outdoors", "taohua");
        set("exits", ([
               "out" : __DIR__"haitan", 
        ]));
        set("no_fight",1);
        setup();
        replace_program(ROOM) ;
}
