//Room: qunyuys5.c

inherit ROOM;

void create()
{
        set("short", "Ⱥ��¥����");
        set("long", @LONG
һ�����ҡ����з���һ�Ŵ󴲣����������廨�Ľ�������ͷ������
�������£��������������һ��Ϸˮԧ�죬��ɫ���ã����������
�ϵ���һ�����򣬺�������һ��������һֻ��ױ���ӡ���ǰ����������
����Ь��һ���еģ�һ��Ů�ģ����Ŷ��á�
LONG);
        set("exits", ([ /* sizeof() == 1 */
        	"south" : __DIR__"qunyulou3",
        ]));
        set("objects", ([
        	__DIR__"npc/baiyi" : 1,
        ]) );

	setup();
        //replace_program(ROOM);
}