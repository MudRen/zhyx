// shanlu.c copyright by yuchang


inherit ROOM;

void create()
{
        set("short", "ɽ��");
        set("long", @LONG
����һ����ֱ��ɽ·��ǰ�����죬һֱ��û������֮�У�
��֪��ô���������Խ��Խϡ�٣��㲻�������ֹ������ʲ
ô�°ɣ����������������ǰ���š�
LONG
        );

        set("outdoors", "qianhuigu");

        set("exits", ([ /* sizeof() == 3 */
                "west" : __DIR__"shangu",
                "east" : __DIR__"kedian",
        ]));

        setup();
       // replace_program(ROOM);
}

