// xiaoyuan.c

inherit ROOM;

#define GANJIANG        "/adm/npc/ganjiang" 
#define MOYE            "/adm/npc/moye" 


void create()
{
        object ob;

	set("short", "������");
	set("long", @LONG
��һ�߽�������ӣ��͸о�����һ����������������ݽ���һ��¯�ӣ�
����ȼ�����ܻ�⣬�ƺ������Ľ���������ǰ�ζ������Ӳ�����Զ������
�Źֵ�һ��һŮ�����Ǵ�˵�еĸɽ���Īа���ޡ�
LONG );

        set("no_fight", 1);
        set("no_sleep_room", 1);

	set("exits", ([
                "out" : __DIR__"road5",
	]));

        GANJIANG->come_here();
        MOYE->come_here();  

	setup();
        //replace_program(ROOM);
}